/**
* @file UserDataBase.cpp
*/
#include "UserDataBase.h"

/**
* @brief Сеттер для атрибута db
*/
void UserDataBase::setClientDataBase(string db){
    clientDataBase = db;
}

/**
* @brief Геттер для атрибута db
*/
string UserDataBase::getClientDataBase(){
    return clientDataBase;
}

/**
* @brief Функция для получения БД клиентов
*@return Возращает векторы логинов и паролей соответственно firstVector, secondVector 
*/
pair<vector<string>, vector<string>> UserDataBase::getClientCredentials() {

    vector<string> firstVector;
    vector<string> secondVector;

    ifstream inputFile(getClientDataBase());

    if (!inputFile.is_open()){
        inputFile.close();
        errorManager.SaveError("критичная", "Ошибка в функции getClientCredentials. Файл с БД не может быть открыт или пуст.", 1);
        
    }
    else if(inputFile.peek() == std::ifstream::traits_type::eof()) {
        inputFile.close();
        errorManager.SaveError("критичная", "Ошибка в функции getClientCredentials. Файл с БД не может быть открыт или пуст.", 2);

    }
    
    else
    {
        std::string line;
        while (std::getline(inputFile, line)) {
            std::istringstream ss(line);
            std::string first, second;
            
            // Чтение двух строк, разделенных пробелом
            if (ss >> first && ss >> second) {
                firstVector.push_back(first);
                secondVector.push_back(second);
            }
        }

        inputFile.close();
    }

    return std::make_pair(firstVector, secondVector);
}

