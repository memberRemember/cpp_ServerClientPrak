#include <iostream>
#include <string>
#include <thread>
#include "CClient.h"

using namespace std;

int main()
{
    CClient client_UDP;

    thread RecProc(&CClient::RecMsg, &client_UDP);

    while (1)
    {
        string content;
        cin >> content;

        client_UDP.SendMsg(content.c_str());
    }

    RecProc.join();

    system("pause");
    return 0;
}