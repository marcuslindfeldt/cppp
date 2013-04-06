/*
 * CommandHandler.cpp
 *
 *  Created on: Apr 5, 2013
 *      Author: fladnag
 */

#include "commandhandler.h"

namespace client {

CommandHandler::CommandHandler(com::MessageHandler& mh) : messageHandler(mh){};
CommandHandler::~CommandHandler() {}

//TODO Sync this with the responses from the server side implementation

void CommandHandler::interpretAndPerformCmd(std::string theCmdLine, const std::map<std::string, com::Protocol>& mymap) throw(com::IllegalCommandException, com::ConnectionClosedException){
	/*
	 * This is being implemented with the notion of client commands being issued as:
	 * "commandtype arg1 arg2 arg3 ..argN"
	 */

	std::vector<std::string> arguments;
	std::istringstream inputSS(theCmdLine);
	std::copy(std::istream_iterator<std::string>(inputSS),
			std::istream_iterator<std::string>(),
			std::back_inserter<std::vector<std::string> >(arguments));

	if(arguments.size > 0){
		std::map< std::string, com::Protocol>::iterator it = mymap.find(arguments.at(0));
		if(it != mymap.end()){
			int protocolNbr =  it->second;
			switch(arguments.size()){
			case '1':
				switch(protocolNbr){
				case com::Protocol::COM_LIST_NG:
					listNg();
					break;
				default:
					throw com::IllegalCommandException;
				}
				break;

				case '2':
					std::string string_param = arguments.at(1);
					switch(protocolNbr){
					case com::Protocol::COM_CREATE_NG:
						createNg(string_param);
						break;
					case com::Protocol::COM_DELETE_NG:
						deleteNg(string_param);
						break;
					case com::Protocol::COM_LIST_ART:
						listArt(string_param);
						break;
					default:
						throw com::IllegalCommandException;
					}
					break;

					case '3':
						const char* grp = (arguments[1]);
						const char* art = (arguments[2]);
						switch(protocolNbr){
						case com::Protocol::COM_DELETE_ART:
							int grpID = atoi(grp);
							int artID = atoi(art);
							deleteArt(grpID, artID);
							break;
						case com::Protocol::COM_GET_ART:
							getArt(grpID, artID);
							break;
						default:
							throw com::IllegalCommandException;
						}
						break;
						case '4':
							switch(protocolNbr){
							case com::Protocol::COM_CREATE_ART:
								const char* id = arguments[1];
								int artID = atoi(id);
								createArt(artID, arguments[2],arguments[3],arguments[4]);
								break;
							default:
								throw com::IllegalCommandException;
							}
							break;
							default:
								throw com::IllegalCommandException;
			}
		}
	}
}

void CommandHandler::listNg() throw(com::IllegalCommandException, com::ConnectionClosedException){
	messageHandler.sendCode(com::Protocol::COM_LIST_NG);
	messageHandler.sendCode(com::Protocol::COM_END);

}
void CommandHandler::createNg(std::string string_param) throw(com::IllegalCommandException, com::ConnectionClosedException){
	messageHandler.sendCode(com::Protocol::COM_CREATE_NG);
	messageHandler.sendStringParameter(string_param);
	messageHandler.sendCode(com::Protocol::COM_END);
}
void CommandHandler::deleteNg(std::string string_param) throw(com::IllegalCommandException, com::ConnectionClosedException){
	messageHandler.sendCode(com::Protocol::COM_DELETE_NG);
	messageHandler.sendStringParameter(string_param);
	messageHandler.sendCode(com::Protocol::COM_END);
}
void CommandHandler::listArt(std::string string_param) throw(com::IllegalCommandException, com::ConnectionClosedException){
	messageHandler.sendCode(com::Protocol::COM_LIST_ART);
	messageHandler.sendStringParameter(string_param);
	messageHandler.sendCode(com::Protocol::COM_END);
}
void CommandHandler::createArt(int artID , std::string artTitle, std::string artAuthor, std::string artText) throw(com::IllegalCommandException, com::ConnectionClosedException){
	messageHandler.sendCode(com::Protocol::COM_CREATE_ART);
	messageHandler.sendIntParameter(artID);
	messageHandler.sendStringParameter(artTitle);
	messageHandler.sendStringParameter(artAuthor);
	messageHandler.sendStringParameter(artText);
	messageHandler.sendCode(com::Protocol::COM_END);
}
void CommandHandler::deleteArt(int groupID, int articleID) throw(com::IllegalCommandException, com::ConnectionClosedException){
	messageHandler.sendCode(com::Protocol::COM_DELETE_ART);
	messageHandler.sendIntParameter(groupID);
	messageHandler.sendIntParameter(articleID);
	messageHandler.sendCode(com::Protocol::COM_END);
}
void CommandHandler::getArt(int groupID, int articleID) throw(com::IllegalCommandException, com::ConnectionClosedException){
	messageHandler.sendCode(com::Protocol::COM_GET_ART);
	messageHandler.sendIntParameter(groupID);
	messageHandler.sendIntParameter(articleID);
	messageHandler.sendCode(com::Protocol::COM_END);
}


} /* namespace client */
