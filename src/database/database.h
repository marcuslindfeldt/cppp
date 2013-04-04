#ifndef DATABASE_H
#define DATABASE_H
#include <string>
#include <vector>
#include "article.h"

/* Interface for inmemory database and file database
 *
 */
 namespace database{

    class Database {
        public:
            virtual ~Database(){};
            virtual Article* getArticle(size_t ngId, size_t artId) const throw(NgNotFoundException,ArtNotFoundException) = 0;
            virtual unsigned int createArticle(size_t ngId,const std::string& title, const std::string& author, const std::string& text) = 0;
            virtual unsigned int deleteArticle(size_t ngId, size_t artId) = 0;
            virtual unsigned int deleteNewsgroup(size_t ngId) = 0;
            virtual unsigned int createNewsgroup(const std::string& name) = 0;
            virtual std::vector<Article> listArticles(size_t ngId) = 0;

    };

    struct NgNotFoundException{};
    struct ArtNotFoundException{};
 }

#endif
