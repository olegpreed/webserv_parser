#include <sstream>
#include <thread>
#include <chrono>
#include <cstdlib>

#include <unistd.h>
#include <arpa/inet.h>
#include "header.hpp"

int main()
{

	// Create socket
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1)
	{
		std::cerr << "Failed to create socket\n";
		return EXIT_FAILURE;
	}

	// Bind to port
	sockaddr_in serverAddr{};
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(PORT);
	if (bind(serverSocket, reinterpret_cast<sockaddr *>(&serverAddr), sizeof(serverAddr)) == -1)
	{
		std::cerr << "Failed to bind to port " << PORT << "\n";
		close(serverSocket);
		return EXIT_FAILURE;
	}

	// Listen for incoming connections
	if (listen(serverSocket, SOMAXCONN) == -1)
	{
		std::cerr << "Failed to listen for connections\n";
		close(serverSocket);
		return EXIT_FAILURE;
	}

	std::cout << "Server listening on port " << PORT << "\n";

	while (true)
	{
		sockaddr_in clientAddr{};
		socklen_t clientAddrLen = sizeof(clientAddr);

		// Accept connection
		int clientSocket = accept(serverSocket, reinterpret_cast<sockaddr *>(&clientAddr), &clientAddrLen);
		if (clientSocket == -1)
		{
			std::cerr << "Failed to accept connection\n";
			continue;
		}

		// Handle request in a separate thread
		std::thread(handleRequest, clientSocket).detach();
	}

	return EXIT_SUCCESS;
}
