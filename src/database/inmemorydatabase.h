#ifndef INMEMDB_H
#define INMEMDB_H

#include <string>
#include <map>
#include "database.h"
#include "article.h"
#include "newsgroup.h"

namespace database {

    class InMemoryDatabase : public Database {

        public:

            InMemoryDatabase() : nbrOfNewsgroup(0), lastNgId(0) {}
            const Article& getArticle(size_t ngId, size_t artId) const;
            int populateNewsgroup(const Article& art, size_t ngId);
            int deleteNewsgroup(size_t ngId);
            int createNewsgroup(const std::string& ngName);
            int populateArticle(size_t ngId, size_t artId);
            int deleteArticle(size_t ngId, size_t artId);
        private:
            size_t nbrOfNewsgroup;
            size_t lastNgId;
            std::map<size_t, Newsgroup> db;

    };

}
#endif
