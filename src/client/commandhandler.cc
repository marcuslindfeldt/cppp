#include "commandhandler.h"

using namespace std;
using namespace com;

namespace client {

	//TODO Sync this with the responses from the server side implementation

void CommandHandler::interpretAndPerformCmd(com::MessageHandler& msgHandler, std::string& cmdLine, const std::map<std::string, int>& mymap, const char& delim) throw(com::IllegalCommandException, com::ConnectionClosedException){
		/*
		 * This is being implemented with the notion of client commands being issued as:
		 * "commandtype arg1 arg2 arg3 ..argN"
		 */


		stringstream inputSS(cmdLine);
		string subStr;
		while (getline(inputSS, subStr, delim)) {
		        arguments.push_back(subStr);
		    }
		/*
		copy(istream_iterator<string>(inputSS),
				istream_iterator<string>(),
				back_inserter<vector<string> >(arguments));
				*/
		if(arguments.size() > 0) {
			map<string, int>::const_iterator it = mymap.find(arguments.at(0));
			if(it != mymap.end()){
				int protocolNbr =  it->second;
				string stringParam;
				const char* grp;
				const char* art;
				const char* id;
				int grpID;
				int artID;
				switch(arguments.size()){
				case 1:
					switch(protocolNbr){
						case Protocol::COM_LIST_NG:
							listNg(msgHandler);
							break;
						default:
							//throw IllegalCommandException;
							break;
					}
					break;
				case 2:
					 stringParam = arguments.at(1);
					switch(protocolNbr) {
						case Protocol::COM_CREATE_NG:
							createNg(msgHandler, stringParam);
							break;
						case Protocol::COM_DELETE_NG:
							deleteNg(msgHandler, stringParam);
							break;
						case Protocol::COM_LIST_ART:
							listArt(msgHandler, stringParam);
							break;
						default:
							//throw IllegalCommandException;
							break;
					}
					break;
				case 3:
					grp = (arguments[1]).c_str();
					art = (arguments[2]).c_str();
					grpID = atoi(grp);
					artID = atoi(art);
					switch(protocolNbr) {
					case Protocol::COM_DELETE_ART:
						deleteArt(msgHandler, grpID, artID);
						break;
					case Protocol::COM_GET_ART:
						getArt(msgHandler, grpID, artID);
						break;
					default:
						//throw IllegalCommandException;
							break;
					}
					break;
				case 4:
					switch(protocolNbr) {
						case Protocol::COM_CREATE_ART:
							id = arguments[1].c_str();
							artID = atoi(id);
							createArt(msgHandler, artID, arguments[2],arguments[3],arguments[4]);
							break;
						default:
							//throw IllegalCommandException;
							break;
					}
					break;
				default:
					//throw IllegalCommandException;
					break;
				}
				arguments.erase(arguments.begin(), arguments.end());
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
