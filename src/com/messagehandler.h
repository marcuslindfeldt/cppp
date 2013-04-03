
#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <string>
#include "connection.h"

namespace com {
	class MessageHandler
	{
	public:
		MessageHandler(Connection c) : conn(c) {};
		~MessageHandler();
	
		void sendByte(int);
		void sendCode(int);
		void sendInt(int);
		void sendIntParameter(int);
		void sendStringParameter(std::string);
		int recvCode();
		int recvInt();
		int recvIntParameter();
		std::string& recvStringParameter();
	private:
		Connection conn;
	};
}

#endif
