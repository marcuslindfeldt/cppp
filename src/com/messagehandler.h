
#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include "connection.h"
#include <string>

namespace com {
	class MessageHandler
	{
	public:
		MessageHandler(Connection& c) : conn(c) {};
		~MessageHandler();
	
		void sendCode(int);
		void sendInt(int);
		void sendIntParameter(int);
		void sendStringParameter(std::string);
		const int recvCode() const;
		const int recvInt() const;
		const int recvIntParameter();
		const std::string recvStringParameter();
	private:
		void sendByte(int) const;
		Connection conn;
	};
}

#endif
