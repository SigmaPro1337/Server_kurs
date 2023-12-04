#include <getopt.h>
#include "Server.h"
#pragma one

using namespace std;

void help(){
    cout << "Это программа сервер для взаимодействия с клиентом\n" << endl;
    cout << "Необходимо ввести парметры командной строки" << endl;
    cout << "парметр -h или --help для справки " << endl;
    cout << "параметр -i или --ip сетевой адрес сервера обязательный" << endl;
    cout << "параметр -p или --port порт серевера необязательный" << endl;
    cout << "параметр -d или --database файл с БД клиентов" << endl;
    cout << "параметр -l или --logfile файл-аутентификации необязательный" << endl;
}
/** 
* @file main.cpp
* @brief Главный модуль программы для получения параметров командной строки
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
                adds = string("127.0.0.1");
            }
            break;
            
        case 'p':
            if (optarg != nullptr) {
                p = string(optarg);
            }
            else{
                p = string("33333");
            }
            break;
        
        case 'd':
            if (optarg != nullptr) {
                db = string(optarg);
            }
            else{
                db = string("DB_client.conf");
            }
            break;
        
        case 'l':
            if (optarg != nullptr) {
                lfile = string(optarg);
            }
            else{
                lfile = string("log.conf");
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

	Server NewServer;
    NewServer.setAddress(adds);
    NewServer.setPort(p);

    NewServer.handeClientInteraction(db, lfile);

    // ./Server -i127.0.0.1 -p33333 -dDB_client.conf -llog.conf
	return 0;
}