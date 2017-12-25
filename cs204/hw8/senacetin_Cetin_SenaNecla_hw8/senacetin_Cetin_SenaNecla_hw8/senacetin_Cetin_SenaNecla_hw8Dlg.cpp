
// senacetin_Cetin_SenaNecla_hw8Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "senacetin_Cetin_SenaNecla_hw8.h"
#include "senacetin_Cetin_SenaNecla_hw8Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Csenacetin_Cetin_SenaNecla_hw8Dlg dialog



Csenacetin_Cetin_SenaNecla_hw8Dlg::Csenacetin_Cetin_SenaNecla_hw8Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Csenacetin_Cetin_SenaNecla_hw8Dlg::IDD, pParent)
	, checkAnd(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Csenacetin_Cetin_SenaNecla_hw8Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, checkAnd);
	DDX_Control(pDX, IDC_COMBO1, dropdown);
	DDX_Control(pDX, IDC_CHECK1, checkShift);
	DDX_Control(pDX, IDC_EDIT1, operand1);
	DDX_Control(pDX, IDC_EDIT2, operand2);
	DDX_Control(pDX, IDC_LIST1, listBox);
	DDX_Control(pDX, IDC_EDIT3, bitBox);
}

BEGIN_MESSAGE_MAP(Csenacetin_Cetin_SenaNecla_hw8Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK1, &Csenacetin_Cetin_SenaNecla_hw8Dlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON1, &Csenacetin_Cetin_SenaNecla_hw8Dlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &Csenacetin_Cetin_SenaNecla_hw8Dlg::OnEnChangeEdit1)
	ON_LBN_SELCHANGE(IDC_LIST1, &Csenacetin_Cetin_SenaNecla_hw8Dlg::OnLbnSelchangeList1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &Csenacetin_Cetin_SenaNecla_hw8Dlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// Csenacetin_Cetin_SenaNecla_hw8Dlg message handlers

BOOL Csenacetin_Cetin_SenaNecla_hw8Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// TODO: Add extra initialization here

	dropdown.SetCurSel(0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Csenacetin_Cetin_SenaNecla_hw8Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Csenacetin_Cetin_SenaNecla_hw8Dlg::OnPaint()
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
HCURSOR Csenacetin_Cetin_SenaNecla_hw8Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//This function operates when the user checks and unchecks the Shift box.
void Csenacetin_Cetin_SenaNecla_hw8Dlg::OnBnClickedCheck1()
{
	if(checkShift.GetCheck()) //if it is checked, combo box and Bits to Shift are enabled
	{
		dropdown.EnableWindow(TRUE);  
		bitBox.EnableWindow(TRUE);
	}
	else //if it is unchecked, combo box and Bits to Shift are disabled
	{
		dropdown.EnableWindow(FALSE);  
		bitBox.EnableWindow(FALSE);
	}
}

int maxSize=0;  //keeps the size of the string 


//This function converts unsigned integers to CString. 
void Csenacetin_Cetin_SenaNecla_hw8Dlg::unsignedToCString (unsigned int & myUnsignedInt1, unsigned int & myUnsignedInt2, unsigned int & result, CString & myCString, CString & myCString2, CString & myCStringResult)
{
	myCString.Format(_T("%u"), myUnsignedInt1);
	myCString2.Format(_T("%u"), myUnsignedInt2);
	myCStringResult.Format(_T("%u"), result);
}


//This function operates when the user clicks on the "Compute" button.  
void Csenacetin_Cetin_SenaNecla_hw8Dlg::OnBnClickedButton1()
{
	CDC *pDC = GetDC();// This class is necessary to get the length of the string
	CSize cz;// An object which keeps the length of the string.

	UpdateData(true);
	CString leftRight, op1, op2;
	dropdown.GetWindowTextW(leftRight);  //get the value inside combo box, operand1 and operand2
	operand1.GetWindowTextW(op1);
	operand2.GetWindowTextW(op2);

	//First checks if both operands are entered or not. 
	if(op1=="" || op2=="")  //If one of the operands is not entered, displays appropriate message.
	{
		CString message = _T("At least one operand was not entered");
		listBox.AddString(message);
		cz = pDC->GetTextExtent(message);  //get the size of the cstring
		if(cz.cx > maxSize)   //if the cstring is longer than maxSize, then make cstring length maxSize
			maxSize = cz.cx;   
		listBox.SetHorizontalExtent(maxSize);  
	}
	else //If both operands are entered, starts calculations.
	{
		CString myCString, myCString2, myCStringResult, textToAdd;
		unsigned int result;
		unsigned int myUnsignedInt1 = _tcstoul(op1,nullptr,10);
		unsigned int myUnsignedInt2 = _tcstoul(op2,nullptr,10);
		
		if(checkShift.GetCheck())  //If the Shift box is checked, checks if bit number is entered.
		{
			CString bitNumber;
			bitBox.GetWindowTextW(bitNumber);

			if(bitNumber=="")  //If bit number is not entered, displays appropriate message. 
			{
				CString message = _T("Specify how many bits you want to shift");
				listBox.AddString(message);
				cz = pDC->GetTextExtent(message);
				if(cz.cx > maxSize)
					maxSize = cz.cx;
				listBox.SetHorizontalExtent(maxSize);
				return;
			}
			else  //If bit number is entered, shifts the operands by the entered bit number and continues calculations with those numbers.  
			{
				unsigned int unsignedBitNumber = _tcstoul(bitNumber,nullptr,10);
				if(leftRight == "Left")
				{
					myUnsignedInt1 = myUnsignedInt1 << unsignedBitNumber;
					myUnsignedInt2 = myUnsignedInt2 << unsignedBitNumber;
				}
				else
				{
					myUnsignedInt1 = myUnsignedInt1 >> unsignedBitNumber;
					myUnsignedInt2 = myUnsignedInt2 >> unsignedBitNumber;
				}
			}
		}

		/***Do calculations, convert from unsigned int to cstring and print to list box appropriately.***/

		if(checkAnd == 0)  //If the AND button is checked
		{   
			result = myUnsignedInt1 & myUnsignedInt2;  
			unsignedToCString (myUnsignedInt1, myUnsignedInt2, result, myCString, myCString2, myCStringResult);  
			textToAdd = myCString + _T(" AND ") + myCString2 + _T(" = ") + myCStringResult;
			listBox.AddString(textToAdd);

			cz = pDC->GetTextExtent(textToAdd);
			if(cz.cx > maxSize)
				maxSize = cz.cx; 
		}
		else if(checkAnd == 1)   //If the OR button is checked
		{
			result = myUnsignedInt1 | myUnsignedInt2;
			unsignedToCString (myUnsignedInt1, myUnsignedInt2, result, myCString, myCString2, myCStringResult);
			textToAdd = myCString + _T(" OR ") + myCString2 + _T(" = ") + myCStringResult;
			listBox.AddString(textToAdd);

			cz = pDC->GetTextExtent(textToAdd);
			if(cz.cx > maxSize)
				maxSize = cz.cx; 
		}
		else if(checkAnd == 2)   //If the XOR button is checked
		{
			result = myUnsignedInt1 ^ myUnsignedInt2;
			unsignedToCString (myUnsignedInt1, myUnsignedInt2, result, myCString, myCString2, myCStringResult);
			textToAdd = myCString + _T(" XOR ") + myCString2 + _T(" = ") + myCStringResult;
			listBox.AddString(textToAdd);

			cz = pDC->GetTextExtent(textToAdd);
			if(cz.cx > maxSize)
				maxSize = cz.cx; 
		}
		listBox.SetHorizontalExtent(maxSize);  //set horizontal length to maxSize
	}
}


void Csenacetin_Cetin_SenaNecla_hw8Dlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void Csenacetin_Cetin_SenaNecla_hw8Dlg::OnLbnSelchangeList1()
{
	// TODO: Add your control notification handler code here
}


void Csenacetin_Cetin_SenaNecla_hw8Dlg::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
}
