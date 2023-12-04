/**
* @file Server.cpp
*/

#include "Server.h"
#include <cstdint>
/**
* @brief Сеттер для атрибута serverAddress
*/
void Server::setAddress(string address1){
    if (address1 != "127.0.0.1"){
        errorManager.SaveError("критичная", "Ошибка в функции setAddress. Использование неразрешенных портов.", 7);
    }
    serverAddress = address1;
}

/**
* @brief Геттер для атрибута serverAddress
*/
string Server::getAddress(){
    return serverAddress;
}

/**
* @brief Сеттер для атрибута serverAddress
*/
void Server::setPort(string port1){
    if (stoi(port1) < 1000){
        errorManager.SaveError("критичная", "Ошибка в функции setPort. Использование зарезервированных портов.", 6);
    }
    serverPort = stoi(port1);
}

/**
* @brief Геттер для атрибута serverAddress
*/
int Server::getPort(){
    return serverPort;
}

/**
* @brief Функция для генерации строки SALT16
*/
string generateSalt() {
    // Символы, которые могут встречаться в строке SALT
    const string saltCharacters = "0123456789ABCDEF";
    const int saltLength = 16;

    // Генератор случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, saltCharacters.length() - 1);

    std::string salt;
    salt.reserve(saltLength);

    for (int i = 0; i < saltLength; ++i) {
        int randomIndex = dis(gen);
        salt += saltCharacters[randomIndex];
    }

    return salt;
}

/**
* @brief Функция перемножения элементов вектора
* @return возвращает произведение. При переполнении вверх должна возвращать 2^31-1, а при переполнении вниз - -2^32.
*/
uint32_t Server::multiplyVectors(const std::vector<uint32_t>& array) {
    if (array.empty()) {
        return 0; // Если массив пуст, возвращаем 0.
    }

    uint32_t result = 1;

        for (const auto& element : array) {
            // Проверка на переполнение вверх
            if (result > (std::numeric_limits<uint32_t>::max() / element)) {
                return 2147483647;
            }
            result *= element;
        }

        return result;
}

/**
* @brief Основная функция для обслуживание клиентов
* @param db хранит в себе путь к файлу с БД клиентов
* @param log хранит в себе путь к журналу с записями об ошибках
*/
int Server::handeClientInteraction(string db, string lfile){
    
    // Получение пути к файлу для записи ошибок
    ErrorManager Err;
    Err.setlogFile(lfile);

    // Получение пути к файлу с БД клиентов
    UserDataBase DB;
    DB.setClientDataBase(db);
    auto result = DB.getClientCredentials();
    vector<std::string> vlogin = result.first;
    vector<std::string> vpassword = result.second;

    // Создание сокета
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        Err.SaveError("критичная", "Ошибка в функции handeClientInteraction. Ошибка при создании сокета.", 4);
    }

    // Настраиваем адрес сервера
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
     serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_port = htons(getPort());

    // Привязка сокета к адресу
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        close(serverSocket);
        Err.SaveError("критичная", "Ошибка в функции handeClientInteraction. Ошибка при привязке сокета к адресу.", 5);
    }

    // Прослушивание порта
    if (listen(serverSocket, 5) == -1) {
        close(serverSocket);
        Err.SaveError("критичная", "Ошибка в функции handeClientInteraction. Ошибка при начале прослушивания порта.", 6);
    }

    std::cout << "\nСервер запущен на адресе 127.0.0.1 и порту " << getPort() << std::endl;

     while (true) {
        // Принимаем соединение от клиента
        struct sockaddr_in clientAddress;
        socklen_t clientAddressLength = sizeof(clientAddress);
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);
        if (clientSocket == -1) {
            close(serverSocket);
            Err.SaveError("некритичная", "Ошибка в функции handeClientInteraction. Ошибка при принятии соединения.", 0);
        }

        cout << "CONNECTION CLIENT: OK" << endl;


        char buf[1024];
        int bytes_read;

        // Получение от клиента логина
        bytes_read = recv(clientSocket, buf, sizeof(buf), 0);
        buf[bytes_read] = '\0';
        User user;
        user.setLogin(string(buf));
        
        string s1;
        // Проверка логина
        if(!user.CheckLogin(vlogin)){
            
            s1 = "ERR";
            cout << "AUTHENTICATION: ERR" << endl;
            cout << "CLOSE SOCKET CLIENT" << endl;
            strcpy(buf,s1.c_str());
            send(clientSocket, buf, s1.length(), 0);

            close(clientSocket);
            Err.SaveError("некритичная", "Ошибка в функции handeClientInteraction. Ошибка аутентификации", 0);
            continue;
        }

        // Отправка SALT16 клиенту
        string s2 = generateSalt();
        cout << "SALT16: " << s2 << endl;
        strcpy(buf, s2.c_str());
        send(clientSocket, buf, s2.length(), 0);


        // Получение от клиента HASH
        bytes_read = recv(clientSocket, buf, sizeof(buf), 0);
        buf[bytes_read] = '\0';
        user.setPassword(string(buf));

        string s3;
        // Проверка пароля
        if(!user.CheckPassword(vpassword, vlogin, s2)){
            
            s3 = "ERR";
            cout << "AUTHENTICATION: ERR" << endl;
            strcpy(buf,s3.c_str());
            send(clientSocket, buf, s3.length(), 0);

            close(clientSocket);
            Err.SaveError("некритичная", "Ошибка в функции handeClientInteraction. Ошибка аутентификации", 0);
            continue;
        }

        string s4 = "OK";
        cout << "AUTHENTICATION: OK" << endl;
        strcpy(buf,s4.c_str());
        send(clientSocket, buf, s4.length(), 0);


        // Получение веторов

        // Получение количества векторов
        uint32_t col = 0;
        recv(clientSocket, &col, sizeof(col), 0);
        cout << "col: " << col << endl;

        for(auto i = 0; i < col; i++){

            // Получение длины вектора
            uint32_t vec_len = 0;
            recv(clientSocket, &vec_len, sizeof(vec_len), 0);
            cout << "vec_len: " << vec_len << endl;

            // Получение вектора
            uint32_t arr[vec_len] = {0};

            recv(clientSocket, &arr, sizeof(arr), 0);

            vector<uint32_t> vec;
            for (size_t j = 0; j < vec_len; j++) {
            vec.push_back(arr[j]);
            cout << vec[j] << " ";
            }
            cout << "\n";

            // Подсчет результатов
            uint32_t res = multiplyVectors(vec);
            cout << "res: " << res << endl;

            // Отправка результата
            send(clientSocket, &res, sizeof(res), 0);


        }

        // Закрываем соединение с клиентом
        cout << "CLOSE SOCKET CLIENT\n" << endl;
        close(clientSocket);
    }

    // Закрываем серверный сокет
    close(serverSocket);

    return 0;
}