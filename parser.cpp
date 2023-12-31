#include "parser.hpp"

void handleRequest(int clientSocket)
{
	// ssize_t recv(int socket, void *buffer, size_t length, int flags);
	// The recv() (recieve) function is normally used only on a connected socket.
	// If no messages are available at the socket, the receive call waits for a message to arrive, unless the socket is nonblocking
	// in which case the value -1 is returned and the external variable errno set to EAGAIN.

	// Stream-Based: Sockets in TCP, which is a stream-oriented protocol, provide a continuous stream of data. 
	// The recv function reads data from this stream, and it's the responsibility of the operating system
	//  to maintain the current position within that stream.

	char buff[200];
	ssize_t bytesRead;
	std::string header;
	std::string body;
	while((bytesRead = recv(clientSocket, buff, sizeof(buff), 0)) != 0)
	{
		if (bytesRead == -1)
			throw std::runtime_error("Error! Couldn't read from the socket.");
		header += std::string(buff, bytesRead);
		if (header.find("\r\n\r\n") != std::string::npos || header.find("\n\n") != std::string::npos)
			break;
	}
	header = removeWhiteSpaces(header);
	std::string method = header.substr(0, header.find(" "));
	if (method == "GET")
		std::cout << header << std::endl;
	else if (method == "POST")
		std::cout << header << std::endl;
	else if (method == "DELETE")
		std::cout << header << std::endl;
	else
		throw std::runtime_error("Error! Invalid method.");

	// Send a simple response
    std::string response = "HTTP/1.1 200 OK\r\nContent-Length: 12\r\n\r\nHello, World!";
    send(clientSocket, response.c_str(), response.size(), 0);

    close(clientSocket);
}
