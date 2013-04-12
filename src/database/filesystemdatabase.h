#ifndef FSDB_H
#define FSDB_H

#include "database.h"

namespace database {

    class FilesystemDatabase : public Database {
        public:
            FilesystemDatabase(const std::string& baseDir) throw(NgNotFoundException);
            Article* getArticle(size_t ngId, size_t artId) throw(NgNotFoundException, ArtNotFoundException);
            std::map<size_t, Article> listArticles(size_t ngId) const throw(NgNotFoundException);
            std::map<size_t, Newsgroup> listNewsgroups() const;
            bool createArticle(size_t ngId, const std::string& title, const std::string& author, const std::string& text);
            bool deleteNewsgroup(size_t ngId);
            bool createNewsgroup(const std::string& ngName);
            bool deleteArticle(size_t ngId, size_t artId) throw(NgNotFoundException, ArtNotFoundException);
        private:
            size_t nextNgId;
            const std::string& baseDir;
    };
}
#endif
