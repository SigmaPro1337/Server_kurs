#include <UnitTest++/UnitTest++.h>
#include "Server.h"


using namespace std;

struct User_fix {
	User * p;
	User_fix() {
		p = new User();
	}
	~User_fix() {
		delete p;
	}
};

    // Модуль User.h

    // Ошибка идентификации
    TEST_FIXTURE(User_fix, SuccessfulIdentificatio){
        p->setLogin("user");
        auto resultat = p->CheckLogin({"user", "ivanov", "user0"});
        // Проверяем результат
        UNITTEST_CHECK_EQUAL(resultat, 1);
    }

    
    // Ошибка идентификации
    TEST_FIXTURE(User_fix, IdentificationError){
        p->setLogin("user");
        auto resultat = p->CheckLogin({"ivanov", "user0"});
        // Проверяем результат
        UNITTEST_CHECK_EQUAL(resultat, 0);
    }
    // Удачная аутентификация
    TEST_FIXTURE(User_fix, SuccessfulAuthentication){
        p->setLogin("user");
        p->setPassword("FADBE82AEAF87829E911A5AC223309C3");
        auto resultat = p->CheckPassword({"P@ssW0rd", "123456", "qwe123"}, {"user", "ivanov", "user0"}, "B050324A4A2D852F");
        // Проверяем результат
        UNITTEST_CHECK_EQUAL(resultat, 1);
    
    }

    // Ошибка аутентификации
    TEST_FIXTURE(User_fix, AuthenticationError){
        p->setLogin("user");
        p->setPassword("FADBE82AEAF87829E911A5AC223309C3");
        auto resultat = p->CheckPassword({"Pass", "123456", "qwe123"}, {"user", "ivanov", "user0"}, "B050324A4A2D852F");
        // Проверяем результат
        UNITTEST_CHECK_EQUAL(resultat, 0);
    }

struct ErrorManager_fix {
	ErrorManager * l;
	ErrorManager_fix() {
		l = new ErrorManager();
	}
	~ErrorManager_fix() {
		delete l;
	}
};

    // Ошибка открытия журнала
    TEST_FIXTURE(ErrorManager_fix, LogOpeningError){
        string substring = "Файл для записи ошибок не может быть открыт";
        CHECK_THROW(l->setlogFile("@/qwe/log.conf"), invalid_argument);
        
    }

struct UserDataBase_fix {
	UserDataBase * u;
	UserDataBase_fix() {
		u = new UserDataBase();
	}
	~UserDataBase_fix() {
		delete u;
	}
};

    // Ошибка открытия БД
    TEST_FIXTURE(UserDataBase_fix, DatabaseOpeningError){
        u->setClientDataBase("@/DB_client.conf");
        CHECK_THROW(u->getClientCredentials(), invalid_argument);
        
    }

    // Ошибка открытия БД
    TEST_FIXTURE(UserDataBase_fix, EmptyDatabaseFile){
        u->setClientDataBase("DB_None.conf");
        CHECK_THROW(u->getClientCredentials(), invalid_argument);
    }

    // Получение БД из файла
    TEST_FIXTURE(UserDataBase_fix, FetchingDatabaseFromFile){
        u->setClientDataBase("DB_client.conf");
        vector<std::string> second = {"P@ssW0rd", "123456", "qwe123"};
        vector<std::string> first = {"user", "ivanov", "user0"};

        auto resultat = u->getClientCredentials();

        vector<std::string> login = resultat.first;
        vector<std::string> password = resultat.second;

        if(first != login){
            CHECK(false);
        }

        if(second != password){
            CHECK(false);
        }

        CHECK(true);
    }

struct Server_fix {
	Server * s;
	Server_fix() {
		s = new Server();
	}
	~Server_fix() {
		delete s;
	}
};

    // Ошибка в адресе сервера
    TEST_FIXTURE(Server_fix, ServerAddressError){
        CHECK_THROW(s->setAddress("8.8.8.8"), invalid_argument);
    }
    // Ошибка в порту сервера
    TEST_FIXTURE(Server_fix, ServerPortError){
        CHECK_THROW(s->setPort("22"), invalid_argument);
    }
    // Перемножение элементов векторов
    TEST_FIXTURE(Server_fix, VectorElementsMultiplication){
        auto resultat = s->multiplyVectors({1, 2, 3, 4});
        UNITTEST_CHECK_EQUAL(resultat, 24);
    }

    // Переполнение вверх при перемножении элементов векторов
    TEST_FIXTURE(Server_fix, OverflowUpwardInVectorElementsMultiplication){
        auto resultat = s->multiplyVectors({8000, 10000, 12000, 12000});
        UNITTEST_CHECK_EQUAL(resultat, 2147483647);
    }


// Запускаем все тесты
int main(int argc, char **argv)
{
	return UnitTest::RunAllTests();
}