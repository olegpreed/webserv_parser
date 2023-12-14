#include "Request.hpp"

Request::~Request() 
{
	_status = REQUEST_LINE;
};

Request::Request(const Request &src) {};

Request::Request &operator=(const Request &src) {};

void removeFirstWhiteSpaces(std::string &requestChunk)
{
	size_t posStart = 0;
	size_t posEnd = header.size() - 1;
	while (posStart < posEnd && isspace(header[posStart]))
		posStart++;
	requestChunk = requestChunk.substr(posStart, posEnd + 1);
}

void Request::parse(std::string &requestChunk)
{
	if (_start)
	{
		removeFirstWhiteSpaces(requestChunk);
		_start = false;
	}

}


