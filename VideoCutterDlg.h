
// VideoCutterDlg.h : header file
//

#pragma once
#include "MediaPlayer.h"
#include "wmp.h"


// CVideoCutterDlg dialog
class CVideoCutterDlg : public CDialogEx
{
// Construction
public:
	CVideoCutterDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VIDEOCUTTER_DIALOG };
#endif

        CString m_videoFileName;
        CString m_script;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

        void UpdatePosition();

public:
  DECLARE_EVENTSINK_MAP()
  void OnPlayStateChange(long NewState);
  void OnOpenStateChange(long NewState);
  MediaPlayer m_mediaPlayer;

  CComPtr<IWMPPlayer4>              m_playerInterface;
  //CComPtr<IWMPRemoteMediaServices>  m_playerServices;
  CComPtr<IWMPControls>             m_playerControls;

  CSliderCtrl m_slider;
  CString m_positionText;
  double m_position;
  CString m_durationText;
  double m_duration;
  bool m_draggingSlider;
  long m_playState;

  double m_stepSize;
  double m_jumpSize;

  CButton m_playPauseButton;
  afx_msg void OnBnClickedOpen();
  afx_msg void OnBnClickedPlayPause();
  afx_msg void OnBnClickedBackJump();
  afx_msg void OnBnClickedBack();
  afx_msg void OnBnClickedForward();
  afx_msg void OnBnClickedForwardJump();
  void OnPositionChange(double oldPosition, double newPosition);
  void OnMediaChange(LPDISPATCH Item);
  afx_msg void OnTimer(UINT_PTR nIDEvent);
  afx_msg void OnClose();
  afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
  afx_msg void OnBnClickedSettings();
  CString m_beginTimeText;
  CString m_endTimeText;
  CString m_captionText;
  afx_msg void OnBnClickedBegin();
  afx_msg void OnBnClickedEnd();
  afx_msg void OnBnClickedScript();
  CStatic m_mediaPlayerPlaceholder;
  afx_msg void OnSize(UINT nType, int cx, int cy);

  CString FormatPrecisePosition() const;
  virtual void OnOK();
  virtual void OnCancel();
};
