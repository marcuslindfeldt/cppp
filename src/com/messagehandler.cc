#include "messagehandler.h"
#include "protocol.h"


namespace com {

	/** 
	* private helper method 
	* send number ranging from 0-255
	*/
	void MessageHandler::sendByte(int byte) const
	{
		conn->write(static_cast<unsigned char>(byte));
	}

	/**
	 * Transmit a code (a constant form the Protocol class).
	 * @param code The code to transmit.
	 */
	void MessageHandler::sendCode(int code)
	{
		sendByte(code);
	}

	/**
	 * Transmit an int value, according to the protocol
	 * @param value The integer to transmitt
	 */
	void MessageHandler::sendInt(int value)
	{
	    sendByte((value >> 24) & 0xFF);
	    sendByte((value >> 16) & 0xFF);
	    sendByte((value >> 8)  & 0xFF);
	    sendByte(value & 0xFF);
	}

	/**
	 * Transmit an int parameter, according to the protocol.
	 * @param param The parameter to transmitt
	 */
	void MessageHandler::sendIntParameter(int param)
	{
		sendByte(Protocol::PAR_NUM);
		sendInt(param);
	}

	void MessageHandler::sendStringParameter(std::string param)
	{
		size_t len = param.length();
		sendCode(Protocol::PAR_STRING);
		sendInt(len);

		for (size_t i = 0; i < len ; ++i) {
			sendByte(param[i]);
		}
	}

	int MessageHandler::recvCode() const
	{
		return conn->read();
	}

	int MessageHandler::recvInt() const
	{
		unsigned char b1 = conn->read();
		unsigned char b2 = conn->read();
		unsigned char b3 = conn->read();
		unsigned char b4 = conn->read();

		return (b1 << 24) | (b2 << 16) | (b3 << 8) | b4;
	}

	int MessageHandler::recvIntParameter()
	{
		int code = recvCode();
		if(code != Protocol::PAR_NUM){
			throw ConnectionClosedException();
		}
		return recvInt();
	}

	const std::string MessageHandler::recvStringParameter()
	{
		int code = recvCode();
		if(code != Protocol::PAR_STRING){
			throw ConnectionClosedException();
		}
		int n = recvInt();
		if(n < 0){
			throw ConnectionClosedException();
		}
		std::string res;

		for(int i = 0; i < n; i++){
			res.push_back(conn->read());
		}
		return res;
	}
}
