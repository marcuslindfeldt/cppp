#ifndef MESSAGE_INTERPRETER_H
#define MESSAGE_INTERPRETER_H

#include "../database/inmemorydatabase.h"
#include "../com/messagehandler.h"

namespace server {

    class MessageInterpreter {
        public:
            MessageInterpreter(com::MessageHandler mh, database::InMemoryDatabase db) : msgHandler(mh), database(db){}
            void interpretMessage(int code);
        private:
            com::MessageHandler msgHandler;
            database::InMemoryDatabase database;
            void listNg();
            void createNg();
            void deleteNg();
            void listArt();
            void createArt();
            void deleteArt();
            void getArt();

    };


}
#endif
