
// MFCSOCKServerSampleDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCSOCKServerSample.h"
#include "MFCSOCKServerSampleDlg.h"
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


// CMFCSOCKServerSampleDlg 对话框



CMFCSOCKServerSampleDlg::CMFCSOCKServerSampleDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MFCSOCKSERVERSAMPLE_DIALOG, pParent)
	, m_Log(_T(""))
	, m_editSend(_T(""))
	, m_editRecv(_T(""))
	, m_Port(_T("6666"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCSOCKServerSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_LOG, m_editLog);
	DDX_Text(pDX, IDC_EDIT_LOG, m_Log);
	DDX_Text(pDX, IDC_EDIT_SEND, m_editSend);
	DDX_Text(pDX, IDC_EDIT_RECEIVE, m_editRecv);
	DDX_Control(pDX, IDC_IPADDRESS1, m_IP);
	DDX_Text(pDX, IDC_EDIT_PORT, m_Port);
}

BEGIN_MESSAGE_MAP(CMFCSOCKServerSampleDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LISTEN, &CMFCSOCKServerSampleDlg::OnButtonListen)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CMFCSOCKServerSampleDlg::OnButtonSend)
	ON_MESSAGE(WM_SOCKET_LOG, OnLogMsg)
	ON_MESSAGE(WM_SOCKET_RECEIVE, OnRecvMsg)
END_MESSAGE_MAP()


// CMFCSOCKServerSampleDlg 消息处理程序

BOOL CMFCSOCKServerSampleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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
	m_IP.SetWindowText("127.0.0.1");

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCSOCKServerSampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCSOCKServerSampleDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCSOCKServerSampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCSOCKServerSampleDlg::OnButtonListen()
{
	// TODO: 在此添加控件通知处理程序代码
	pSocketServer = new CSocketServer();
	UpdateData(TRUE);
	pSocketServer->m_hMsgWnd = this->GetSafeHwnd();
	if (pSocketServer->Create(_ttoi(m_Port), SOCK_STREAM, FD_ACCEPT | FD_CLOSE))
		WriteLog("创建服务器SOCKET成功");
	else WriteLog("创建服务器SOCKET失败");

	if (pSocketServer->Listen())
		WriteLog("监听服务器成功");
	else WriteLog("监听服务器失败");
}


void CMFCSOCKServerSampleDlg::OnButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码
	if (pSocketServer == NULL)
	{
		WriteLog("SOCKET没有初始化");
		return;
	}
	if (pSocketServer->m_clientList.GetCount() <= 0)
	{
		WriteLog("没有客户端SOCKET");
		return;
	}
	UpdateData(TRUE);
	int iLen = m_editSend.GetLength();
	BYTE* s = new BYTE[iLen];
	memset(s, 0x00, iLen);
	memcpy(s, (LPCTSTR)m_editSend, iLen);

	int iCount = pSocketServer->m_clientList.GetCount();
	for (int i = 0; i < iCount; i++)
	{
		POSITION pos = pSocketServer->m_clientList.FindIndex(i);
		SocketClient* pClient = (SocketClient*)pSocketServer->m_clientList.GetAt(pos);
		if (pClient != NULL)	pClient->Send((unsigned char*)s, iLen);
	}

	WriteLog("发送数据中。。。。。。");
}
// 记录日志
void CMFCSOCKServerSampleDlg::WriteLog(CString log)
{
	m_Log += log;
	m_Log += "\r\n";
	UpdateData(FALSE);
}

// 接收消息通知
LRESULT CMFCSOCKServerSampleDlg::OnRecvMsg(WPARAM dwEvent, LPARAM dwLen)
{
	if (!dwLen)	return 0;
	BYTE* temp = new BYTE[dwLen + 1];
	memset(temp, 0x00, dwLen + 1);
	memcpy(temp, (const void*)dwEvent, dwLen);
	CString log;
	log.Format("接收到客户端数据=%s\r\n", (LPCTSTR)temp);

	if (m_editRecv.GetLength() > 50000)	m_editRecv = "";
	m_editRecv += log;
	UpdateData(FALSE);
	return 0;
}

// 接收到日志
LRESULT CMFCSOCKServerSampleDlg::OnLogMsg(WPARAM dwEvent, LPARAM dwLen)
{
	if (!dwLen)	return 0;
	BYTE* temp = new BYTE[dwLen + 1];
	memset(temp, 0x00, dwLen + 1);
	memcpy(temp, (const void*)dwEvent, dwLen);
	WriteLog((LPCTSTR)temp);
	return 0;
}