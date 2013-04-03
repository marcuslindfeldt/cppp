#include "messagehandler.h"
#include "connection.h"

namespace com {

	void MessageHandler::sendByte(int)
	{

	}

	void MessageHandler::sendCode(int)
	{

	}

	void MessageHandler::sendInt(int value)
	{
	    conn.write((value >> 24) & 0xFF);
	    conn.write((value >> 16) & 0xFF);
	    conn.write((value >> 8)  & 0xFF);
	    conn.write(value & 0xFF);
	}

	void MessageHandler::sendIntParameter(int)
	{

	}

	void MessageHandler::sendStringParameter(std::string)
	{

	}

	int MessageHandler::recvCode()
	{

	}

	int MessageHandler::recvInt()
	{

	}

	int MessageHandler::recvIntParameter()
	{

	}

	std::string& MessageHandler::recvStringParameter()
	{

	}
}
