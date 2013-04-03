#ifndef ARTICLE_H
#define ARTICLE_H

#include <string>

namespace database {

    class Article {
        public:
        	Article(const std::string& ti, const std::string& a, const std::string& te) : title(ti) , author(a) , text(te) {}
        	~Article() {}
        	const std::string& getTitle() const { return title; }
        	const std::string& getAuthor() const { return author; }
        	const std::string& getText() const { return text; }
        private:
        	std::string title, author, text;
    };
}
#endif