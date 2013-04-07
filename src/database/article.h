#ifndef ARTICLE_H
#define ARTICLE_H

#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>

namespace database {

    class Article {
        friend std::istream& operator>>(std::istream& in, Article& art);
        friend std::ostream& operator<<(std::ostream& out, const Article& art);

        public:
        	Article(const std::string& ti, const std::string& a, const std::string& te) : title(ti) , author(a) , text(te) {}
        	~Article() {}
        	const std::string& getTitle() const { return title; }
        	const std::string& getAuthor() const { return author; }
        	const std::string& getText() const { return text; }
        private:
        	std::string title, author, text;
    };

   /* std::istream& operator>>(std::istream& in, Article& art) {
        getline(in, art.title);
        getline(in, art.author);
        in >> noskipws;
        art.text = string((istream_iterator<char>(in)), istream_iterator<char>());
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const Article& art) {
        return out << art.title << endl << art.author << endl << art.text << endl;
    }*/
}
#endif
