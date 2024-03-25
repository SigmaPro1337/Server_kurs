#!/bin/bash

# 1-ый тестовый сценарий
printf "Применение программы без аргументов\n"
./Server

# 2-ый тестовый сценарий
printf "Применение программы с флагом -h\n"
./Server -h

# 3-ый тестовый сценарий
printf "Применение программы с полным набором необходимых параметров\n"
./Server -i127.0.0.1 -p33333 -dDB_client.conf -llog.conf