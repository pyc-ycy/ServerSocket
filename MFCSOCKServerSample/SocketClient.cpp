// SocketClient.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCSOCKServerSample.h"
#include "SocketClient.h"


// SocketClient

SocketClient::SocketClient()
{
	m_nLength = 0;
	memset(m_szReceBuf, 0, sizeof(m_szReceBuf));
	memset(m_szSendBuf, 0, sizeof(m_szSendBuf));
	m_bConnect = FALSE;
	m_hMsgWnd = NULL;
	m_strHost.Empty();
	m_strIP.Empty();
}

SocketClient::~SocketClient()
{
	if (m_hSocket != INVALID_SOCKET)
		Close();
}


// SocketClient 成员函数
// 发送数据
void SocketClient::OnSend(int nErrorCode)
{
	int nSendBytes = Send(m_szSendBuf, strlen(m_szSendBuf), 0);
	char* pLog = new char[20];
	sprintf(pLog, "服务器发送%d个数据", nSendBytes);
	if (m_hMsgWnd != NULL)
		::SendMessage(m_hMsgWnd, WM_SOCKET_LOG, (WPARAM)pLog, strlen(pLog));
	memset(m_szSendBuf, 0, sizeof(m_szSendBuf));
	AsyncSelect(FD_READ | FD_CLOSE);
}
// 接收数据
void SocketClient::OnReceive(int nErrorCode)
{
	m_nLength = Receive((void*)m_szReceBuf, MAXSOCKBUF, 0);
	m_szReceBuf[m_nLength] = 0;
	char* recvBuf = new char[MAXSOCKBUF];
	sprintf(recvBuf, (const char*)&m_szReceBuf, m_nLength);
	if (m_hMsgWnd != NULL)
		::SendMessage(m_hMsgWnd, WM_SOCKET_RECEIVE, (WPARAM)recvBuf, strlen(recvBuf));
	CAsyncSocket::OnReceive(nErrorCode);
}
// 连接
void SocketClient::OnConnect(int nErrorCode)
{
	char* pLog = new char[200];
	if (nErrorCode == 0)
		sprintf(pLog, "连接服务器成功");
	else sprintf(pLog, "连接服务器失败，错误代码=%d", nErrorCode);
	if (m_hMsgWnd != NULL)
		::SendMessage(m_hMsgWnd, WM_SOCKET_LOG, (WPARAM)pLog, strlen(pLog));
}
void SocketClient::OnClose(int nErrorCode)
{
	CAsyncSocket::OnClose(nErrorCode);
}
void SocketClient::Init()
{
	memset(m_szReceBuf, 0, sizeof(m_szReceBuf));
	m_nLength = MAXSOCKBUF;
}