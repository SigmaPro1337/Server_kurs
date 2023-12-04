all:
	g++ main.cpp Server.cpp UserDataBase.cpp User.cpp ErrorManager.cpp ./md5/md5.cpp -o Server -lcryptopp
test:
	g++ unittest.cpp Server.cpp UserDataBase.cpp User.cpp ErrorManager.cpp ./md5/md5.cpp -o Test -lcryptopp -lUnitTest++ 
clean:
	rm -f Server
