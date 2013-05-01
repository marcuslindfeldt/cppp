#include "commandhandler.h"
#include <boost/tokenizer.hpp>

using boost::tokenizer;
using boost::escaped_list_separator;
using namespace std;
using namespace com;

typedef tokenizer<escaped_list_separator<char> > so_tokenizer;

namespace client {

	bool CommandHandler::perform(string& cmdstring) 
	throw(IllegalCommandException, 
	      ConnectionClosedException,
	      invalid_argument)
	{

	    so_tokenizer tok(cmdstring, escaped_list_separator<char>('\\', ' ', '\"'));
	    so_tokenizer::iterator begin = tok.begin(); 
	    so_tokenizer::iterator end = tok.end();
		// explode string on whitespace
		// stringstream ss(cmdstring);
		// istream_iterator<string> begin(ss);
		// istream_iterator<string> end;
		vector<string> args(begin, end);

		if(args.size() < 1) throw IllegalCommandException();
		
		string cmd = args.front();
		args.erase(args.begin());

		if(cmd == "list") {
			switch(args.size()){
				case 0:
					this->listNg();
					break;
				case 1:
					this->listArt(args);
					break;
				default:
				throw invalid_argument("");
			}
		}else if(cmd == "read") {
			this->getArt(args);
		}else if(cmd == "create") {
			switch(args.size()){
				case 1:
				this->createNg(args);
				break;
				case 4:
				this->createArt(args);
				break;
				default:
				throw invalid_argument("");
			}
		}else if(cmd == "delete") {
			switch(args.size()){
				case 1:
				this->deleteNg(args);
				break;
				case 2:
				this->deleteArt(args);
				break;
				default:
				throw invalid_argument("");
			}
		}else if(cmd == "clear") {
			cout << "\x1B[2J\x1B[H";
			return false;
		}else if(cmd == "quit") {
			throw ConnectionClosedException();
		}else if(cmd == "help"){
			cout << "Available commands:" << endl
			<< "  list\t\t\t\t\tList all newsgroups" << endl
			<< "  list <ngid>\t\t\t\tList articles in newsgroup" << endl
			<< "  read <ngid> <id>\t\t\tDisplay article" << endl
			<< "  create <newsgroup>\t\t\tCreate newsgroup" << endl
			<< "  create <ngid> <title> <author> <body>\tCreate article" << endl
			<< "  delete <ngid>\t\t\t\tDelete newsgroup" << endl
			<< "  delete <ngid> <id>\t\t\tDelete article" << endl
			<< "  clear\t\t\t\t\tClear the screen" << endl
			<< "  quit\t\t\t\t\tExit the application" << endl;
			return false;
		}else{
			throw IllegalCommandException();	
		}

		return true;
	}

	void CommandHandler::listNg() 
		throw(ConnectionClosedException) 
	{
		mh.sendCode(Protocol::COM_LIST_NG);
		mh.sendCode(Protocol::COM_END);
	}

	void CommandHandler::createNg(vector<string> args) 
		throw(ConnectionClosedException) 
	{
		mh.sendCode(Protocol::COM_CREATE_NG);
		mh.sendStringParameter(args.front());
		mh.sendCode(Protocol::COM_END);
	}	


	void CommandHandler::deleteNg(vector<string> args)
		throw(ConnectionClosedException) 
	{
		if(args.size() < 1) throw invalid_argument("");

		int ngid = stoi(args.front());

		mh.sendCode(Protocol::COM_DELETE_NG);
		mh.sendIntParameter(ngid);
		mh.sendCode(Protocol::COM_END);
	}

	void CommandHandler::listArt(vector<string> args)
		throw(ConnectionClosedException,
		      invalid_argument) 
	{
		int ngid = stoi(args.front());

		mh.sendCode(Protocol::COM_LIST_ART);
		mh.sendIntParameter(ngid);
		mh.sendCode(Protocol::COM_END);
	}

	void CommandHandler::createArt(vector<string> args)
		throw(ConnectionClosedException,
		      invalid_argument) 
	{
		if(args.size() < 4) throw invalid_argument("");

		int ngid = stoi(args[0]);
		string title = args[1];
		string author = args[2];
		string body = args[3];

		mh.sendCode(Protocol::COM_CREATE_ART);
		mh.sendIntParameter(ngid);
		mh.sendStringParameter(title);
		mh.sendStringParameter(author);
		mh.sendStringParameter(body);
		mh.sendCode(Protocol::COM_END);
	}

	void CommandHandler::deleteArt(vector<string> args)
		throw(ConnectionClosedException,
		      invalid_argument) 
	{
		if(args.size() < 2) throw invalid_argument("");

		int ngid = stoi(args[0]);
		int artid = stoi(args[1]);
		
		mh.sendCode(Protocol::COM_DELETE_ART);
		mh.sendIntParameter(ngid);
		mh.sendIntParameter(artid);
		mh.sendCode(Protocol::COM_END);
	}

	void CommandHandler::getArt(vector<string> args)
		throw(ConnectionClosedException,
		      invalid_argument) 
	{
		if(args.size() < 2) throw invalid_argument("");

		int ngid = stoi(args[0]);
		int artid = stoi(args[1]);
		
		mh.sendCode(Protocol::COM_GET_ART);
		mh.sendIntParameter(ngid);
		mh.sendIntParameter(artid);
		mh.sendCode(Protocol::COM_END);
	}		
}