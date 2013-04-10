#ifndef INMEMDB_H
#define INMEMDB_H

#include "database.h"

namespace database {

    class InMemoryDatabase : public Database {
        public:
            InMemoryDatabase()  {}
            Article* getArticle(size_t ngId, size_t artId) throw(NgNotFoundException, ArtNotFoundException);
            std::map<size_t, Article> listArticles(size_t ngId) const throw(NgNotFoundException);
            std::map<size_t, Newsgroup> listNewsgroups() const;
            bool createArticle(size_t ngId, const std::string& title, const std::string& author, const std::string& text);
            bool deleteNewsgroup(size_t ngId);
            bool createNewsgroup(const std::string& ngName);
            bool deleteArticle(size_t ngId, size_t artId) throw(NgNotFoundException, ArtNotFoundException);
        private:
            size_t lastNgId;
            std::map<size_t, Newsgroup> db;
    };
}
#endif