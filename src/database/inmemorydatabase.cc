#include "inmemorydatabase.h"
#include "article.h"
#include "newsgroup.h"
#include "../com/protocol.h"
#include <utility>
#include <algorithm>

using namespace std;
using namespace com;

namespace database {

    unsigned int InMemoryDatabase::createNewsgroup(const string& ngName) {

        map<size_t, Newsgroup>::iterator it = db.begin();
        while(it != db.end()) {
            if(it -> second.getName() == ngName) {
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

    map<size_t, Newsgroup> InMemoryDatabase::listNewsgroups() const  {
        return db;
    }

    unsigned int InMemoryDatabase::deleteNewsgroup(size_t ngId) {
        return db.erase(ngId) !=0 ? Protocol::ANS_ACK : Protocol::ERR_NG_DOES_NOT_EXIST;
    }

    unsigned int InMemoryDatabase::createArticle(size_t ngId, const string& title, const string& author, const string& text) {
        map<size_t, Newsgroup>::iterator it = db.find(ngId);
        if(it == db.end()) return Protocol::ERR_NG_DOES_NOT_EXIST;
        it->second.addArticle(title, author, text);
        return Protocol::ANS_ACK;
    }

    map<size_t, Article> InMemoryDatabase::listArticles(size_t ngId) const throw(NgNotFoundException) {
        map<size_t, Newsgroup>::const_iterator it = db.find(ngId);
        if(it == db.end()) throw NgNotFoundException();
        return it->second.getArticles();
    }

    Article* InMemoryDatabase::getArticle(size_t ngId, size_t artId) throw(NgNotFoundException, ArtNotFoundException) {
        map<size_t, Newsgroup>::iterator it = db.find(ngId);
        if(it == db.end()) throw NgNotFoundException();
        Article* artP = it->second.getArticle(artId);
        if(artP == 0) throw ArtNotFoundException();
        return artP;
    }

   unsigned int InMemoryDatabase::deleteArticle(size_t ngId, size_t artId) {
        map<size_t, Newsgroup>::iterator it = db.find(ngId);
        if(it == db.end()) return Protocol::ERR_NG_DOES_NOT_EXIST;
        if(it->second.delArticle(artId) == 0) return Protocol::ERR_ART_DOES_NOT_EXIST;
        return Protocol::ANS_ACK;
    }
}