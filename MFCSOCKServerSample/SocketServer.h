#pragma once
#include "SocketClient.h"
// CSocketServer 命令目标

class CSocketServer : public CAsyncSocket
{
public:
	CSocketServer();
	virtual ~CSocketServer();
public:
	void DeleteRemoteSocket(SocketClient* pSock);
	POSITION GetRemoteSocketPos(SocketClient* pSock);
	SocketClient* GetRemoteSocket(int pSock);
	CPtrList m_clientList;
	HWND m_hMsgWnd;
public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


