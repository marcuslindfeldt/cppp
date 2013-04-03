#include <map>
#include <vector>
#include <utility>
#include <string>
#include <algorithm>
#include "inmemorydatabase.h"
#include "article.h"
#include "newsgroup.h"
#include "../com/protocol.h"
using namespace std;
using namespace com;


namespace database {

    unsigned int InMemoryDatabase::createNewsgroup(const string& ngName) {

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
            return Protocol::ANS_ACK;
       }
        return Protocol::ERR_NG_ALREADY_EXISTS;

    }

    //TODO --lastNgId ?
    unsigned int InMemoryDatabase::deleteNewsgroup(size_t ngId) {
        return db.erase(ngId)!=0 ? Protocol::ANS_ACK : Protocol::ERR_NG_DOES_NOT_EXIST;
    }

    unsigned int InMemoryDatabase::createArticle(size_t ngId, const string& title, const string& author, const string& text) {
       if(db.find(ngId) == db.end()) {return Protocol::ERR_NG_DOES_NOT_EXIST;}
        db[ngId].addArticle(title, author, text);
        return Protocol::ANS_ACK;
    }
    vector<Article> InMemoryDatabase::listArticles(size_t ngId) {

    }

   unsigned int InMemoryDatabase::deleteArticle(size_t ngId, size_t artId) {
        if(db.find(ngId) == db.end()) {return Protocol::ERR_NG_DOES_NOT_EXIST;}
        if(!db[ngId].getArticles().erase(artId)) {return Protocol::ERR_ART_DOES_NOT_EXIST;}
        return Protocol::ANS_ACK;
    }




}
