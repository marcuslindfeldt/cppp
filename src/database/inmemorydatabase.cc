#include "inmemorydatabase.h"
#include <utility>
#include <algorithm>

using namespace std;

namespace database {

    bool InMemoryDatabase::createNewsgroup(const string& ngName) {

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
            return true;
        }
        return false;
    }

    map<size_t, Newsgroup> InMemoryDatabase::listNewsgroups() const  {
        return db;
    }

    bool InMemoryDatabase::deleteNewsgroup(size_t ngId) {
        return db.erase(ngId) !=0;
    }

    bool InMemoryDatabase::createArticle(size_t ngId, const string& title, const string& author, const string& text) {
        map<size_t, Newsgroup>::iterator it = db.find(ngId);
        if(it == db.end()) return false;
        it->second.addArticle(title, author, text);
        return true;
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

    bool InMemoryDatabase::deleteArticle(size_t ngId, size_t artId) throw (NgNotFoundException, ArtNotFoundException) {
        map<size_t, Newsgroup>::iterator it = db.find(ngId);
        if(it == db.end()) throw NgNotFoundException();
        if(it->second.delArticle(artId) == 0) throw ArtNotFoundException();
        return true;
    }
}
