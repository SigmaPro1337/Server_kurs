all:
	g++ main.cpp Server.cpp UserDataBase.cpp User.cpp ErrorManager.cpp ./md5/md5.cpp -o Server -lcryptopp
unittest:
	g++ unittest.cpp Server.cpp UserDataBase.cpp User.cpp ErrorManager.cpp ./md5/md5.cpp -o Test -lcryptopp -lUnitTest++ 
clienttest:
	g++ client.cpp TestData.cpp ./md5/md5.cpp -o ClientTest -lcryptopp
clean:
	rm -f Server
