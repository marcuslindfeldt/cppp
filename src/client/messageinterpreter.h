#ifndef MESSAGE_INTERPRETER_H
#define MESSAGE_INTERPRETER_H

#include "../com/messagehandler.h"
#include <iostream>

namespace client {

    class MessageInterpreter {
        public:
            MessageInterpreter(){}
            void interpretAnsAndBuildRes(com::MessageHandler& mh, std::ostream& out) throw(com::IllegalCommandException, com::ConnectionClosedException);
        private:
            void listNg(com::MessageHandler& mh, std::ostream& out) throw(com::IllegalCommandException, com::ConnectionClosedException);
            void createNg(com::MessageHandler& mh, std::ostream& out) throw(com::IllegalCommandException, com::ConnectionClosedException);
            void deleteNg(com::MessageHandler& mh, std::ostream& out) throw(com::IllegalCommandException, com::ConnectionClosedException);
            void listArt(com::MessageHandler& mh, std::ostream& out) throw(com::IllegalCommandException, com::ConnectionClosedException);
            void createArt(com::MessageHandler& mh, std::ostream& out) throw(com::IllegalCommandException, com::ConnectionClosedException);
            void deleteArt(com::MessageHandler& mh, std::ostream& out) throw(com::IllegalCommandException, com::ConnectionClosedException);
            void getArt(com::MessageHandler& mh, std::ostream& out) throw(com::IllegalCommandException, com::ConnectionClosedException);
    };
}
#endif