/**
 * @file ErrorManager.cpp
 */
#include "ErrorManager.h"

/**
* @brief Геттер для атрибута logFile
*/
string ErrorManager::getlogFile(){
    return logFile;
}
/**
* @brief Сетттер для атрибута logFile
*/
void ErrorManager::setlogFile(string logfile){
    std::ifstream inputFile(logfile);
    if (!inputFile.is_open()){
        inputFile.close();
        SaveError("критичная", "Ошибка в функции setlogFile. Файл для записи ошибок не может быть открыт.", 3);
    }
    logFile = logfile;
}


/**
* @brief Функция для обработки ошибок. Аварийно завершает программу
* @param info Описывает подробную информацию об ошибке
*/
void ErrorManager::ErrorManage(string info){
    throw std::invalid_argument(info);
}

/**
* @brief Функция записи ошибок в журнал записи ошибок
*/
void ErrorManager::SaveError(string flag, string info, int type1=0){
     // Получаем текущую дату и время
    time_t currentTime = time(nullptr);
    tm* localTime = localtime(&currentTime);

    string logFileName = getlogFile();
    std::ofstream logFile(logFileName, std::ios::app);
    if (logFile.is_open()) {
        // Записываем дату и время
        logFile << std::put_time(localTime, "%Y-%m-%d %H:%M:%S") << " ";

        // Добавляем флаг
        logFile << flag << " ";

        // Записываем информацию об ошибке
        logFile << info << std::endl;

        // Закрываем файл
        logFile.close();
    }
    if (flag == "критичная"){
        ErrorManage(info);
    }
    
}
