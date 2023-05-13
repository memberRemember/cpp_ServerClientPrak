#define _WINSOCK_DEPRECATED_NO_WARNINGS //откл уведы о старых версиях
#include "CServer_UDP.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#pragma comment(lib, "ws2_32.lib") //либра для сокетов Winsock
using namespace std;
// конструктор класса CServer_UDP
CServer_UDP::CServer_UDP() : m_terminal(false)
{
    /*переменная в которой версия сокета*/
    WORD sockVersion = MAKEWORD(2, 2);

    /*переменная в которой инициализация сокета*/
    WSADATA wsaData;

    if (WSAStartup(sockVersion, &wsaData) != 0)
    {
        cout << "Initialize WSA failed";
        return;
    }
    // сокет для UDP
    m_sServer = socket(AF_INET, SOCK_DGRAM, 0);
    //структура с адресом серва
    struct sockaddr_in m_SocAddrserver;
    m_SocAddrserver.sin_addr.S_un.S_addr = 0; //адрес сервера
    m_SocAddrserver.sin_family = AF_INET; //тип адреса ipv4
    m_SocAddrserver.sin_port = htons(8090); //порт

    /* привязка сокета к серву*/
    int ret = bind(m_sServer, (sockaddr *) &m_SocAddrserver, sizeof(m_SocAddrserver));

    if (ret == -1)
    {
        cout << "bind failed" << endl;
        WSACleanup();
    }
    else
    {
        int len_Client = sizeof(sockaddr); //получение смс
        char recBuf[1025]; //буфер
        int len = recvfrom(m_sServer, recBuf, 1024, 0, (sockaddr*)&m_SocAddrClient, &len_Client);
        if (len > 0)
        {
            recBuf[len] = '\0';
            cout << "Client say: " << recBuf << endl;
            string newmessage  = "\n[1] - summa\n[2] - game (WIP)";
            SendMsg(newmessage.c_str());
        }
    }
}


void CServer_UDP::RecMsg()
{
    char recBuf[1025]; // char массив, хранящий полученное сообщение
    while (!m_terminal) { // прослушка сообщений, пока не отменят
        int len = recvfrom(m_sServer, recBuf, 1024, 0, 0, 0); // длина сообщения
        if (len > 0) // проверка на наличие символов в сообщении
        {
            recBuf[len] = '\0'; // маркер конца смс
            cout << "Client say1: " << recBuf << endl; // вывод смс в консоль серва
            string recBufStr = recBuf; // превращение смс в стринг
            int reznya = recBufStr.find(" "); //выбор пробела как разделителя слов
            recBufStr = recBufStr.substr(0,reznya); //разделение на отдельные слова
            if(recBufStr.compare("1")==0) //если смс равно 1
            {

                string message = "Enter A:";
                SendMsg(message.c_str()); //отправка смс на клиент
                cout << message; //дублирование в консоль серва
                int a,b;
                char recBuf1[1025];
                bool NegrPashet = true;
                while(NegrPashet)
                {
                    int len1 = recvfrom(m_sServer, recBuf1, 1024, 0, 0, 0);
                    recBuf1[len1] = '\0';
                    cout << "Client say:" << recBuf1 << endl;
                    string recBufStr1 = recBuf1;
                    int reznya1 = recBufStr1.find(" ");
                    recBufStr1 = recBufStr1.substr(0, reznya1);
                    a = stoi(recBufStr1); //считывание инт с клиента
                    cout << a;
                    NegrPashet = false;
                }
                message = "Enter B: ";
                SendMsg(message.c_str());
                NegrPashet = true;
                while(NegrPashet)
                {
                    int len1 = recvfrom(m_sServer, recBuf1, 1024, 0, 0, 0);
                    recBuf1[len1] = '\0';
                    cout << "Client say:" << recBuf1 << endl;
                    string recBufStr1 = recBuf1;
                    int reznya1 = recBufStr1.find(" ");
                    recBufStr1 = recBufStr1.substr(0, reznya1);
                    b = stoi(recBufStr1);
                    cout << b;
                    NegrPashet = false;
                }
                a = a+b;
                message = "Sum: " + to_string(a);
                SendMsg(message.c_str());
                string newmessage  = "\n[1] - summa\n[2] - game (WIP)";
                SendMsg(newmessage.c_str());
            }
            if(recBufStr.compare("2")==0) //если смс равно 2
            {
                string message = "Guess the number (1-10):";
                SendMsg(message.c_str());
                string message1 = "You have 5 attempts";
                SendMsg(message1.c_str());
                cout << message;
                cout << message1;
                char recBuf4[1025];
                int n;
                int x;
                int count = 5;

                srand(time(0));
                n = rand()%10 + 1;
                do
                {
                    int len4 = recvfrom(m_sServer, recBuf4, 1024, 0, 0, 0);
                    recBuf4[len4] = '\0';
                    string recBuffStr4 = recBuf4;
                    x = stoi(recBuffStr4);
                    if (x == n)
                    {
                        string message2 = "You won!";
                        SendMsg(message2.c_str());
                        cout << message2;
                        break;
                    }
                    else if (x!=n){
                        string message4 = "Attempts left: ";
                        count = count-1;
                        message4 = message4 + to_string(count);
                        SendMsg(message4.c_str());
                    }
                }
                while (x!=n && count>0);
                {
                    string newmessage  = "\n[1] - summa\n[2] - game (WIP)";
                    SendMsg(newmessage.c_str());
                }
            }
        }
    }
}


void CServer_UDP::SendMsg(const char sendBuf[]) //отправка смс на клиент
{
    int ret = sendto(m_sServer, sendBuf, strlen(sendBuf), 0, (sockaddr*) &m_SocAddrClient, sizeof(m_SocAddrClient));

    if (ret == -1)
    {
        cout << " send failed " << endl;
        cout << GetLastError() << endl;
    }
}


CServer_UDP::~CServer_UDP()
{
    closesocket(m_sServer);
    WSACleanup();
}



