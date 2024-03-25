/** 
* @file User.h
* @author Черный М.В.
* @version 1.0
* @date 31.10.2023
* @copyright ИБСТ ПГУ
* @brief Заголовочный файл для модуля User
*/

#include <string>
#include  <vector>
#include <iostream>
#include "./md5/md5.h"
using namespace std;

/**
* @brief Класс, содержащий информацию о текущем пользователе
* @param login логин клиента, который подключен
* @param password пароль клиента, который подключен
*/
class User{
    private:
        string login;
        string password;
    public:
        bool CheckLogin(vector<string> Db_login);
        bool CheckPassword(vector<string> Db_password, vector<string> Db_login, string SALT);
        
        string getLogin();
        void setLogin(string login1);

        string getPassword();
        void setPassword(string password1);

};