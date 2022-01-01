
// VideoCutterDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "VideoCutter.h"
#include "VideoCutterDlg.h"
#include "afxdialogex.h"
#include "afxdialogex.h"
#include "ScriptDlg.h"
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CVideoCutterDlg dialog



CVideoCutterDlg::CVideoCutterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VIDEOCUTTER_DIALOG, pParent)
  , m_positionText(_T(""))
  , m_durationText(_T(""))
  , m_draggingSlider(false)
  , m_playState(wmppsStopped)
  , m_stepSize( 5.0 )
  , m_jumpSize( 30.0 )
  , m_beginTimeText(_T(""))
  , m_endTimeText(_T(""))
  , m_captionText(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

  m_script = CString("# Scale to 1080p, print text\r\n"
          "x $rcs = 'scale=1920:1080';\r\n"
        "x $fnt = \"fontfile=calibri.ttf:fontcolor=white:fontsize=42\";\r\n"
        "x $tx = 50;\r\n"
        "x $ty = 950;\r\n"
        "x $dtxt = \'drawtext=text=$caption:x=$tx:y=$ty:$fnt\';\r\n"
        "x $copts{ '22.flt' } = \"-vf \\\"$rcs,$dtxt\\\"\"\r\n"
        "\r\n");
}

void CVideoCutterDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_MEDIA_PLAYER, m_mediaPlayer);
  DDX_Control(pDX, IDC_SLIDER, m_slider);
  DDX_Control(pDX, IDC_MEDIA_PLAYER_PLACEHOLDER, m_mediaPlayerPlaceholder);
  DDX_Control(pDX, IDC_PLAY_PAUSE, m_playPauseButton);
  if (!pDX->m_bSaveAndValidate)
  {
    DDX_Text(pDX, IDC_POSITION, m_positionText);
    DDX_Text(pDX, IDC_DURATION, m_durationText);
    DDX_Text(pDX, IDC_BEGIN_TIME_TEXT, m_beginTimeText);
    DDX_Text(pDX, IDC_END_TIME_TEXT, m_endTimeText);
  }
  DDX_Text(pDX, IDC_CAPTION, m_captionText);
}

BEGIN_MESSAGE_MAP(CVideoCutterDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
  ON_BN_CLICKED(IDC_OPEN, &CVideoCutterDlg::OnBnClickedOpen)
  ON_BN_CLICKED(IDC_PLAY_PAUSE, &CVideoCutterDlg::OnBnClickedPlayPause)
  ON_BN_CLICKED(IDC_BACK_JUMP, &CVideoCutterDlg::OnBnClickedBackJump)
  ON_BN_CLICKED(IDC_BACK, &CVideoCutterDlg::OnBnClickedBack)
  ON_BN_CLICKED(IDC_FORWARD, &CVideoCutterDlg::OnBnClickedForward)
  ON_BN_CLICKED(IDC_FORWARD_JUMP, &CVideoCutterDlg::OnBnClickedForwardJump)
  ON_WM_TIMER()
  ON_WM_CLOSE()
  ON_WM_HSCROLL()
  ON_BN_CLICKED(IDC_SETTINGS, &CVideoCutterDlg::OnBnClickedSettings)
  ON_BN_CLICKED(IDC_BEGIN, &CVideoCutterDlg::OnBnClickedBegin)
  ON_BN_CLICKED(IDC_END, &CVideoCutterDlg::OnBnClickedEnd)
  ON_BN_CLICKED(IDC_SCRIPT, &CVideoCutterDlg::OnBnClickedScript)
  ON_WM_SIZE()
END_MESSAGE_MAP()


// CVideoCutterDlg message handlers


static CMFCDynamicLayout::MoveSettings move(int x, int y)
{
  CMFCDynamicLayout::MoveSettings m;
  m.m_nXRatio = x;
  m.m_nYRatio = y;
  return m;
}

static CMFCDynamicLayout::SizeSettings size(int x, int y)
{
  CMFCDynamicLayout::SizeSettings s;
  s.m_nXRatio = x;
  s.m_nYRatio = y;
  return s;
}



BOOL CVideoCutterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

        EnableDynamicLayout(TRUE);

        // Works incorrect for some reason
        //LoadDynamicLayoutResource(m_lpszTemplateName);

        CMFCDynamicLayout * layout = GetDynamicLayout();
        layout->Create(this);

        layout->AddItem(IDC_MEDIA_PLAYER_PLACEHOLDER, move(0, 0), size(100, 100));
        layout->AddItem(IDC_SLIDER, move( 0, 100 ), size( 100, 0 ));
        layout->AddItem(IDC_OPEN, move(50, 100), size(0, 0));
        layout->AddItem(IDC_PLAY_PAUSE, move(50, 100), size(0, 0));
        layout->AddItem(IDC_BACK, move(50, 100), size(0, 0));
        layout->AddItem(IDC_BACK_JUMP, move(50, 100), size(0, 0));
        layout->AddItem(IDC_FORWARD_JUMP, move(50, 100), size(0, 0));
        layout->AddItem(IDC_FORWARD, move(50, 100), size(0, 0));
        layout->AddItem(IDC_POSITION, move(50, 100), size(0, 0));
        layout->AddItem(IDC_DURATION, move(50, 100), size(0, 0));
        layout->AddItem(IDC_SETTINGS, move(50, 100), size(0, 0));
        layout->AddItem(IDC_BEGIN, move(50, 100), size(0, 0));
        layout->AddItem(IDC_BEGIN_TIME_TEXT, move(50, 100), size(0, 0));
        layout->AddItem(IDC_END, move(50, 100), size(0, 0));
        layout->AddItem(IDC_END_TIME_TEXT, move(50, 100), size(0, 0));
        layout->AddItem(IDC_CAPTION, move(50, 100), size(0, 0));
        layout->AddItem(IDC_CAPTION_STATIC, move(50, 100), size(0, 0));
        layout->AddItem(IDC_SCRIPT, move(50, 100), size(0, 0));

        IUnknown * player = m_mediaPlayer.GetControlUnknown();

        player->QueryInterface(__uuidof(IWMPPlayer4),
                               reinterpret_cast<void**>(&m_playerInterface));

        player->QueryInterface(__uuidof(IWMPControls), 
                               reinterpret_cast<void**>(&m_playerControls));

        SetTimer(1, 200, 0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVideoCutterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVideoCutterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVideoCutterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BEGIN_EVENTSINK_MAP(CVideoCutterDlg, CDialogEx)
  ON_EVENT(CVideoCutterDlg, IDC_MEDIA_PLAYER, 5001, CVideoCutterDlg::OnOpenStateChange, VTS_I4)
  ON_EVENT(CVideoCutterDlg, IDC_MEDIA_PLAYER, 5101, CVideoCutterDlg::OnPlayStateChange, VTS_I4)
  ON_EVENT(CVideoCutterDlg, IDC_MEDIA_PLAYER, 5202, CVideoCutterDlg::OnPositionChange, VTS_R8 VTS_R8)
  ON_EVENT(CVideoCutterDlg, IDC_MEDIA_PLAYER, 5802, CVideoCutterDlg::OnMediaChange, VTS_DISPATCH)
END_EVENTSINK_MAP()

void CVideoCutterDlg::UpdatePosition()
{
  if (!m_draggingSlider)
  {
    CComBSTR positionString;
    m_playerControls->get_currentPositionString(&positionString);
    m_positionText = positionString;
    UpdateData(TRUE);
    UpdateData(FALSE);
    m_playerControls->get_currentPosition(&m_position);
    m_slider.SetPos(static_cast<int>(m_position));
  }
}

void CVideoCutterDlg::OnBnClickedOpen()
{
  CString extensions(_T("Video Files (*.avi;*.mkv;*.mp4)|")
    _T("*.avi; *.mkv; *.mp4|All Files (*.*)|*.*||"));

  CFileDialog fileDialog(
    TRUE,
    nullptr,
    nullptr,
    OFN_FILEMUSTEXIST,
    extensions
  );

  if (IDOK == fileDialog.DoModal())
  {
    m_videoFileName = fileDialog.GetPathName();
    m_playerInterface->put_URL(ATL::CComBSTR(m_videoFileName));
  }
}


void CVideoCutterDlg::OnOpenStateChange(long NewState)
{}

void CVideoCutterDlg::OnPlayStateChange(long NewState)
{
  m_playState = NewState;
  CString playPauseButtonText;
  switch (NewState)
  {
  case wmppsStopped:
    playPauseButtonText = "No Video";
    break;

  case wmppsPaused:
    playPauseButtonText = "Play";
    break;

  case wmppsPlaying:
    playPauseButtonText = "Pause";
    break;

  case wmppsUndefined:
  case wmppsScanForward:
  case wmppsScanReverse:
  case wmppsBuffering:
  case wmppsWaiting:
  case wmppsMediaEnded:
  case wmppsTransitioning:
  case wmppsReady:
  case wmppsReconnecting:
  default:
    playPauseButtonText = "Wait...";
    break;
  }

  m_playPauseButton.SetWindowText(playPauseButtonText);
}


void CVideoCutterDlg::OnPositionChange(double oldPosition, double newPosition)
{
  UpdatePosition();
}


void CVideoCutterDlg::OnMediaChange(LPDISPATCH Item)
{
  CComPtr<IWMPMedia>    m_media = CComQIPtr <IWMPMedia>(Item);
  CComBSTR durationString;
  m_media->get_durationString(&durationString);
  m_durationText = durationString;
  UpdateData(TRUE);
  UpdateData(FALSE);

  m_media->get_duration(&m_duration);
  m_slider.SetRange(0, static_cast<int>(m_duration));
}


void CVideoCutterDlg::OnBnClickedPlayPause()
{
  switch (m_playState)
  {
  case wmppsStopped:
  case wmppsPaused:
    m_playerControls->play( );
    break;

  case wmppsPlaying:
    m_playerControls->pause( );
    break;

  default:;
  }
}


void CVideoCutterDlg::OnBnClickedBackJump()
{
  UpdatePosition();
  m_position = (std::max)(0.0, m_position - m_jumpSize);
  m_playerControls->put_currentPosition(m_position);
  UpdatePosition();
}


void CVideoCutterDlg::OnBnClickedBack()
{
  UpdatePosition();
  m_position = (std::max)(0.0, m_position - m_stepSize);
  m_playerControls->put_currentPosition(m_position);
  UpdatePosition();
}


void CVideoCutterDlg::OnBnClickedForward()
{
  UpdatePosition();
  m_position = (std::min)(m_duration, m_position + m_stepSize);
  m_playerControls->put_currentPosition(m_position);
  UpdatePosition();
}


void CVideoCutterDlg::OnBnClickedForwardJump()
{
  UpdatePosition();
  m_position = (std::min)(m_duration, m_position + m_jumpSize);
  m_playerControls->put_currentPosition(m_position);
  UpdatePosition();
}

void CVideoCutterDlg::OnTimer(UINT_PTR nIDEvent)
{
  UpdatePosition();

  CDialogEx::OnTimer(nIDEvent);
}



void CVideoCutterDlg::OnClose()
{
  KillTimer(1);

  CDialogEx::OnClose();
}


void CVideoCutterDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
  switch (nSBCode)
  {
  case SB_LEFT:
  case SB_RIGHT:
  case SB_LINELEFT:
  case SB_LINERIGHT:
  case SB_PAGELEFT:
  case SB_PAGERIGHT:
    m_position = m_slider.GetPos();
    m_playerControls->put_currentPosition(m_position);
    break;

  case SB_THUMBTRACK:
  {
    int const sliderPos = m_slider.GetPos();
    int const minutes = sliderPos / 60;
    int const seconds = sliderPos % 60;
    m_positionText.Format(_T("%i:%i"), minutes, seconds);
    UpdateData(TRUE);
    UpdateData(FALSE);
    m_draggingSlider = true;
    break;
  }

  case SB_THUMBPOSITION:
    m_draggingSlider = false;
    m_position = nPos;
    m_playerControls->put_currentPosition(m_position);
    break;

  default:;
  }

  CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CVideoCutterDlg::OnBnClickedSettings()
{
  // TODO: Add your control notification handler code here
}


void CVideoCutterDlg::OnBnClickedBegin()
{
  UpdatePosition();
  m_beginTimeText = FormatPrecisePosition();
  UpdateData(TRUE);
  UpdateData(FALSE);
}


void CVideoCutterDlg::OnBnClickedEnd()
{
  UpdatePosition();
  m_endTimeText = FormatPrecisePosition();
  UpdateData(TRUE);
  UpdateData(FALSE);

  if (!m_captionText.IsEmpty())
  {
    m_script += _T("x $caption = '");
    m_script += m_captionText;
    m_script += _T("'\r\n");
  }

  m_script += m_videoFileName;
  m_script += _T(" ");
  m_script += m_beginTimeText;
  m_script += _T(" ");
  m_script += m_endTimeText;
  m_script += _T("\r\n\r\n");
}


void CVideoCutterDlg::OnBnClickedScript()
{
  CScriptDlg scriptDlg(this, m_script);
  scriptDlg.DoModal();
  m_script = scriptDlg.GetScriptText();
}


void CVideoCutterDlg::OnSize(UINT nType, int cx, int cy)
{
  CDialogEx::OnSize(nType, cx, cy);

  if (m_mediaPlayerPlaceholder.m_hWnd)
  {
    CRect mediaRect;
    m_mediaPlayerPlaceholder.GetWindowRect(&mediaRect);
    ScreenToClient(&mediaRect);
    m_mediaPlayer.SetWindowPos(0, mediaRect.left, mediaRect.top,
      mediaRect.Width(), mediaRect.Height(), 0 );
  }
}

CString CVideoCutterDlg::FormatPrecisePosition() const
{
  int const    minutes = static_cast< int >( m_position ) / 60;
  double const seconds = m_position - 60.0 * minutes;
  CString formatted;
  formatted.Format(_T("%i:%.2f"), minutes, seconds );
  return formatted;
}



void CVideoCutterDlg::OnOK()
{
  KillTimer(1);

  CDialogEx::OnOK();
}


void CVideoCutterDlg::OnCancel()
{
  KillTimer(1);

  CDialogEx::OnCancel();
}
