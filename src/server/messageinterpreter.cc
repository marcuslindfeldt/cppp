#include "messageinterpreter.h"
#include "../com/protocol.h"
#include "../database/inmemorydatabase.h"
#include "../com/messagehandler.h"
#include <string>
#include <map>

using namespace database;
using namespace com;
using namespace std;

namespace server {

    void MessageInterpreter::interpretMessage(int code) throw(IllegalCommandException, ConnectionClosedException) {
        switch(code){
            case Protocol::COM_LIST_NG:
                listNg();
                break;
            case Protocol::COM_CREATE_NG:
                createNg();
                break;
            case Protocol::COM_DELETE_NG:
                deleteNg();
                break;
            case Protocol::COM_LIST_ART:
                listArt();
                break;
            case Protocol::COM_CREATE_ART:
                createArt();
                break;
            case Protocol::COM_DELETE_ART:
                deleteArt();
                break;
            case Protocol::COM_GET_ART:
                getArt();
                break;
            default:
                throw IllegalCommandException();
                break;
        }
        msgHandler.sendCode(Protocol::ANS_END);
    }

    void MessageInterpreter::listNg() throw(IllegalCommandException, ConnectionClosedException) {
        if(msgHandler.recvCode() != Protocol::COM_END) throw IllegalCommandException();
        map<size_t, Newsgroup> ngs = database.listNewsgroups();
        msgHandler.sendCode(Protocol::ANS_LIST_NG);
        msgHandler.sendIntParameter(ngs.size());
        for(map<size_t, Newsgroup>::iterator it = ngs.begin(); it != ngs.end(); ++it) {
            msgHandler.sendIntParameter(it->first);
            msgHandler.sendStringParameter(it->second.getName());
        }
    }

    void MessageInterpreter::createNg() throw(IllegalCommandException, ConnectionClosedException) {
        string name = msgHandler.recvStringParameter();
        if(msgHandler.recvCode() != Protocol::COM_END) throw IllegalCommandException();
        msgHandler.sendCode(Protocol::ANS_CREATE_NG);
        unsigned int code = database.createNewsgroup(name);
        if(code == Protocol::ERR_NG_ALREADY_EXISTS) {
            msgHandler.sendCode(Protocol::ANS_NAK);
        }
        msgHandler.sendCode(code);
    }

    void MessageInterpreter::deleteNg() throw(IllegalCommandException, ConnectionClosedException) {
        int id = msgHandler.recvIntParameter();
        if(msgHandler.recvCode() != Protocol::COM_END) throw IllegalCommandException();
        msgHandler.sendCode(Protocol::ANS_DELETE_NG);
        unsigned int code = database.deleteNewsgroup(id);
        if(code == Protocol::ERR_NG_DOES_NOT_EXIST) {
            msgHandler.sendCode(Protocol::ANS_NAK);
        }
        msgHandler.sendCode(code);
    }

    void MessageInterpreter::listArt() throw(IllegalCommandException, ConnectionClosedException) {
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

    void MessageInterpreter::createArt() throw(IllegalCommandException, ConnectionClosedException) {
        int id = msgHandler.recvIntParameter();
        string title = msgHandler.recvStringParameter();
        string author = msgHandler.recvStringParameter();
        string text = msgHandler.recvStringParameter();
        if(msgHandler.recvCode() != Protocol::COM_END) throw IllegalCommandException();
        msgHandler.sendCode(Protocol::ANS_CREATE_ART);
        unsigned int code = database.createArticle(id, title, author, text);
        if(code == Protocol::ERR_NG_DOES_NOT_EXIST) {
            msgHandler.sendCode(Protocol::ANS_NAK);
        }
        msgHandler.sendCode(code);
    }

    void MessageInterpreter::deleteArt() throw(IllegalCommandException, ConnectionClosedException) {
        int ngId = msgHandler.recvIntParameter();
        int artId = msgHandler.recvIntParameter();
        if(msgHandler.recvCode() != Protocol::COM_END) throw IllegalCommandException();
        msgHandler.sendCode(Protocol::ANS_DELETE_ART);
        unsigned int code = database.deleteArticle(ngId, artId);
        if(code == Protocol::ERR_NG_DOES_NOT_EXIST || code == Protocol::ERR_ART_DOES_NOT_EXIST) {
            msgHandler.sendCode(Protocol::ANS_NAK);
        }
        msgHandler.sendCode(code);
    }

    void MessageInterpreter::getArt() throw(IllegalCommandException, ConnectionClosedException) {
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