#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include "connection.h"
#include <string>

namespace com {
	struct IllegalCommandException {};

	class MessageHandler {
	public:
		MessageHandler(Connection& c) : conn(c) {};
		void sendCode(int) throw(ConnectionClosedException);
		void sendInt(int) throw(ConnectionClosedException);
		void sendIntParameter(int) throw(ConnectionClosedException);
		void sendStringParameter(std::string) throw(ConnectionClosedException);
		int recvCode() const throw(ConnectionClosedException);
		int recvInt() const throw(ConnectionClosedException);
		int recvIntParameter() throw(IllegalCommandException, ConnectionClosedException);
		const std::string recvStringParameter() throw(IllegalCommandException, ConnectionClosedException);
	private:
		void sendByte(int) const throw(ConnectionClosedException);
		Connection conn;
	};
}
#endif
