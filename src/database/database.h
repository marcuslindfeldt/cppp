#ifndef DATABASE_H
#define DATABASE_H
#include <string>
#include "Article.h"

/* Interface for inmemory database and file database
 *
 */
 namespace database{

    class Database {
        public:
            virtual ~Database(){};
            virtual const Article& getArticle(size_t ngId, size_t artId) const;
            virtual int populateNewsgroup(const Article& art, size_t ngId);
            virtual int deleteArticle(size_t ngId, size_t artId);
            virtual int deleteNewsgroup(size_t ngId);
            virtual int saveNewsgroup(const std::string& name);
            virtual int populateArticle(size_t ngId, size_t artId);

    };
 }
