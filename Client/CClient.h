#pragma once

#include <winsock2.h>

class CClient {
public:
    CClient();
    void RecMsg();
    void SendMsg(const char sendBuf[]);
    ~CClient();
private:
    SOCKET m_sockClient;
    sockaddr_in m_TargetServer;
};