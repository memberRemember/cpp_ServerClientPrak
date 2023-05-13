#include <iostream>
#include <thread>
#include <string>

#include "CServer_UDP.h"
using namespace std;

int main()
{
	/*setlocale(LC_ALL, "ru");*/
	CServer_UDP server_UDP;//объект сервера UDP
    thread recProc(&CServer_UDP::RecMsg, &server_UDP);//поток для приема смс
	while (1)//прослушка
	{
		/*cout << "Введите контент: ";*/
		string content;
		cin >> content;
		server_UDP.SendMsg(content.c_str());
	}

	/*recProc.join();
	cout << "Пример" << endl;
	system("pause");
	return 0;
	cout << __cplusplus << std::endl;*/

    return 0;
}