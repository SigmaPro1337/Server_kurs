#include <sys/types.h>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fstream>
#include <string>
#include "./md5/md5.h"

using namespace std;

class TestData
{
    private:
    char uname[1024] = {0};
    char passwd[1024] = {0};

    char s_addr_str[1024] = {0};
    int sin_port = {0};
    int serverSocket;
    
    uint32_t vector_n;
    uint32_t* vector_lens;
    uint32_t* vectors;

    int send_recv();

    public:

    void read_data(FILE* fin);
    void print();
    int run_test();
};