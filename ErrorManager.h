/** 
* @file ErrorManager.h
* @author Черный М.В.
* @version 1.0
* @date 31.10.2023
* @copyright ИБСТ ПГУ
* @brief Заголовочный файл для модуля ErrorManager
*/
#include <string>
#include <chrono>
#include <ctime>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

/** @brief Класс обработки ошибок ErrorManager
* @details Менеджер вывода сообщений об ошибках
*/
class ErrorManager{
    public:
        string getlogFile();
        void setlogFile(string logfile);

        void ErrorManage(string info);

        void SaveError(string flag, string info, int type1);

    private:
        string logFile;
};