#ifndef DATABASE_H
#define DATABASE_H
#include <string>
#include "article.h"

/* Interface for inmemory database and file database
 *
 */
 namespace database{

    class Database {
        public:
            virtual ~Database(){};
            virtual const Article& getArticle(size_t ngId, size_t artId) const = 0;
            virtual int populateNewsgroup(const Article& art, size_t ngId) = 0;
            virtual int deleteArticle(size_t ngId, size_t artId) = 0;
            virtual int deleteNewsgroup(size_t ngId) = 0;
            virtual int createNewsgroup(const std::string& name) = 0;
            virtual int populateArticle(size_t ngId, size_t artId) = 0;

    };
 }
#endif
