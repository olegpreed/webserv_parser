#ifndef HEADER_HPP
#define HEADER_HPP

#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <cctype>

#define PORT 8080

void handleRequest(int clientSocket);

#endif