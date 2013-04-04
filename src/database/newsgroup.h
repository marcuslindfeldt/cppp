#ifndef NEWSGROUP_H
#define NEWSGROUP_H

#include "article.h"
#include <string>
#include <map>

namespace database {

    class Newsgroup {
        public:
        	Newsgroup(const std::string& n) : name(n) {}
        	~Newsgroup() {
        		articles.clear();
        	}
        	const std::string& getName() const { return name; }
        	std::map<size_t, Article> getArticles() const { return articles; }
        	void addArticle(const std::string& ti, const std::string& a, const std::string& te);
        	void delArticle(size_t i);
        	Article* getArticle(size_t i) const;
        private:
        	size_t lastArticleId;
        	std::string name;
        	std::map<size_t, Article> articles;
    };
}
#endif