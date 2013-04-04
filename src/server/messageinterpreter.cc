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

    void MessageInterpreter::interpretMessage(int code) {
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
                break;
        }
    }

    void MessageInterpreter::listNg(){
        if(msgHandler.recvCode() != Protocol::COM_END) throw ConnectionClosedException();
        map<size_t, Newsgroup> ngs = database.listNewsgroups();
        msgHandler.sendCode(Protocol::ANS_LIST_NG);
        msgHandler.sendCode(Protocol::PAR_NUM);
        msgHandler.sendInt(ngs.size());
        for(map<size_t, Newsgroup>::iterator it = ngs.begin(); it != ngs.end(); ++it) {
            msgHandler.sendCode(Protocol::PAR_NUM);
            msgHandler.sendInt(it->first);
            msgHandler.sendStringParameter(it->second.getName());
        }
    }

    void MessageInterpreter::createNg(){}
    void MessageInterpreter::deleteNg(){}
    void MessageInterpreter::listArt(){}
    void MessageInterpreter::createArt(){}
    void MessageInterpreter::deleteArt(){}
    void MessageInterpreter::getArt(){}
}
