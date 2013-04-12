#include "messageinterpreter.h"
#include "../com/protocol.h"
#include <string>
#include <map>

using namespace database;
using namespace com;
using namespace std;

namespace server {

    void MessageInterpreter::interpretAndPerformCmd() throw(IllegalCommandException, ConnectionClosedException) {
        int code = mh.recvCode();
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
        mh.sendCode(Protocol::ANS_END);
    }

    void MessageInterpreter::listNg() throw(IllegalCommandException, ConnectionClosedException) {
        if(mh.recvCode() != Protocol::COM_END) throw IllegalCommandException();
        map<size_t, Newsgroup> ngs = db->listNewsgroups();
        mh.sendCode(Protocol::ANS_LIST_NG);
        mh.sendIntParameter(ngs.size());
        for(map<size_t, Newsgroup>::iterator it = ngs.begin(); it != ngs.end(); ++it) {
            mh.sendIntParameter(it->first);
            mh.sendStringParameter(it->second.getName());
        }
    }

    void MessageInterpreter::createNg() throw(IllegalCommandException, ConnectionClosedException) {
        string name = mh.recvStringParameter();
        if(mh.recvCode() != Protocol::COM_END) throw IllegalCommandException();
        mh.sendCode(Protocol::ANS_CREATE_NG);
        if(!db->createNewsgroup(name)) {
            mh.sendCode(Protocol::ANS_NAK);
            mh.sendCode(Protocol::ERR_NG_ALREADY_EXISTS);
        } else {
            mh.sendCode(Protocol::ANS_ACK);
        }
    }

    void MessageInterpreter::deleteNg() throw(IllegalCommandException, ConnectionClosedException) {
        int id = mh.recvIntParameter();
        if(mh.recvCode() != Protocol::COM_END) throw IllegalCommandException();
        mh.sendCode(Protocol::ANS_DELETE_NG);
        if(!db->deleteNewsgroup(id)) {
            mh.sendCode(Protocol::ANS_NAK);
            mh.sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
        } else {
            mh.sendCode(Protocol::ANS_ACK);
        }
    }

    void MessageInterpreter::listArt() throw(IllegalCommandException, ConnectionClosedException) {
        int id = mh.recvIntParameter();
        if(mh.recvCode() != Protocol::COM_END) throw IllegalCommandException();
        mh.sendCode(Protocol::ANS_LIST_ART);
        try {
            map<size_t, Article> arts = db->listArticles(id);
            mh.sendCode(Protocol::ANS_ACK);
            mh.sendIntParameter(arts.size());
            for(map<size_t, Article>::iterator it = arts.begin(); it != arts.end(); ++it) {
                mh.sendIntParameter(it->first);
                mh.sendStringParameter(it->second.getTitle());
            }
        } catch (NgNotFoundException e) {
            mh.sendCode(Protocol::ANS_NAK);
            mh.sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
        }
    }

    void MessageInterpreter::createArt() throw(IllegalCommandException, ConnectionClosedException) {
        int id = mh.recvIntParameter();
        string title = mh.recvStringParameter();
        string author = mh.recvStringParameter();
        string text = mh.recvStringParameter();
        if(mh.recvCode() != Protocol::COM_END) throw IllegalCommandException();
        mh.sendCode(Protocol::ANS_CREATE_ART);
        if(!db->createArticle(id, title, author, text)) {
            mh.sendCode(Protocol::ANS_NAK);
            mh.sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
        } else {
            mh.sendCode(Protocol::ANS_ACK);
        }
    }

    void MessageInterpreter::deleteArt() throw(IllegalCommandException, ConnectionClosedException) {
        int ngId = mh.recvIntParameter();
        int artId = mh.recvIntParameter();
        if(mh.recvCode() != Protocol::COM_END) throw IllegalCommandException();
        mh.sendCode(Protocol::ANS_DELETE_ART);
        try {
            db->deleteArticle(ngId, artId);
            mh.sendCode(Protocol::ANS_ACK);
        } catch (NgNotFoundException ngE) {
            mh.sendCode(Protocol::ANS_NAK);
            mh.sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
        } catch (ArtNotFoundException artE) {
            mh.sendCode(Protocol::ANS_NAK);
            mh.sendCode(Protocol::ERR_ART_DOES_NOT_EXIST);
        }
    }

    void MessageInterpreter::getArt() throw(IllegalCommandException, ConnectionClosedException) {
        int ngId = mh.recvIntParameter();
        int artId = mh.recvIntParameter();
        if(mh.recvCode() != Protocol::COM_END) throw IllegalCommandException();
        mh.sendCode(Protocol::ANS_GET_ART);
        try {
            Article* artP = db->getArticle(ngId, artId);
            mh.sendCode(Protocol::ANS_ACK);
            mh.sendStringParameter(artP->getTitle());
            mh.sendStringParameter(artP->getAuthor());
            mh.sendStringParameter(artP->getText());
        } catch (NgNotFoundException ngE) {
            mh.sendCode(Protocol::ANS_NAK);
            mh.sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
        } catch (ArtNotFoundException artE) {
            mh.sendCode(Protocol::ANS_NAK);
            mh.sendCode(Protocol::ERR_ART_DOES_NOT_EXIST);
        }
    }
}
