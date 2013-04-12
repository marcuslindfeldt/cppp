#ifndef MESSAGE_INTERPRETER_H
#define MESSAGE_INTERPRETER_H

#include "../database/database.h"
#include "../com/messagehandler.h"

namespace server {

    class MessageInterpreter {
        public:
            MessageInterpreter(com::MessageHandler& mh, database::Database* db):mh(mh),db(db){};
            void interpretAndPerformCmd() throw(com::IllegalCommandException, com::ConnectionClosedException);
        private:
            void listNg() throw(com::IllegalCommandException, com::ConnectionClosedException);
            void createNg() throw(com::IllegalCommandException, com::ConnectionClosedException);
            void deleteNg() throw(com::IllegalCommandException, com::ConnectionClosedException);
            void listArt() throw(com::IllegalCommandException, com::ConnectionClosedException);
            void createArt() throw(com::IllegalCommandException, com::ConnectionClosedException);
            void deleteArt() throw(com::IllegalCommandException, com::ConnectionClosedException);
            void getArt() throw(com::IllegalCommandException, com::ConnectionClosedException);
            com::MessageHandler& mh;
            database::Database* db;
    };
}
#endif