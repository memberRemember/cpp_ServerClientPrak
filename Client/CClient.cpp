#include "CClient.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

CClient::CClient()
{
    WORD sockVersion = MAKEWORD(2, 2);
    WSADATA wsaData;
    if (WSAStartup(sockVersion, &wsaData) != 0)
    {
        std::cout << "Initialize WSA failed" << std::endl;
        return;
    }

    m_sockClient = socket(AF_INET, SOCK_DGRAM, 0);

    m_TargetServer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    m_TargetServer.sin_family = AF_INET;
    m_TargetServer.sin_port = htons(8090);

    if (m_sockClient == -1)
    {
        std::cout << "Create socket failed!" << std::endl;
        WSACleanup();
    }
    else
    {
        sendto(m_sockClient, "hello server", strlen("hello server"), 0, (sockaddr*)&m_TargetServer, sizeof(m_TargetServer));
    }
}

void CClient::SendMsg(const char sendBuf[])
{
    sendto(m_sockClient, sendBuf, strlen(sendBuf), 0, (sockaddr*)&m_TargetServer, sizeof(m_TargetServer));
}
void CClient::RecMsg()
{
    char recBuf[1025];

    while (1)
    {
        int len = recvfrom(m_sockClient, recBuf, 1024, 0, 0, 0);
        if (len > 0)
        {
            recBuf[len] = '\0';
            std::cout << "Server say: " << recBuf << std::endl;
        }
    }

}

CClient::~CClient()
{
    closesocket(m_sockClient);
    WSACleanup();
}