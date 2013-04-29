#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include "../com/messagehandler.h"
#include "../com/protocol.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>

namespace client {

    class CommandHandler {
    public:
    	CommandHandler(com::MessageHandler& mh):mh(mh){}
    	// Parse command and perform appropriate action
    	bool perform(std::string& cmd) throw(com::IllegalCommandException, com::ConnectionClosedException);
    private:
        void createNg(std::vector<std::string> args) throw(com::IllegalCommandException, com::ConnectionClosedException);
        void listNg() throw(com::IllegalCommandException, com::ConnectionClosedException);
        com::MessageHandler mh;
    };
}
#endif
