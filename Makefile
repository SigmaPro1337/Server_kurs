all:
	g++ main.cpp Server.cpp UserDataBase.cpp User.cpp ErrorManager.cpp ./md5/md5.cpp -o Server -lcryptopp
clean:
	rm -f Server
