#include "messageinterpreter.h"
#include "../com/protocol.h"
#include <string>
#include <iostream>
using namespace com;
using namespace std;

namespace client {

ostream& MessageInterpreter::interpretAnsAndBuildRes(MessageHandler& msgHandler, ostream& out) throw(IllegalCommandException, ConnectionClosedException) {
	int code = msgHandler.recvCode();
	switch (code) {
	case Protocol::ANS_LIST_NG:
		listNg(msgHandler,out);
		break;
	case Protocol::ANS_CREATE_NG:
		createNg(msgHandler,out);
		break;
	case Protocol::ANS_DELETE_NG:
		deleteNg(msgHandler,out);
		break;
	case Protocol::ANS_LIST_ART:
		listArt(msgHandler,out);
		break;
	case Protocol::ANS_CREATE_ART:
		createArt(msgHandler,out);
		break;
	case Protocol::ANS_DELETE_ART:
		deleteArt(msgHandler,out);
		break;
	case Protocol::ANS_GET_ART:
		getArt(msgHandler,out);
		break;
	default:
		throw IllegalCommandException();
	}
	return out;
}

ostream& MessageInterpreter::listNg(MessageHandler& msgHandler, ostream& out) throw(IllegalCommandException, ConnectionClosedException) {
	int nbrRows = msgHandler.recvIntParameter();
	if (nbrRows > 0) {
		for(int i = 0; i < nbrRows; ++i) {
			int k = msgHandler.recvIntParameter();
			string str = msgHandler.recvStringParameter(); // cant call these functions in a stream.
			out <<  k << ". " << str << endl; // Important to follow the convention in messageHandler for dataflow!!
		}
	} else {
		out << "No Newsgroups." << endl;
	}
	if(msgHandler.recvCode() != Protocol::ANS_END) throw IllegalCommandException();
	return out;
}

ostream& MessageInterpreter::createNg(MessageHandler& msgHandler, ostream& out) throw(IllegalCommandException, ConnectionClosedException) {
	if(msgHandler.recvCode() == Protocol::ANS_ACK) {
		out << "Newsgroup was successfully created." << endl;
	} else {
		int k = msgHandler.recvCode();
		out << "ERROR " << k << ": Newsgroup already exists." << endl;
	}
	if(msgHandler.recvCode() != Protocol::ANS_END) throw IllegalCommandException();
	return out;
}

ostream& MessageInterpreter::deleteNg(MessageHandler& msgHandler, ostream& out) throw(IllegalCommandException, ConnectionClosedException) {
	if(msgHandler.recvCode() == Protocol::ANS_ACK) {
		out << "Newsgroup was successfully deleted." << endl;
	} else {
		int k = msgHandler.recvCode();
		out << "ERROR " << k << ": Newsgroup does not exist." << endl;
	}
	if(msgHandler.recvCode() != Protocol::ANS_END) throw IllegalCommandException();
	return out;
}

ostream& MessageInterpreter::listArt(MessageHandler& msgHandler, ostream& out) throw(IllegalCommandException, ConnectionClosedException) {
	if(msgHandler.recvCode() == Protocol::ANS_ACK) {
		int nbrRows = msgHandler.recvIntParameter();
		if (nbrRows > 0) {
			for(int i = 0; i < nbrRows; ++i) {
				 int k = msgHandler.recvIntParameter();
				string str = msgHandler.recvStringParameter();
				out << k << ". " << str << endl;
			}
		} else {
			out << "No Articles." << endl;
		}
	} else {
		out << "ERROR " << msgHandler.recvCode() << ": Newsgroup does not exist." << endl;
	}
	if(msgHandler.recvCode() != Protocol::ANS_END) throw IllegalCommandException();
	return out;
}

ostream& MessageInterpreter::createArt(MessageHandler& msgHandler, ostream& out) throw(IllegalCommandException, ConnectionClosedException) {
	int k = msgHandler.recvCode();
	if(k == Protocol::ANS_ACK) {
		out << "Article was successfully created." << endl;
	} else {
		out << "ERROR "  << ": Newsgroup does not exist." << endl;
	}
	if(msgHandler.recvCode() != Protocol::ANS_END) throw IllegalCommandException();
	return out;
}

ostream& MessageInterpreter::deleteArt(MessageHandler& msgHandler, ostream& out) throw(IllegalCommandException, ConnectionClosedException) {
	if(msgHandler.recvCode() == Protocol::ANS_ACK) {
		out << "Article was successfully deleted." << endl;
	} else {
		int code = msgHandler.recvCode();
		if(code == Protocol::ERR_NG_DOES_NOT_EXIST) {
			out << "ERROR " << code << ": Newsgroup does not exist." << endl;
		} else {
			out << "ERROR " << code << ": Article does not exist." << endl;
		}
	}
	if(msgHandler.recvCode() != Protocol::ANS_END) throw IllegalCommandException();
	return out;
}

ostream& MessageInterpreter::getArt(MessageHandler& msgHandler, ostream& out) throw(IllegalCommandException, ConnectionClosedException) {
	if(msgHandler.recvCode() == Protocol::ANS_ACK) {
		string title = msgHandler.recvStringParameter();
		string author = msgHandler.recvStringParameter();
		out << "Title: " << title << endl << "Author: " << author << endl << msgHandler.recvStringParameter() << endl;
	} else {
		int code = msgHandler.recvCode();
		if(code == Protocol::ERR_NG_DOES_NOT_EXIST) {
			out << "ERROR " << code << ": Newsgroup does not exist." << endl;
		} else {
			out << "ERROR " << code << ": Article does not exist." << endl;
		}
	}
	if(msgHandler.recvCode() != Protocol::ANS_END) throw IllegalCommandException();
	return out;
}
}
