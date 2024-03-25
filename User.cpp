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
* @brief Функция проверки логина пользователя, который подключен
* @return Возвращает true, если логин подключенного клиента обнаружен в базе данных; в противном случае возвращает false
*/
bool User::CheckLogin(vector<string> Db_login){
    for (size_t i = 0; i < Db_login.size(); i++) {
        if (Db_login[i] == login){
            return 1;
        }
    }

    return 0;
    
}

/**
* @brief Функция проверки пароля подключенного клиента
* @return Возвращает true, если пароль клиента, подключенного в данный момент, соответствует паролю из базы данных; в противном случае возвращает false
*/
bool User::CheckPassword(vector<string> Db_password, vector<string> Db_login, string SALT){
    int user_idx = 0;
    for (size_t i = 0; i < Db_login.size(); ++i) {
        if (Db_login[i] == login){
            user_idx = i;
        }
    }
    
    string hash = SALT + Db_password[user_idx];
    string HASHMD5 = MD5_hash(hash);
    
    if (HASHMD5 == password){
        return 1;
    }
    else{
        return 0;
    }
}
