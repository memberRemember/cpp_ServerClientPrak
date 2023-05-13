#pragma once //следит чтобы файл при компиляции был только один
#include <winsock2.h>
using namespace std;

class CServer_UDP
{
public:
    CServer_UDP();
    void SendMsg(const char sendBuf[]);
    void RecMsg();
    ~CServer_UDP();

private:
    SOCKET m_sServer;
    struct sockaddr_in m_SocAddrClient{};//хранит инфу о клиенте при подключении
    bool m_terminal;
};

