#include "filesystemdatabase.h"
#include <utility>
#include <algorithm>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <fstream>
#include <unistd.h>
#include <sys/stat.h>

using namespace std;

namespace database {

	FilesystemDatabase::FilesystemDatabase(const std::string& baseDir) throw(NgNotFoundException):baseDir(baseDir)
	{
		DIR *dir;
		struct dirent *entry;
		size_t highest = 1;
		if( (dir=opendir(baseDir.c_str())) ){
			while( (entry = readdir(dir)) ) {
				if( entry->d_name[0] != '.' ) {

					string dir_name(entry->d_name);
					size_t split_index = dir_name.find_first_of('-');
					size_t ngId = atoi(dir_name.substr(0, split_index).c_str());
					if(ngId >= highest){
						highest = ngId + 1;
					}
				}
			}
			closedir(dir);
		}else{
			cerr << "Unable to open directory: " << baseDir << endl;
			throw BasedirNotFoundException();
		}
		nextNgId = highest;
	}

	Article* FilesystemDatabase::getArticle(size_t ngId, size_t artId) throw(NgNotFoundException, ArtNotFoundException)
	{
		map<size_t,Newsgroup> ngs = listNewsgroups();
		map<size_t,Newsgroup>::iterator it = ngs.find(ngId);

		if(it == ngs.end()) throw NgNotFoundException();

		string path = baseDir + "/" + to_string(ngId) + "-" + it->second.getName() + "/" + to_string(artId);
		ifstream infile(path.c_str());

		if(!infile.is_open()){
			throw ArtNotFoundException();
		}

		string art_title;
		string art_author;
		getline(infile, art_title);
		getline(infile, art_author);
		string art_body((istreambuf_iterator<char>(infile)),
				  istreambuf_iterator<char>());

		Article* artP = new Article(art_title, art_author, art_body);
		return artP;
	}

	map<size_t, Newsgroup> FilesystemDatabase::listNewsgroups() const
	{
		DIR *dir;
		struct dirent *entry;
		map<size_t, Newsgroup> ngs;
		if( (dir=opendir(baseDir.c_str())) ){
			while( (entry = readdir(dir) )){

				if( entry->d_name[0] != '.' ) {
					string dir_name(entry->d_name);

					size_t split_index = dir_name.find_first_of('-');
					size_t ngId = atoi(dir_name.substr(0, split_index).c_str());
					Newsgroup ng(dir_name.substr(split_index + 1));

					ngs.insert(make_pair(ngId, ng));
				}
			}
			closedir(dir);
		}
		return ngs;
	}

	map<size_t, Article> FilesystemDatabase::listArticles(size_t ngId) const throw(NgNotFoundException)
	{
		map<size_t, Article> articles;
		map<size_t,Newsgroup> ngs = listNewsgroups();
		map<size_t,Newsgroup>::iterator it = ngs.find(ngId);

		if(it == ngs.end()) throw NgNotFoundException();

		string ngdir = baseDir + "/" + to_string(ngId) + "-" + it->second.getName();

		DIR *dir;
		struct dirent *entry;
		string art_id;
		string art_title;
		string art_author;
		string art_body;

		if( (dir=opendir(ngdir.c_str())) ) {
			while( (entry = readdir(dir)) ) {
				if( entry->d_name[0] != '.' ) {
					art_id = entry->d_name;
					// parse article
					string file_path = ngdir + "/" + art_id;
					ifstream infile(file_path.c_str());

					getline(infile, art_title);
					getline(infile, art_author);

					string art_body((istreambuf_iterator<char>(infile)),
					istreambuf_iterator<char>());

					Article a(art_title, art_author, art_body);
					articles.insert(make_pair(atoi(art_id.c_str()), a));
					infile.close();
				}
			}
		closedir(dir);
		}	
		return articles;
	}


	bool FilesystemDatabase::createArticle(size_t ngId, const string& title, const string& author, const string& text)
	{
		map<size_t,Newsgroup> ngs = listNewsgroups();
		map<size_t,Newsgroup>::iterator it = ngs.find(ngId);

		if(it == ngs.end()) return false;
		// iterate to a free id
		string ngdir = baseDir + "/" + to_string(ngId) + "-" + it->second.getName();

		DIR *dir;
		struct dirent *entry;
		int highest = 1;
		if( (dir=opendir(ngdir.c_str())) ) {
			while( (entry = readdir(dir)) ) {
				if( entry->d_name[0] != '.' &&
				    atoi(entry->d_name) >= highest) {

					highest = atoi(entry->d_name) + 1;
				}
			}
			closedir(dir);
		}	
		// create an article
		string path = baseDir + "/" + to_string(ngId) + "-" + it->second.getName() + "/" + to_string(highest);		
		ofstream outfile(path.c_str());
		outfile << title << endl << author << endl << text;
		outfile.close();
		return true;
	}

	bool FilesystemDatabase::deleteNewsgroup(size_t ngId)
	{
		map<size_t,Newsgroup> ngs = listNewsgroups();
		map<size_t,Newsgroup>::iterator it = ngs.find(ngId);

		if(it == ngs.end()) return false;

		string ngdir = baseDir + "/" + to_string(ngId) + "-" + it->second.getName();

		DIR *dir;
		struct dirent *entry;

		if( (dir=opendir(ngdir.c_str()) ) ){
			while( (entry = readdir(dir) )){
				if( entry->d_name[0] != '.' ) {
					// delete contents
					string path = ngdir + "/" + entry->d_name;
					unlink(path.c_str());
				}
			}
			closedir(dir);
			return rmdir(ngdir.c_str()) == 0; 
		}
		return false;
	}

	bool FilesystemDatabase::createNewsgroup(const string& ngName)
	{
		map<size_t,Newsgroup> ngs = listNewsgroups();
		map<size_t, Newsgroup>::iterator it = ngs.begin(); 
		while(it != ngs.end() && it->second.getName() != ngName) ++it;


		string ngdir = baseDir + "/" + to_string(nextNgId) + "-" + ngName;	
		
		if (it != ngs.end() || 
		    mkdir(ngdir.c_str(), S_IRWXU|S_IRGRP|S_IXGRP) != 0){
			return false;
		}
		++nextNgId;
		return true;
	}

	bool FilesystemDatabase::deleteArticle(size_t ngId, size_t artId) throw(NgNotFoundException, ArtNotFoundException)
	{
		map<size_t,Newsgroup> ngs = listNewsgroups();
		map<size_t,Newsgroup>::iterator it = ngs.find(ngId);

		if(it == ngs.end()) throw NgNotFoundException();

		string path = baseDir + "/" + to_string(ngId) + "-" + it->second.getName() + "/" + to_string(artId);
		if(unlink(path.c_str()) != 0){
			throw ArtNotFoundException();
		}
		return true;
	}
}
