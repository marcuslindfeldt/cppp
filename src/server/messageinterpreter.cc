#include "messageinterpreter.h"
#include "../com/protocol.h"
#include <string>
#include <map>
#include <iostream>

using namespace database;
using namespace com;
using namespace std;

namespace server {

    void MessageInterpreter::interpretAndPerformCmd(MessageHandler& msgHandler, Database& database) throw(IllegalCommandException, ConnectionClosedException) {
        int code = msgHandler.recvCode();
        switch(code){
            case Protocol::COM_LIST_NG:
                listNg(msgHandler,database);
                break;
            case Protocol::COM_CREATE_NG:
                createNg(msgHandler,database);
                break;
            case Protocol::COM_DELETE_NG:
                deleteNg(msgHandler,database);
                break;
            case Protocol::COM_LIST_ART:
                listArt(msgHandler,database);
                break;
            case Protocol::COM_CREATE_ART:
                createArt(msgHandler,database);
                break;
            case Protocol::COM_DELETE_ART:
                deleteArt(msgHandler,database);
                break;
            case Protocol::COM_GET_ART:
                getArt(msgHandler,database);
                break;
            default:
                throw IllegalCommandException();
                break;
        }
        msgHandler.sendCode(Protocol::ANS_END);
    }

    void MessageInterpreter::listNg(MessageHandler& msgHandler, Database& database) throw(IllegalCommandException, ConnectionClosedException) {
        if(msgHandler.recvCode() != Protocol::COM_END) throw IllegalCommandException();
        map<size_t, Newsgroup> ngs = database.listNewsgroups();
        msgHandler.sendCode(Protocol::ANS_LIST_NG);
        msgHandler.sendIntParameter(ngs.size());
        for(map<size_t, Newsgroup>::iterator it = ngs.begin(); it != ngs.end(); ++it) {
            msgHandler.sendIntParameter(it->first);
            msgHandler.sendStringParameter(it->second.getName());
        }
    }

    void MessageInterpreter::createNg(MessageHandler& msgHandler, Database& database) throw(IllegalCommandException, ConnectionClosedException) {
        string name = msgHandler.recvStringParameter();
        if(msgHandler.recvCode() != Protocol::COM_END) throw IllegalCommandException();
        msgHandler.sendCode(Protocol::ANS_CREATE_NG);
        if(!database.createNewsgroup(name)) {
            msgHandler.sendCode(Protocol::ANS_NAK);
        }else{
        msgHandler.sendCode(Protocol::ANS_ACK);
        }
    }

    void MessageInterpreter::deleteNg(MessageHandler& msgHandler, Database& database) throw(IllegalCommandException, ConnectionClosedException) {
        int id = msgHandler.recvIntParameter();
        if(msgHandler.recvCode() != Protocol::COM_END) throw IllegalCommandException();
        msgHandler.sendCode(Protocol::ANS_DELETE_NG);
        msgHandler.sendCode(database.deleteNewsgroup(id) ? Protocol::ANS_ACK : Protocol::ANS_NAK); 
    }

    void MessageInterpreter::listArt(MessageHandler& msgHandler, Database& database) throw(IllegalCommandException, ConnectionClosedException) {
        int id = msgHandler.recvIntParameter();
        if(msgHandler.recvCode() != Protocol::COM_END) throw IllegalCommandException();
        msgHandler.sendCode(Protocol::ANS_LIST_ART);
        try {
            map<size_t, Article> arts = database.listArticles(id);
            msgHandler.sendCode(Protocol::ANS_ACK);
            msgHandler.sendIntParameter(arts.size());
            for(map<size_t, Article>::iterator it = arts.begin(); it != arts.end(); ++it) {
                msgHandler.sendIntParameter(it->first);
                msgHandler.sendStringParameter(it->second.getTitle());
            }
        } catch (NgNotFoundException e) {
            msgHandler.sendCode(Protocol::ANS_NAK);
            msgHandler.sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
        }
    }

    void MessageInterpreter::createArt(MessageHandler& msgHandler, Database& database) throw(IllegalCommandException, ConnectionClosedException) {
        int id = msgHandler.recvIntParameter();
        string title = msgHandler.recvStringParameter();
        string author = msgHandler.recvStringParameter();
        string text = msgHandler.recvStringParameter();
        if(msgHandler.recvCode() != Protocol::COM_END) throw IllegalCommandException();
        msgHandler.sendCode(Protocol::ANS_CREATE_ART);
        msgHandler.sendCode(database.createArticle(id, title, author, text) ? Protocol::ANS_ACK : Protocol::ERR_NG_DOES_NOT_EXIST);
    }

    void MessageInterpreter::deleteArt(MessageHandler& msgHandler, Database& database) throw(IllegalCommandException, ConnectionClosedException) {
        int ngId = msgHandler.recvIntParameter();
        int artId = msgHandler.recvIntParameter();
        if(msgHandler.recvCode() != Protocol::COM_END) throw IllegalCommandException();
        msgHandler.sendCode(Protocol::ANS_DELETE_ART);
        try {
            database.deleteArticle(ngId, artId);
            msgHandler.sendCode(Protocol::ANS_ACK);
        } catch (NgNotFoundException ngE) {
            msgHandler.sendCode(Protocol::ANS_NAK);
            msgHandler.sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
        } catch (ArtNotFoundException artE) {
            msgHandler.sendCode(Protocol::ANS_NAK);
            msgHandler.sendCode(Protocol::ERR_ART_DOES_NOT_EXIST);
        }       
    }

    void MessageInterpreter::getArt(MessageHandler& msgHandler, Database& database) throw(IllegalCommandException, ConnectionClosedException) {
        int ngId = msgHandler.recvIntParameter();
        int artId = msgHandler.recvIntParameter();
        if(msgHandler.recvCode() != Protocol::COM_END) throw IllegalCommandException();
        msgHandler.sendCode(Protocol::ANS_GET_ART);
        try {
            Article* artP = database.getArticle(ngId, artId);
            msgHandler.sendCode(Protocol::ANS_ACK);
            msgHandler.sendStringParameter(artP->getTitle());
            msgHandler.sendStringParameter(artP->getAuthor());
            msgHandler.sendStringParameter(artP->getText());
        } catch (NgNotFoundException ngE) {
            msgHandler.sendCode(Protocol::ANS_NAK);
            msgHandler.sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
        } catch (ArtNotFoundException artE) {
            msgHandler.sendCode(Protocol::ANS_NAK);
            msgHandler.sendCode(Protocol::ERR_ART_DOES_NOT_EXIST);
        }
    }
}
