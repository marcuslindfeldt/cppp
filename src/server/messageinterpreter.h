#ifndef MESSAGE_INTERPRETER_H
#define MESSAGE_INTERPRETER_H

#include "../database/inmemorydatabase.h"
#include "../com/messagehandler.h"

namespace server {

    class MessageInterpreter {
        public:
            MessageInterpreter(com::MessageHandler mh, database::InMemoryDatabase db) : msgHandler(mh), database(db){}
            void interpretMessage(int code) throw(com::IllegalCommandException, com::ConnectionClosedException);
        private:
            com::MessageHandler msgHandler;
            database::InMemoryDatabase database;
            void listNg() throw(com::IllegalCommandException, com::ConnectionClosedException);
            void createNg() throw(com::IllegalCommandException, com::ConnectionClosedException);
            void deleteNg() throw(com::IllegalCommandException, com::ConnectionClosedException);
            void listArt() throw(com::IllegalCommandException, com::ConnectionClosedException);
            void createArt() throw(com::IllegalCommandException, com::ConnectionClosedException);
            void deleteArt() throw(com::IllegalCommandException, com::ConnectionClosedException);
            void getArt() throw(com::IllegalCommandException, com::ConnectionClosedException);

    };


}
#endif
