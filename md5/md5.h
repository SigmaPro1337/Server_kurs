/** 
* @file md5.h
* @author Черный М.В.
* @version 1.0
* @date 31.10.2023
* @copyright ИБСТ ПГУ
* @brief Заголовочный файл для модуля md5
*/

#include <iostream>
#include <vector>

#include <cryptopp/hex.h> // HexEncoder

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <cryptopp/md5.h> // MD%, для другого алгоритма - другой заголовочный файл

std::string MD5_hash(std::string msg);