#ifndef ARTICLE_H
#define ARTICLE_H

namespace database {

    class Article {
        public:
        	Article(int id, const string& title, const string& author, const stirng& text) : id(id), title(title) , author(author) , text(text) {}
        	~Article() {}
        	const string& getTitle() const { return title; }
        	const string& getAuthor() const { return author; }
        	const string& getText() const { return text; }
        private:
        	int id;
        	string title, author, text;
    };
}
#endif