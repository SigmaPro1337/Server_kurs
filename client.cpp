#include "TestData.h"

using namespace std;


int main()
{
    FILE* fin =  fopen("client_data.conf", "r");
    int n_of_tests = 0;
    fscanf(fin,"%d\n", &n_of_tests);

    TestData test_client;

    printf("RUNNING TESTS\n");
    for(int i = 0; i < n_of_tests; i++)
    {
        printf("\nTEST N%d\n", i+1);
        test_client.read_data(fin);
        test_client.print();
        
        test_client.run_test();
    }

    fclose(fin); 
    return 0;
 }