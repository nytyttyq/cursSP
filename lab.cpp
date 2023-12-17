#include <afxwin.h>
#include <windows.h>
#include "resource.h"
#include <afxext.h>
#include "iostream"
#include "afxdialogex.h"


int const1 = 65536, a, b, al;
CString strText1;
int gg[31]; //dll out array

class CMyDialog : public CDialog
{
public:
	CMyDialog(UINT nIDTemplate = IDD_DIALOG1, CWnd* pParentWnd = NULL);
protected:
	CComboBox my_DlgCombo1, my_DlgCombo2, my_DlgCombo3, my_DlgCombo4;
	CSpinButtonCtrl pSpin1, pSpin2, pSpin3;
	void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBAr);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP();
};

BEGIN_MESSAGE_MAP(CMyDialog, CDialog)
	ON_WM_VSCROLL()
END_MESSAGE_MAP();

void CMyDialog::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_COMBO1, my_DlgCombo1);
	DDX_Control(pDX, IDC_COMBO2, my_DlgCombo2);
	DDX_Control(pDX, IDC_COMBO3, my_DlgCombo3);
	DDX_Control(pDX, IDC_COMBO4, my_DlgCombo4);

	DDX_Control(pDX, spin1, pSpin1);
	DDX_Control(pDX, IDC_SPIN2, pSpin2);
	DDX_Control(pDX, IDC_SPIN3, pSpin3);
	CDialog::DoDataExchange(pDX);
}

class CMyFrameWnd:public CFrameWnd
{
	public:
		CMyFrameWnd();
		int my_poly_coef[7];
		
	protected:
		CToolBar my_WndToolBar;

		afx_msg void OnQuit();

		afx_msg void OnAbout();

		afx_msg void OnText();
		afx_msg void OnGraf();

		afx_msg void OnOpen();
		afx_msg void OnSave();
		afx_msg void OnDelete();

		afx_msg void OnProjectData();
		afx_msg void OnProjectRun();

		int CMyFrameWnd::OnCreate(LPCREATESTRUCT lpCreateStruct);
		DECLARE_MESSAGE_MAP();
};


BEGIN_MESSAGE_MAP(CMyFrameWnd,CFrameWnd)
	//Project
	ON_COMMAND(ID_PROJECT_DATA,&CMyFrameWnd::OnProjectData)
	ON_COMMAND(ID_PROJECT_RUN, &CMyFrameWnd::OnProjectRun)
	//File
	ON_COMMAND(ID_FILE_OPEN, &CMyFrameWnd::OnOpen)
	ON_COMMAND(ID_FILE_SAVE, &CMyFrameWnd::OnSave)
	ON_COMMAND(ID_FILE_DELETE, &CMyFrameWnd::OnDelete)
	//Result
	ON_COMMAND(ID_RESULT_TEXT, &CMyFrameWnd::OnText)
	ON_COMMAND(ID_RESULT_GRAF, &CMyFrameWnd::OnGraf)
	//About
	ON_COMMAND(ID_ABOUT, &CMyFrameWnd::OnAbout)
	//Quit
	ON_COMMAND(ID_QUIT, &CMyFrameWnd::OnQuit)
	//ToolBar 
	ON_COMMAND(ID_BUTTON_DATA, &CMyFrameWnd::OnProjectData)
	ON_COMMAND(ID_BUTTON_RUN, &CMyFrameWnd::OnProjectRun)
	ON_COMMAND(ID_BUTTON_OPEN, &CMyFrameWnd::OnOpen)
	ON_COMMAND(ID_BUTTON_Save, &CMyFrameWnd::OnSave)
	ON_COMMAND(ID_BUTTON_DELETE, &CMyFrameWnd::OnDelete)
	ON_COMMAND(ID_BUTTON_TEXT, &CMyFrameWnd::OnText)
	ON_COMMAND(ID_BUTTON_GRAF, &CMyFrameWnd::OnGraf)
	ON_COMMAND(ID_BUTTON_ABOUT, &CMyFrameWnd::OnAbout)
	ON_COMMAND(ID_BUTTON_QUIT, &CMyFrameWnd::OnQuit)

	ON_WM_CREATE()
END_MESSAGE_MAP();

CMyFrameWnd::CMyFrameWnd()
{
	Create(NULL, (LPCTSTR)"CRINGE",
		WS_OVERLAPPEDWINDOW, rectDefault, NULL, MAKEINTRESOURCE(IDR_MENU1));
};


//-----------------------------------------------------------
void CMyDialog::OnOK()
{
	CString tmp_data;
	CMyFrameWnd* pMainWnd = (CMyFrameWnd*)(this->GetParent());

	my_DlgCombo1.GetWindowTextA(tmp_data);
	pMainWnd->my_poly_coef[0] = atoi(tmp_data);
	my_DlgCombo2.GetWindowTextA(tmp_data);
	pMainWnd->my_poly_coef[1] = atoi(tmp_data);
	my_DlgCombo3.GetWindowTextA(tmp_data);
	pMainWnd->my_poly_coef[2] = atoi(tmp_data);
	my_DlgCombo4.GetWindowTextA(tmp_data);
	pMainWnd->my_poly_coef[3] = atoi(tmp_data);

	int n;
	n = pSpin1.GetPos() - const1;
	pMainWnd->my_poly_coef[4] = n;
	n = pSpin2.GetPos() - const1;
	pMainWnd->my_poly_coef[5] = n;
	n = pSpin3.GetPos() - const1;
	pMainWnd->my_poly_coef[6] = n;
	UpdateData(TRUE);
	CDialog::OnOK();

	al = sizeof(gg) / sizeof(gg[0]);
}

void CMyDialog::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBAr)
{
	if (nSBCode==SB_ENDSCROLL)
	{
		return;
	}
	CSpinButtonCtrl* pSpin6 = (CSpinButtonCtrl*)pScrollBAr;
	if (pSpin6 = &pSpin1)
	{
		strText1.Format("%d", (pSpin6->GetPos() - const1));
		SetDlgItemText(IDC_STATIC1, strText1);
	}
	if (pSpin6 = &pSpin2)
	{
		strText1.Format("%d", (pSpin6->GetPos() - const1));
		SetDlgItemText(IDC_STATIC2, strText1);
	}
	if (pSpin6 = &pSpin3)
	{
		strText1.Format("%d", (pSpin6->GetPos() - const1));
		SetDlgItemText(IDC_STATIC3, strText1);
	}

	CDialog::OnVScroll(nSBCode, nPos, pScrollBAr);
}

void CMyFrameWnd::OnProjectData()
{
	CMyDialog my_Dialog;
	my_Dialog.DoModal();
}
void CMyFrameWnd::OnProjectRun()
{
	CString buf_data;
	buf_data.Format("a1 = %d, b1 = %d, c1 = %d \n c2 = %d \n a3 = %d, b3 = %d, c3 = %d", my_poly_coef[0],
		my_poly_coef[1], my_poly_coef[2], my_poly_coef[3], my_poly_coef[4], my_poly_coef[5], my_poly_coef[6]);
	MessageBox(buf_data);

	//dll func and message box
	int* Func(int* in_arr, int* out_arr);
	HINSTANCE my_dll = AfxLoadLibrary("CursDll.dll");
	typedef int* (*CALCFUN)(int*, int*);
	CALCFUN my_Func = (CALCFUN)GetProcAddress(my_dll, "Func");
	(*my_Func)(my_poly_coef, gg);
	AfxFreeLibrary(my_dll);
}
void CMyFrameWnd::OnOpen()
{
	CFileDialog my_FileDialog(TRUE, "txt");
	if (my_FileDialog.DoModal() == IDOK)
	{
		CStdioFile file(my_FileDialog.GetPathName(), CFile::modeRead);
		CString numBuffer;
		for (int i = 0; i < al; i++)
		{
			file.ReadString(numBuffer);
			gg[i] = _ttoi(numBuffer);
		}
		file.Close();
	}

}

void CMyFrameWnd::OnSave()
{
	CFileDialog my_FileDialog(FALSE, "txt", "Result");
	if (my_FileDialog.DoModal() == IDOK)
	{
		CStdioFile file(my_FileDialog.GetPathName(), CFile::modeWrite | CFile::modeCreate);
		CString numBuffer;
		for (int i = 0; i < al; i++)
		{
			numBuffer.Format(_T("%d\n"), gg[i]);
			file.WriteString(numBuffer);
		}
		file.Close();
	}
	
}
void CMyFrameWnd::OnDelete()
{
	CFileDialog my_FileDialog(TRUE, "txt");
	if (my_FileDialog.DoModal() == IDOK)
	{
		CFile::Remove(my_FileDialog.GetPathName());		
	}
}

void CMyFrameWnd::OnText()
{
	int iter = 0; //iterator
	CString f; f.Format("");
	int al = sizeof(gg) / sizeof(gg[0]);
	for (int i = -15; i < 16; i++)
	{
		f.Format(f + "x = %d,\t y = %d\n", i, gg[iter]);
		iter++;
	}
	MessageBox(f);
}
void CMyFrameWnd::OnGraf()
{
	::MessageBox(NULL, (LPCTSTR)"Вибраний пункт меню Result -> Graf", (LPCTSTR)"Graf", MB_OK);
}
void CMyFrameWnd::OnAbout()
{
	::MessageBox(NULL, (LPCTSTR)"Вибраний пункт меню About", (LPCTSTR)"About", MB_OK);
}
void CMyFrameWnd::OnQuit()
{
	::MessageBox(NULL, (LPCTSTR)"Вибраний пункт меню Quit", (LPCTSTR)"Quit", MB_OK);
}
//-----------------------------------------------------
//Dialog class

CMyDialog::CMyDialog(UINT nIDTemplate, CWnd* pParentWnd) : CDialog(nIDTemplate, pParentWnd) { }

BOOL CMyDialog::OnInitDialog()
{
	

	/*int const1 = 65536;*/
	CString strText1, strText2, strText3;
	int m_nSpin=0;
	CDialog::OnInitDialog();
	pSpin1.SetRange(0, 200);
	pSpin1.SetPos(m_nSpin);
	pSpin2.SetRange(0, 200);
	pSpin2.SetPos(m_nSpin);
	pSpin3.SetRange(0, 200);
	pSpin3.SetPos(m_nSpin);
	strText1.Format("%d", (pSpin1.GetPos() - const1));
	SetDlgItemText(IDC_STATIC1, strText1);
	strText2.Format("%d", (pSpin2.GetPos() - const1));
	SetDlgItemText(IDC_STATIC2, strText2);
	strText3.Format("%d", (pSpin3.GetPos() - const1));
	SetDlgItemText(IDC_STATIC3, strText3);
	CString buf_data;
	buf_data.Format("%d", 0);
	my_DlgCombo1.AddString("10");
	my_DlgCombo1.AddString("100");
	my_DlgCombo1.AddString("50");	
	my_DlgCombo2.AddString("10");
	my_DlgCombo2.AddString("50");
	my_DlgCombo2.AddString("100");
	my_DlgCombo3.AddString("10");
	my_DlgCombo3.AddString("50");
	my_DlgCombo3.AddString("100");
	my_DlgCombo4.AddString("10");
	my_DlgCombo4.AddString("50");
	my_DlgCombo4.AddString("100");
	my_DlgCombo1.SetWindowText(buf_data);
	my_DlgCombo2.SetWindowText(buf_data);
	my_DlgCombo3.SetWindowText(buf_data);
	my_DlgCombo4.SetWindowText(buf_data);

	return true;
}
//End dialog 

int CMyFrameWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CFrameWnd::OnCreate(lpCreateStruct);
	my_WndToolBar.Create(this);
	my_WndToolBar.LoadToolBar(MAKEINTRESOURCE(IDR_TOOLBAR1));
	return 0;
}
class CMyApp :public CWinApp
{
public:
	virtual BOOL InitInstance();
};
BOOL CMyApp::InitInstance()
{
	CMyFrameWnd* pMainWnd = new CMyFrameWnd;
	m_pMainWnd = pMainWnd;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
};

CMyApp app;
