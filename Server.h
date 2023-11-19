/** 
* @file Server.h
* @author Черный М.В.
* @version 1.0
* @date 31.10.2023
* @copyright ИБСТ ПГУ
* @brief Заголовочный файл для модуля Server
*/

#pragma one
#include <sys/types.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fstream>
#include <vector>
#include <random>

#include <string>
#include <locale>
#include <codecvt>


#include "./md5/md5.h"
#include "UserDataBase.h"
#include "User.h"
//#include "ErrorManager.h"
using namespace std;


/** 
* @brief Основной класс для взаимодействия клиента с сервером
* @param serverAddress адрес сервера
* @param serverPort порт сервера
*/
class Server{
    public:
        int handeClientInteraction(string db, string lfile);
        uint32_t multiplyVectors(const std::vector<uint32_t>& array);
        
        void setAddress(string address1);
        string getAddress();

        void setPort(string port1);
        int getPort();
    private:
        string serverAddress;
        int serverPort;


};
