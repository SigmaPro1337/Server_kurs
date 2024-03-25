/** 
* @file UserDataBase.h
* @author Черный М.В.
* @version 1.0
* @date 31.10.2023
* @copyright ИБСТ ПГУ
* @brief Заголовочный файл для модуля UserDataBase
*/

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include "ErrorManager.h"

using namespace std;
/**
* @brief Класс, предназначенный для извлечения информации из базы данных клиентов.
* @param clientDataBase Путь к файлу базы данных клиентов
* @param errorManager Экземпляр класса ErrorManager, ответственного за обработку ошибок.
*/
class UserDataBase{
    public:
        pair<vector<string>, vector<string>> getClientCredentials();

        string getClientDataBase();
        void setClientDataBase(string db);
    private:
        string clientDataBase;
        ErrorManager errorManager;

};