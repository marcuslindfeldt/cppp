#include "inmemorydatabase.h"
#include "article.h"
#include "newsgroup.h"
#include "../com/protocol.h"
#include <map>
#include <utility>
#include <string>
#include <algorithm>

using namespace std;
using namespace com;


namespace database {

    int InMemoryDatabase::createNewsgroup(const string& ngName) {

        map<size_t, Newsgroup>::iterator it = db.begin();
        while(it != db.end()) {
            if(it -> second.getName() == ngName){
                break;
            }
            ++it;
        }

        if(it == db.end()){

            ++lastNgId;
            Newsgroup ng(ngName);
            db.insert(make_pair(lastNgId, ng));
            ++nbrOfNewsgroup;
            return Protocol::ANS_CREATE_NG;
       }
        return Protocol::ERR_NG_ALREADY_EXISTS;

    }
    int InMemoryDatabase::populateNewsgroup(const Article& art, size_t ngId) {
        return 0;
    }



}
