#ifndef MESSAGE_INTERPRETER_H
#define MESSAGE_INTERPRETER_H

#include "../database/inmemorydatabase.h"
#include "../com/messagehandler.h"
#include "../com/connectionclosedexception.h"

namespace server {

    class MessageInterpreter {
        public:
            MessageInterpreter(com::MessageHandler mh, database::InMemoryDatabase db) : msgHandler(mh), database(db){}
            void interpretMessage(int code) throw(com::ConnectionClosedException);
        private:
            com::MessageHandler msgHandler;
            database::InMemoryDatabase database;
            void listNg();
            void createNg() throw(com::ConnectionClosedException);
            void deleteNg() throw(com::ConnectionClosedException);
            void listArt() throw(com::ConnectionClosedException);
            void createArt() throw(com::ConnectionClosedException);
            void deleteArt() throw(com::ConnectionClosedException);
            void getArt() throw(com::ConnectionClosedException);

    };


}
#endif
