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
class UserDataBase{
    public:
        pair<vector<string>, vector<string>> getClientCredentials();

        string getClientDataBase();
        void setClientDataBase(string db);
    private:
        string clientDataBase;
        ErrorManager errorManager;

};