#ifndef INMEMDB_H
#define INMEMDB_H

#include <string>
#include <map>
#include <vector>
#include "database.h"
#include "article.h"
#include "newsgroup.h"

namespace database {

    class InMemoryDatabase : public Database {

        public:

            InMemoryDatabase() : nbrOfNewsgroup(0), lastNgId(0) {}
            Article* getArticle(size_t ngId, size_t artId) const throw(NgNotFoundException, ArtNotFoundException);
            std::vector<Article> listArticles(size_t ngId);
            unsigned int createArticle(size_t ngId, const std::string& title, const std::string& author, const std::string& text);
            unsigned int deleteNewsgroup(size_t ngId);
            unsigned int createNewsgroup(const std::string& ngName);
            unsigned int deleteArticle(size_t ngId, size_t artId);
        private:
            size_t nbrOfNewsgroup;
            size_t lastNgId;
            std::map<size_t, Newsgroup> db;

    };

}
#endif
