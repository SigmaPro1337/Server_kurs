/**
 * @file User.cpp
 */
#include "User.h"

/**
* @brief Геттер для атрибута login
*/
string User::getLogin(){
    return login;
}

/**
* @brief Сеттер для атрибута login
*/
void User::setLogin(string login1){
    login = login1;

}

/**
* @brief Геттер для атрибута password
*/
string User::getPassword(){
    return password;
}

/**
* @brief Сеттер для атрибута password
*/
void User::setPassword(string password1){
    password = password1;
}


/**
* @brief Функция для проверки логина пользователя
*@return 1 - в случае успешной идентификации, 0 - в обратном случае
*/
bool User::CheckLogin(vector<string> Db_login){
    for (size_t i = 0; i < Db_login.size(); ++i) {
        if (Db_login[i] == login){
            return 1;
        }
    }

    return 0;
    
}


bool User::CheckPassword(vector<string> Db_password, vector<string> Db_login, string SALT){
    int t = 0;
    for (size_t i = 0; i < Db_login.size(); ++i) {
        if (Db_login[i] == login){
            t = i;
        }
    }
    
    string hash = SALT + Db_password[t];
    string HASHMD5 = MD5_hash(hash);
    
    if (HASHMD5 == password){
        return 1;
    }
    else{
        return 0;
    }
}
