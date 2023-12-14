#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>

enum Status
{
	FIRST_LINE,
	HEADERS,
	BODY,
	DONE
}

class Request {
	private:
		std::string _method;
		std::string _version;
		std::string _uri;
		std::string _query;
		std::map<std::string, std::string> _headers;
		std::string _body;
		std::string _request;
		bool _start;
		Status _status;
	
	public:
		Request(const std::string &request);
		~Request();
		Request(const Request &src);
		Request &operator=(const Request &src);
		void parse(std::string &requestChunk);
		void parseRequestLine(const std::string &requestLine);
		void parseHeaders(const std::string &headers);
		void removeWhiteSpaces(const std::string &str);
}


#endif