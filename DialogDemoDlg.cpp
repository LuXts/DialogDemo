// DialogDemoDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "DialogDemo.h"
#include "DialogDemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
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

// CDialogDemoDlg 对话框

CDialogDemoDlg::CDialogDemoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOGDEMO_DIALOG, pParent)
	, m_sPathEdit(_T(""))
	, m_sWriteEdit(_T(""))
	, m_sAddEdit(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDialogDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PATH_EDIT, m_sPathEdit);
	//  DDX_Control(pDX, IDC_WRITE_EDIT, m_sWriteEdit);
	DDX_Text(pDX, IDC_WRITE_EDIT, m_sWriteEdit);
	DDX_Text(pDX, IDC_ADD_EDIT, m_sAddEdit);
}

BEGIN_MESSAGE_MAP(CDialogDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN_BUTTON, &CDialogDemoDlg::OnClickedOpenButton)
	ON_BN_CLICKED(IDC_ADD_BUTTON, &CDialogDemoDlg::OnClickedAddButton)
	ON_BN_CLICKED(IDC_WRITE_BUTTON, &CDialogDemoDlg::OnClickedWriteButton)
END_MESSAGE_MAP()

// CDialogDemoDlg 消息处理程序

BOOL CDialogDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_sWriteEdit = "hello world";
	m_sAddEdit = "hello 交大";
	UpdateData(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDialogDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDialogDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDialogDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDialogDemoDlg::OnClickedOpenButton()
{
	CFileDialog mFileDialog(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT, _T("文本文件(*.txt)|*.txt||"), AfxGetMainWnd());
	if (mFileDialog.DoModal() != IDCANCEL) {
		m_sPathEdit = mFileDialog.GetPathName();
		UpdateData(FALSE);
	}
	// TODO: 在此添加控件通知处理程序代码
}

void CDialogDemoDlg::OnClickedAddButton()
{
	if (m_sPathEdit == "") {
		MessageBox(_T("请输入正确的文件名！"));
	}
	else {
		UpdateData(TRUE);
		CFile m_cFile;
		m_cFile.Open(m_sPathEdit, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite);
		if (m_cFile) {
			m_cFile.SeekToEnd();
			m_cFile.Write(m_sAddEdit, m_sAddEdit.GetLength() * sizeof(wchar_t));
			MessageBox(_T("以 UTF-16 LE 追加成功！"));
		}
		else {
			MessageBox(_T("打开文件出错！"));
		}
		m_cFile.Close();
	}
	//MessageBox(m_sAddEdit);
	// TODO: 在此添加控件通知处理程序代码
}

void CDialogDemoDlg::OnClickedWriteButton()
{
	if (m_sPathEdit == "") {
		MessageBox(_T("请输入正确的文件名！"));
	}
	else {
		UpdateData(TRUE);
		CFile m_cFile;
		m_cFile.Open(m_sPathEdit, CFile::modeCreate | CFile::modeReadWrite);
		if (m_cFile) {
			m_cFile.Write(m_sWriteEdit, m_sWriteEdit.GetLength() * sizeof(wchar_t));
			MessageBox(_T("以 UTF-16 LE 写入成功！"));
		}
		else
		{
			MessageBox(_T("打开文件出错！"));
		}
		m_cFile.Close();
	}
	//MessageBox(m_sWriteEdit);
	// TODO: 在此添加控件通知处理程序代码
}