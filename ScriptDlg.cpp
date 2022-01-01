// ScriptDlg.cpp : implementation file
//

#include "pch.h"
#include "VideoCutter.h"
#include "ScriptDlg.h"
#include "afxdialogex.h"


// CScriptDlg dialog
CString CScriptDlg::m_lastFileName;

IMPLEMENT_DYNAMIC(CScriptDlg, CDialogEx)

CScriptDlg::CScriptDlg(CWnd* pParent, CString const & scriptText)
	: CDialogEx(IDD_SCRIPT, pParent)
  , m_scriptText(scriptText)
{

}

CScriptDlg::~CScriptDlg()
{
}

CString CScriptDlg::GetScriptText() const
{
  return m_scriptText;
}

void CScriptDlg::UpdateSaveButtonText()
{
  CString buttonText;
  if (m_lastFileName.IsEmpty())
  {
    buttonText = _T("Save...");
  }
  else
  {
    CString fileName(PathFindFileName(m_lastFileName));
    buttonText = CString("Save ") + fileName;
  }
  m_saveButton.SetWindowText(buttonText);
}

void CScriptDlg::SaveScript()
{
  CStringA asciiScript(m_scriptText);
  CStdioFile file(m_lastFileName, CFile::modeWrite|CFile::typeBinary|CFile::modeCreate);
  file.Write(asciiScript.GetString(), asciiScript.GetLength());
}

void CScriptDlg::LoadScript()
{
  CStdioFile file(m_lastFileName, CFile::modeRead | CFile::typeBinary);
  size_t const nBytes = file.GetLength();
  CStringA asciiScript;
  file.Read(asciiScript.GetBuffer(nBytes), nBytes);
  asciiScript.ReleaseBuffer(nBytes);
  m_scriptText = CString(asciiScript);
}

void CScriptDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_SCRIPT_TEXT, m_scriptText);
  DDX_Control(pDX, IDC_SAVE, m_saveButton);
}


BEGIN_MESSAGE_MAP(CScriptDlg, CDialogEx)
  ON_BN_CLICKED(IDC_OPEN, &CScriptDlg::OnBnClickedOpen)
  ON_BN_CLICKED(IDC_SAVE, &CScriptDlg::OnBnClickedSave)
  ON_BN_CLICKED(IDC_SAVE_AS, &CScriptDlg::OnBnClickedSaveAs)
  ON_WM_CLOSE()
END_MESSAGE_MAP()


// CScriptDlg message handlers


void CScriptDlg::OnBnClickedOpen()
{
  CString extensions(_T("Text Files (*.txt)|")
    _T("*.txt|All Files (*.*)|*.*||"));

  CFileDialog fileDialog(
    TRUE,
    nullptr,
    nullptr,
    OFN_FILEMUSTEXIST,
    extensions
  );

  if (IDOK == fileDialog.DoModal())
  {
    m_lastFileName = fileDialog.GetPathName();
    LoadScript();
    UpdateSaveButtonText();
  }
}


void CScriptDlg::OnBnClickedSave()
{
  UpdateData();

  if (m_lastFileName.IsEmpty())
  {
    CString extensions(_T("Text Files (*.txt)|")
      _T("*.txt|All Files (*.*)|*.*||"));

    CString defaultExtension(_T("*.txt"));

    CFileDialog fileDialog(
      FALSE,
      defaultExtension,
      m_lastFileName,
      OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
      extensions
    );

    if (IDOK == fileDialog.DoModal())
    {
      m_lastFileName = fileDialog.GetPathName();
      UpdateSaveButtonText();
    }
  }

  if (!m_lastFileName.IsEmpty())
  {
    SaveScript();
  }
}


void CScriptDlg::OnBnClickedSaveAs()
{
  UpdateData();

  CString extensions(_T("Text Files (*.txt)|")
    _T("*.txt|All Files (*.*)|*.*||"));

  CString defaultExtension(_T("*.txt"));

  CFileDialog fileDialog(
    FALSE,
    defaultExtension,
    m_lastFileName,
    OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
    extensions
  );

  if (IDOK == fileDialog.DoModal())
  {
    m_lastFileName = fileDialog.GetPathName();
    SaveScript();
    UpdateSaveButtonText();
  }
}

void CScriptDlg::OnClose()
{
  UpdateData();

  CDialogEx::OnClose();
}


void CScriptDlg::OnOK()
{
  UpdateData();

  CDialogEx::OnOK();
}


void CScriptDlg::OnCancel()
{
  UpdateData();

  CDialogEx::OnCancel();
}
