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
    	void parse(std::string& cmd) throw(com::IllegalCommandException, com::ConnectionClosedException);
    private:
        com::MessageHandler mh;
    };
}
#endif
