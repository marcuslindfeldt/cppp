#include "messageinterpreter.h"
#include "../com/protocol.h"
#include <string>

using namespace com;
using namespace std;

namespace client {

    void MessageInterpreter::interpretAnsAndBuildRes(MessageHandler& msgHandler, ostream& out) throw(IllegalCommandException, ConnectionClosedException) {
        int code = msgHandler.recvCode();
        switch (code) {
            case Protocol::ANS_LIST_NG:
                listNg(msgHandler,out);
                break;
            case Protocol::ANS_CREATE_NG:
                createNg(msgHandler,out);
                break;
            case Protocol::ANS_DELETE_NG:
                deleteNg(msgHandler,out);
                break;
            case Protocol::ANS_LIST_ART:
                listArt(msgHandler,out);
                break;
            case Protocol::ANS_CREATE_ART:
                createArt(msgHandler,out);
                break;
            case Protocol::ANS_DELETE_ART:
                deleteArt(msgHandler,out);
                break;
            case Protocol::ANS_GET_ART:
                getArt(msgHandler,out);
                break;
            default:
                throw IllegalCommandException();
        }
    }

    void MessageInterpreter::listNg(MessageHandler& msgHandler, ostream& out) throw(IllegalCommandException, ConnectionClosedException) {
        int nbrRows = msgHandler.recvIntParameter();
        if (nbrRows > 0) {
            for(int i = 0; i < nbrRows; ++i) {
                out << msgHandler.recvIntParameter() << ". " << msgHandler.recvStringParameter() << endl;
            }
        } else {
            out << "No Newsgroups." << endl;
        }
        if(msgHandler.recvCode() != Protocol::ANS_END) throw IllegalCommandException();
    }

    void MessageInterpreter::createNg(MessageHandler& msgHandler, ostream& out) throw(IllegalCommandException, ConnectionClosedException) {
        if(msgHandler.recvCode() == Protocol::ANS_ACK) {
            out << "Newsgroup was successfully created." << endl;
        } else {
            out << "ERROR " << msgHandler.recvCode() << ": Newsgroup already exists.";
        }
        if(msgHandler.recvCode() != Protocol::ANS_END) throw IllegalCommandException();
    }

    void MessageInterpreter::deleteNg(MessageHandler& msgHandler, ostream& out) throw(IllegalCommandException, ConnectionClosedException) {
        if(msgHandler.recvCode() == Protocol::ANS_ACK) {
            out << "Newsgroup was successfully deleted." << endl;
        } else {
            out << "ERROR " << msgHandler.recvCode() << ": Newsgroup does not exist.";
        }
        if(msgHandler.recvCode() != Protocol::ANS_END) throw IllegalCommandException();
    }

    void MessageInterpreter::listArt(MessageHandler& msgHandler, ostream& out) throw(IllegalCommandException, ConnectionClosedException) {
        if(msgHandler.recvCode() == Protocol::ANS_ACK) {
            int nbrRows = msgHandler.recvIntParameter();
            if (nbrRows > 0) {
                for(int i = 0; i < nbrRows; ++i) {
                    out << msgHandler.recvIntParameter() << ". " << msgHandler.recvStringParameter() << endl;
                }
            } else {
                out << "No Articles." << endl;
            }
        } else {
            out << "ERROR " << msgHandler.recvCode() << ": Newsgroup does not exist.";
        }
        if(msgHandler.recvCode() != Protocol::ANS_END) throw IllegalCommandException();
    }

    void MessageInterpreter::createArt(MessageHandler& msgHandler, ostream& out) throw(IllegalCommandException, ConnectionClosedException) {
        if(msgHandler.recvCode() == Protocol::ANS_ACK) {
            out << "Article was successfully created." << endl;
        } else {
            out << "ERROR " << msgHandler.recvCode() << ": Newsgroup does not exist.";
        }
        if(msgHandler.recvCode() != Protocol::ANS_END) throw IllegalCommandException();
    }

    void MessageInterpreter::deleteArt(MessageHandler& msgHandler, ostream& out) throw(IllegalCommandException, ConnectionClosedException) {
        if(msgHandler.recvCode() == Protocol::ANS_ACK) {
            out << "Article was successfully deleted." << endl;
        } else {
            int code = msgHandler.recvCode();
            if(code == Protocol::ERR_NG_DOES_NOT_EXIST) {
                out << "ERROR " << code << ": Newsgroup does not exist.";
            } else {
                out << "ERROR " << code << ": Article does not exist.";
            }
        }
        if(msgHandler.recvCode() != Protocol::ANS_END) throw IllegalCommandException();
    }

    void MessageInterpreter::getArt(MessageHandler& msgHandler, ostream& out) throw(IllegalCommandException, ConnectionClosedException) {
        if(msgHandler.recvCode() == Protocol::ANS_ACK) {
            out << "Title: " << msgHandler.recvStringParameter() << endl << "Author: " << msgHandler.recvStringParameter() << endl << msgHandler.recvStringParameter();
        } else {
            int code = msgHandler.recvCode();
            if(code == Protocol::ERR_NG_DOES_NOT_EXIST) {
                out << "ERROR " << code << ": Newsgroup does not exist.";
            } else {
                out << "ERROR " << code << ": Article does not exist.";
            }
        }
        if(msgHandler.recvCode() != Protocol::ANS_END) throw IllegalCommandException();
    }
}