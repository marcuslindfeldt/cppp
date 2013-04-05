/*
 * CommandHandler.h
 *
 *  Created on: Apr 5, 2013
 *      Author: fladnag
 */

#ifndef COMMANDHANDLER_H_
#define COMMANDHANDLER_H_
#include "../com/messagehandler.h"
#include "../com/protocol.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

namespace client {

class CommandHandler {
public:
	CommandHandler(com::MessageHandler& mh); //constructor
	virtual ~CommandHandler();
            void interpretAndPerformCmd(std::string cmdLine) throw(com::IllegalCommandException, com::ConnectionClosedException);
private:
            void listNg() throw(com::IllegalCommandException, com::ConnectionClosedException);
            void createNg(std::string string_param) throw(com::IllegalCommandException, com::ConnectionClosedException);
            void deleteNg(std::string string_param) throw(com::IllegalCommandException, com::ConnectionClosedException);
            void listArt(std::string string_param) throw(com::IllegalCommandException, com::ConnectionClosedException);
            void createArt(int artID , std::string artTitle, std::string artAuthor, std::string artText) throw(com::IllegalCommandException, com::ConnectionClosedException);
            void deleteArt(int groupID, int articleID) throw(com::IllegalCommandException, com::ConnectionClosedException);
            void getArt(int groupID, int articleID) throw(com::IllegalCommandException, com::ConnectionClosedException);
            com::MessageHandler messageHandler;
    };


} /* End of name space client */
#endif /* COMMANDHANDLER_H_ */
