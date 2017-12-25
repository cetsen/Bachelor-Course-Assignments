
// senacetin_Cetin_SenaNecla_hw8Dlg.h : header file
//

#pragma once
#include "afxwin.h"


// Csenacetin_Cetin_SenaNecla_hw8Dlg dialog
class Csenacetin_Cetin_SenaNecla_hw8Dlg : public CDialogEx
{
// Construction
public:
	Csenacetin_Cetin_SenaNecla_hw8Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SENACETIN_CETIN_SENANECLA_HW8_DIALOG };

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
public:
	int checkAnd;
	afx_msg void OnBnClickedCheck1();
	CComboBox dropdown;
	CButton checkShift;
	afx_msg void OnBnClickedButton1();
	CEdit operand1;
	CEdit operand2;
	afx_msg void OnEnChangeEdit1();
	CListBox listBox;
	CEdit bitBox;
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnCbnSelchangeCombo1();
	void unsignedToCString (unsigned int & myUnsignedInt1, unsigned int & myUnsignedInt2, unsigned int & result, CString & myCString, CString & myCString2, CString & myCStringResult);
};
