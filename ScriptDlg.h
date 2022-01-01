#pragma once


// CScriptDlg dialog

class CScriptDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CScriptDlg)

public:
	CScriptDlg(CWnd* pParent, CString const & scriptText);
	virtual ~CScriptDlg();

        CString GetScriptText() const;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCRIPT };
#endif

        static CString m_lastFileName;

        void UpdateSaveButtonText();
        static void SaveScript(CString const & scriptText);
        void LoadScript();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
  CString m_scriptText;
  afx_msg void OnBnClickedOpen();
  afx_msg void OnBnClickedSave();
  afx_msg void OnBnClickedSaveAs();
  afx_msg void OnClose();
  virtual void OnOK();
  virtual void OnCancel();
  CButton m_saveButton;
  virtual BOOL OnInitDialog();
};
