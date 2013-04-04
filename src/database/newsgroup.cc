#include "article.h"
#include "newsgroup.h"
#include <string>
#include <map>
#include <utility>
#include <algorithm>

using namespace std;

namespace database {

	void Newsgroup::addArticle(const string& ti, const string& a, const string& te) {
		size_t id = ++lastArticleId;
		Article article(ti,a,te);
		articles.insert(make_pair(id, article));
	}

	size_t Newsgroup::delArticle(size_t i) {
		return articles.erase(i);
	}

	Article* Newsgroup::getArticle(size_t i) {
		return &articles.find(i)->second;
	}
}