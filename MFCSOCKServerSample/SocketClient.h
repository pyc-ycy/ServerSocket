#pragma once
#define MAXSOCKBUF	1024
// SocketClient 命令目标

class SocketClient : public CAsyncSocket
{
public:
	SocketClient();
	virtual ~SocketClient();
public:
	void Init();
	int m_nLength;
	CString m_strHost;
	CString m_strIP;
	char m_szSendBuf[MAXSOCKBUF];
	char m_szReceBuf[MAXSOCKBUF];
	HWND m_hMsgWnd;
	BOOL m_bConnect;
public:
	virtual void OnSend(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


