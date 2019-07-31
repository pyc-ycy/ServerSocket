
// MFCSOCKServerSampleDlg.h: 头文件
//

#pragma once
#include "SocketServer.h"


// CMFCSOCKServerSampleDlg 对话框
class CMFCSOCKServerSampleDlg : public CDialog
{
// 构造
public:
	void WriteLog(CString log);
	CSocketServer* pSocketServer;
	CMFCSOCKServerSampleDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCSOCKSERVERSAMPLE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 状态信息框
	CEdit m_editLog;
	CString m_Log;
	// 发送数据输入框
	CString m_editSend;
	// 接收数据
	CString m_editRecv;
	// IP地址
	CIPAddressCtrl m_IP;
	// 端口输入框
	CString m_Port;
	afx_msg void OnButtonListen();
	afx_msg void OnButtonSend();
	afx_msg LRESULT OnLogMsg(WPARAM dwEvent, LPARAM dwLen);
	afx_msg LRESULT OnRecvMsg(WPARAM dwEvent, LPARAM dwLen);
};
