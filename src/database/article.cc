#include "article.h"
#include <iterator>
#include <sstream>
#include <algorithm>

using namespace std;

namespace database {

    istream& operator>>(istream& in, Article& art) {
        getline(in, art.title);
        getline(in, art.author);
        in >> noskipws;
        art.text = string((istream_iterator<char>(in)), istream_iterator<char>());
        return in;
    }

    ostream& operator<<(ostream& out, const Article& art) {
        return out << art.title << endl << art.author << endl << art.text << endl;
    }
}
