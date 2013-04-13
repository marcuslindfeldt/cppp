#include "newsgroup.h"
#include <utility>
#include <algorithm>

using namespace std;

namespace database {

    Newsgroup::Newsgroup(const string& n): name(n) {
    lastArticleId = 0;

    }
	void Newsgroup::addArticle(const string& ti, const string& a, const string& te) {
		size_t id = ++lastArticleId;
		Article article(ti,a,te);
		articles.insert(make_pair(id, article));
	}

	size_t Newsgroup::delArticle(size_t i) {
		return articles.erase(i);
	}

	Article* Newsgroup::getArticle(size_t i) {
		std::map<size_t, Article> ::iterator it = articles.find(i);
		if(it == articles.end()) return NULL;
		return &articles.find(i)->second;
	}
}
