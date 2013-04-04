#ifndef MESSAGE_INTERPRETER_H
#define MESSAGE_INTERPRETER_H

#include "../database/inmemorydatabase.h"
#include "../com/messagehandler.h"

namespace server {

    class MessageInterpreter {
        public:
            MessageInterpreter(){}
            void interpretAndPerformCmd(com::MessageHandler& mh, database::Database& db) throw(com::IllegalCommandException, com::ConnectionClosedException);
        private:
            void listNg(com::MessageHandler& mh, database::Database& db) throw(com::IllegalCommandException, com::ConnectionClosedException);
            void createNg(com::MessageHandler& mh, database::Database& db) throw(com::IllegalCommandException, com::ConnectionClosedException);
            void deleteNg(com::MessageHandler& mh, database::Database& db) throw(com::IllegalCommandException, com::ConnectionClosedException);
            void listArt(com::MessageHandler& mh, database::Database& db) throw(com::IllegalCommandException, com::ConnectionClosedException);
            void createArt(com::MessageHandler& mh, database::Database& db) throw(com::IllegalCommandException, com::ConnectionClosedException);
            void deleteArt(com::MessageHandler& mh, database::Database& db) throw(com::IllegalCommandException, com::ConnectionClosedException);
            void getArt(com::MessageHandler& mh, database::Database& db) throw(com::IllegalCommandException, com::ConnectionClosedException);

    };


}
#endif
