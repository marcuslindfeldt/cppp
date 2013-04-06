#include "commandhandler.h"

using namespace std;
using namespace com;

namespace client {

	//TODO Sync this with the responses from the server side implementation

	void CommandHandler::interpretAndPerformCmd(MessageHandler& msgHandler, string& theCmdLine, const map<string, Protocol>& mymap) throw(IllegalCommandException, ConnectionClosedException){
		/*
		 * This is being implemented with the notion of client commands being issued as:
		 * "commandtype arg1 arg2 arg3 ..argN"
		 */

		vector<string> arguments;
		istringstream inputSS(theCmdLine);
		copy(istream_iterator<string>(inputSS),
				istream_iterator<string>(),
				back_inserter<vector<string> >(arguments));

		if(arguments.size > 0) {
			map<string, Protocol>::iterator it = mymap.find(arguments.at(0));
			if(it != mymap.end()){
				int protocolNbr =  it->second;
				switch(arguments.size()){
				case '1':
					switch(protocolNbr){
						case Protocol::COM_LIST_NG:
							listNg(msgHandler);
							break;
						default:
							throw IllegalCommandException;
							break;
					}
					break;
				case '2':
					string string_param = arguments.at(1);
					switch(protocolNbr) {
						case Protocol::COM_CREATE_NG:
							createNg(msgHandler, string_param);
							break;
						case Protocol::COM_DELETE_NG:
							deleteNg(msgHandler, string_param);
							break;
						case Protocol::COM_LIST_ART:
							listArt(msgHandler, string_param);
							break;
						default:
							throw IllegalCommandException;
							break;
					}
					break;
				case '3':
					const char* grp = (arguments[1]);
					const char* art = (arguments[2]);
					switch(protocolNbr) {
						case Protocol::COM_DELETE_ART:
							int grpID = atoi(grp);
							int artID = atoi(art);
							deleteArt(msgHandler, grpID, artID);
							break;
						case Protocol::COM_GET_ART:
							getArt(msgHandler, grpID, artID);
							break;
						default:
							throw IllegalCommandException;
							break;
					}
					break;
				case '4':
					switch(protocolNbr) {
						case Protocol::COM_CREATE_ART:
							const char* id = arguments[1];
							int artID = atoi(id);
							createArt(msgHandler, artID, arguments[2],arguments[3],arguments[4]);
							break;
						default:
							throw IllegalCommandException;
							break;
					}
					break;
				default:
					throw IllegalCommandException;
					break;
				}
			}
		}
	}

	void CommandHandler::listNg(MessageHandler& msgHandler) throw(IllegalCommandException, ConnectionClosedException) {
		msgHandler.sendCode(Protocol::COM_LIST_NG);
		msgHandler.sendCode(Protocol::COM_END);
	}

	void CommandHandler::createNg(MessageHandler& msgHandler, string& string_param) throw(IllegalCommandException, ConnectionClosedException) {
		msgHandler.sendCode(Protocol::COM_CREATE_NG);
		msgHandler.sendStringParameter(string_param);
		msgHandler.sendCode(Protocol::COM_END);
	}

	void CommandHandler::deleteNg(MessageHandler& msgHandler, string& string_param) throw(IllegalCommandException, ConnectionClosedException) {
		msgHandler.sendCode(Protocol::COM_DELETE_NG);
		msgHandler.sendStringParameter(string_param);
		msgHandler.sendCode(Protocol::COM_END);
	}

	void CommandHandler::listArt(MessageHandler& msgHandler, string& string_param) throw(IllegalCommandException, ConnectionClosedException) {
		msgHandler.sendCode(Protocol::COM_LIST_ART);
		msgHandler.sendStringParameter(string_param);
		msgHandler.sendCode(Protocol::COM_END);
	}

	void CommandHandler::createArt(MessageHandler& msgHandler, int artID , string& artTitle, string& artAuthor, string& artText) throw(IllegalCommandException, ConnectionClosedException) {
		msgHandler.sendCode(Protocol::COM_CREATE_ART);
		msgHandler.sendIntParameter(artID);
		msgHandler.sendStringParameter(artTitle);
		msgHandler.sendStringParameter(artAuthor);
		msgHandler.sendStringParameter(artText);
		msgHandler.sendCode(Protocol::COM_END);
	}

	void CommandHandler::deleteArt(MessageHandler& msgHandler, int groupID, int articleID) throw(IllegalCommandException, ConnectionClosedException) {
		msgHandler.sendCode(Protocol::COM_DELETE_ART);
		msgHandler.sendIntParameter(groupID);
		msgHandler.sendIntParameter(articleID);
		msgHandler.sendCode(Protocol::COM_END);
	}

	void CommandHandler::getArt(MessageHandler& msgHandler, int groupID, int articleID) throw(IllegalCommandException, ConnectionClosedException) {
		msgHandler.sendCode(Protocol::COM_GET_ART);
		msgHandler.sendIntParameter(groupID);
		msgHandler.sendIntParameter(articleID);
		msgHandler.sendCode(Protocol::COM_END);
	}
}