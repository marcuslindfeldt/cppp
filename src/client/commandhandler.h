#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include "../com/messagehandler.h"
#include "../com/protocol.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <stdexcept>

namespace client {

    class CommandHandler {
    public:
    	CommandHandler(com::MessageHandler& mh):mh(mh){}
    	// Parse command and perform appropriate action
    	bool perform(std::string& cmd) throw(com::IllegalCommandException, com::ConnectionClosedException, std::invalid_argument);
    private:
        void listNg() throw(com::ConnectionClosedException);
        void createNg(std::vector<std::string> args) throw(com::ConnectionClosedException);
        void deleteNg(std::vector<std::string> args) throw(com::ConnectionClosedException);
        void listArt(std::vector<std::string> args) throw(com::ConnectionClosedException, std::invalid_argument);
        void createArt(std::vector<std::string> args) throw(com::ConnectionClosedException, std::invalid_argument);
        void deleteArt(std::vector<std::string> args) throw(com::ConnectionClosedException, std::invalid_argument);
        void getArt(std::vector<std::string> args) throw(com::ConnectionClosedException, std::invalid_argument);
        com::MessageHandler& mh;
    };
}
#endif
