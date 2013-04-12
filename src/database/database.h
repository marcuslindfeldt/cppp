#ifndef DATABASE_H
#define DATABASE_H 
#include <map>
#include <string>
#include "article.h"
#include "newsgroup.h"

/* Interface for inmemory database and file database
 *
 */
 namespace database{

    struct NgNotFoundException{};
    struct ArtNotFoundException{};
    struct BasedirNotFoundException{};

    class Database {
        public:
            virtual ~Database(){};
            virtual Article* getArticle(size_t ngId, size_t artId) throw(NgNotFoundException,ArtNotFoundException) = 0;
            virtual bool createArticle(size_t ngId,const std::string& title, const std::string& author, const std::string& text) = 0;
            virtual bool deleteArticle(size_t ngId, size_t artId) throw(NgNotFoundException, ArtNotFoundException) = 0;
            virtual bool deleteNewsgroup(size_t ngId) = 0;
            virtual bool createNewsgroup(const std::string& name) = 0;
            virtual std::map<size_t, Article> listArticles(size_t ngId) const throw(NgNotFoundException) = 0;
            virtual std::map<size_t, Newsgroup> listNewsgroups() const = 0;
    };
 }
#endif