#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include "../com/messagehandler.h"
#include "../com/protocol.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <map>

namespace client {

    class CommandHandler {
    public:
    	CommandHandler(){}
        void interpretAndPerformCmd(com::MessageHandler& msgHandler, std::string& cmdLine, const std::map<std::string, com::Protocol>& mymap) throw(com::IllegalCommandException, com::ConnectionClosedException);
    private:
        void listNg(com::MessageHandler& msgHandler) throw(com::IllegalCommandException, com::ConnectionClosedException);
        void createNg(com::MessageHandler& msgHandler, std::string string_param) throw(com::IllegalCommandException, com::ConnectionClosedException);
        void deleteNg(com::MessageHandler& msgHandler, std::string string_param) throw(com::IllegalCommandException, com::ConnectionClosedException);
        void listArt(com::MessageHandler& msgHandler, std::string string_param) throw(com::IllegalCommandException, com::ConnectionClosedException);
        void createArt(com::MessageHandler& msgHandler, int artID , std::string artTitle, std::string artAuthor, std::string artText) throw(com::IllegalCommandException, com::ConnectionClosedException);
        void deleteArt(com::MessageHandler& msgHandler, int groupID, int articleID) throw(com::IllegalCommandException, com::ConnectionClosedException);
        void getArt(com::MessageHandler& msgHandler, int groupID, int articleID) throw(com::IllegalCommandException, com::ConnectionClosedException);
    };
}
#endif