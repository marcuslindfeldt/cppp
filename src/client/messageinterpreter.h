#ifndef MESSAGE_INTERPRETER_H
#define MESSAGE_INTERPRETER_H

#include "../com/messagehandler.h"
#include <iostream>

namespace client {

    class MessageInterpreter {
        public:
            MessageInterpreter(){}
            std::ostream& interpretAnsAndBuildRes(com::MessageHandler& mh, std::ostream& out) throw(com::IllegalCommandException, com::ConnectionClosedException);
        private:
            std::ostream& listNg(com::MessageHandler& mh, std::ostream& out) throw(com::IllegalCommandException, com::ConnectionClosedException);
            std::ostream& createNg(com::MessageHandler& mh, std::ostream& out) throw(com::IllegalCommandException, com::ConnectionClosedException);
            std::ostream& deleteNg(com::MessageHandler& mh, std::ostream& out) throw(com::IllegalCommandException, com::ConnectionClosedException);
            std::ostream& listArt(com::MessageHandler& mh, std::ostream& out) throw(com::IllegalCommandException, com::ConnectionClosedException);
            std::ostream& createArt(com::MessageHandler& mh, std::ostream& out) throw(com::IllegalCommandException, com::ConnectionClosedException);
            std::ostream& deleteArt(com::MessageHandler& mh, std::ostream& out) throw(com::IllegalCommandException, com::ConnectionClosedException);
            std::ostream& getArt(com::MessageHandler& mh, std::ostream& out) throw(com::IllegalCommandException, com::ConnectionClosedException);
    };
}
#endif
