#include "TestData.h"

using namespace std;

int TestData:: send_recv()
{
    send(serverSocket, uname, sizeof(uname), 0);

    char SALT[1024] = {0};
    int bytes_read = recv(serverSocket, SALT, sizeof(SALT), 0);
    printf("Ожидается число SALT. ");
    if (strcmp(SALT, "ERR") == 0)
    {
        printf("Получен код: ERR.\n");
        return 1;
    }
    printf("Получено число SALT.\n");
    

    string hash = string(SALT) + string(passwd);
    string HASHMD5 = MD5_hash(hash);

    char buf[1024]= {0};
    strcpy(buf, HASHMD5.c_str());
    send(serverSocket, buf, sizeof(buf), 0);


    char CODE[1024] = {0};
    int code_bytes_read = recv(serverSocket, CODE, sizeof(CODE), 0);
    printf("Ожидается код аутентификации. ");
    if (strcmp(CODE, "OK") != 0)
    {
        printf("Получен код: ERR.\n");
        return 1;
    }
    else
    if (strcmp(CODE, "OK") == 0)
    {
        printf("Получен код: %s.\n", CODE);
        send(serverSocket, &vector_n, sizeof(vector_n), 0);

        int cnt = 0;

        for (int i = 0; i < vector_n; i++)
        {
            send(serverSocket, &vector_lens[i], sizeof(vector_lens[i]), 0);
            for (int y = 0; y < vector_lens[i]; y++)
            {
                uint32_t v = vectors[cnt];
                send(serverSocket, &v, sizeof(v), 0);
                cnt++;
            }

            uint32_t res_recv = 0;
            recv(serverSocket, &res_recv, sizeof(res_recv), 0);
            printf("Получен результат: %ld\n", res_recv);
        }            
    }   

    return 0;
}


void TestData:: read_data(FILE* fin)
{
    fscanf(fin,"%s ", &uname);
    fscanf(fin,"%s ", &passwd);
    fscanf(fin,"%s ", &s_addr_str);
    fscanf(fin,"%d ", &sin_port);
    fscanf(fin,"%d: ", &vector_n);
    
    vector_lens = (uint32_t*)calloc(vector_n, sizeof(uint32_t));

    int sum_len = 0;
    for (int i = 0; i < vector_n; i++)
    {
        fscanf(fin,"%d ", &(vector_lens[i]));   
        sum_len += vector_lens[i];
    }

    vectors = (uint32_t*)calloc(sum_len, sizeof(uint32_t));
    
    int cnt = 0;
    for (int i = 0; i < vector_n; i++)
    {
        
        for(int y = 0; y < vector_lens[i]; y++)
        {
            int v = 0;               
            fscanf(fin,"%d ", &v);           
            vectors[cnt] = v;                
            cnt ++;
        }

    }
}


void TestData:: print()
{
    printf("идентификатор: %s, пароль: %s, адрес: %s, порт: %d\n", uname, passwd, s_addr_str, sin_port);

    int cnt = 0;
    for (int i = 0; i < vector_n; i++)
    {
        printf("vector N%d, vector len %d: { ", i, vector_lens[i]);
        for (int y = 0; y < vector_lens[i]; y++)
        {
            printf("%d ", vectors[cnt]);
            cnt++;
        }
        printf("}\n");
    }
}

int TestData:: run_test()
{
    // Создание сокета
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        printf("Error: Ошибка при создании сокета\n");
            return 1;
    }

    // Настраиваем адрес сервера
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr((char*)s_addr_str);
    serverAddress.sin_port = htons(sin_port);

    
    if(connect(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0)
    {
        printf("Error: Ошибка при подключении\n");
        return 1;
    }

    send_recv();

    close(serverSocket);
    return 0;
}