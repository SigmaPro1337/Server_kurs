/** 
* @file main.cpp
*/
#include <getopt.h>
#include "Server.h"
#pragma one

using namespace std;
/**
* @brief Функция для получения инструкции по использованию программы
*/
void help(){
    cout << "Это программа сервер для взаимодействия с клиентом\n" << endl;
    cout << "Парметры командной строки" << endl;
    cout << "-h для справки" << endl;
    cout << "Необязятельные параметры:" << endl;
    cout << "-i сетевой адрес сервера" << endl;
    cout << "-p порт сервера" << endl;
    cout << "-d файл с БД клиентов" << endl;
    cout << "-l лог-файл" << endl;
    cout << "Пример запуска со значениями по умолчанию: ./Server -i127.0.0.1 -p33333 -d/etc/vcalc.conf -l./var/log/vcalc.log" << endl;
}

/**
* @brief Функция для извлечения параметров командной строки от оператора
*/
int main (int argc, char *argv[]){

	// Опции командной строки
    const struct option long_options[] = {
        {"ip", optional_argument, nullptr, 'i'},
        {"port", optional_argument, nullptr, 'p'},
        {"db", optional_argument, nullptr, 'd'},
        {"logfile", optional_argument, nullptr, 'l'},
        {"help", no_argument, nullptr, 'h'},
        {nullptr, 0, nullptr, 0}
    };

    // Класс для взаимодействия с клиент-сервером
    string adds;
    string p;
    string db;
    string lfile;

   // Обработка опций командной строки
    int opt;
    int option_index = 0;
    while ((opt = getopt_long(argc, argv, "i::p::d::l::h::", long_options, &option_index)) != -1) {
        switch (opt) {
        case 'i':
            if (optarg != nullptr) {
                adds = string(optarg);
            }
            else{
                cerr << "Error: Invalid option\n";
                return 2;
            }
            break;
            
        case 'p':
            if (optarg != nullptr) { 
                p = string(optarg);
            }
            else{
                cerr << "Error: Invalid option\n";
                return 2;
            }
            break;
        
        case 'd':
            if (optarg != nullptr) {
                db = string(optarg);
            }
            else{
                cerr << "Error: Invalid option\n";
                return 2;
            }
            break;
        
        case 'l':
            if (optarg != nullptr) {
                lfile = string(optarg);
            }
            else{
                cerr << "Error: Invalid option\n";
                return 2;
            }
            break;
            
        case 'h':
            help();        
            return 1;

        default:
            // Некорректная опция
            cerr << "Error: Invalid option\n";
            help();
            return 2;
        }
    }
    
    if(adds == ""){
        adds = string("127.0.0.1");
        help();
    }
    if (p == "" )
    {
        p = string("33333"); 
    }
    if (db == "")
    {
        db = string("./etc/vcalc.conf");
    }
    if (lfile == "")
    {
        lfile = string("./var/log/vcalc.log"); 
    }

	Server NewServer;
    NewServer.setAddress(adds);
    NewServer.setPort(p);

    NewServer.handeClientInteraction(db, lfile);

    // ./Server -i127.0.0.1 -p33333 -dDB_client.conf -llog.conf
	return 0;
}