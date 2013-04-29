#include "commandhandler.h"

using namespace std;
using namespace com;

namespace client {

	bool CommandHandler::perform(string& cmdstring) 
	throw(com::IllegalCommandException, 
	      com::ConnectionClosedException)
	{
		// explode string on whitespace
		stringstream ss(cmdstring);
		istream_iterator<string> begin(ss);
		istream_iterator<string> end;
		vector<string> args(begin, end);

		if(args.size() < 1) throw IllegalCommandException();
		
		string cmd = args.front();
		args.erase(args.begin());

		if(cmd == "list") {
			this->listNg();
		}else if(cmd == "read") {
			cout << "reading..." << endl;
		}else if(cmd == "create") {
			switch(args.size()){
				case 1:
				this->createNg(args);
				break;
			}
		}else if(cmd == "delete") {
			cout << "deleting..." << endl;
		}else if(cmd == "clear") {
			cout << "\x1B[2J\x1B[H";
			return false;
		}else if(cmd == "quit") {
			throw ConnectionClosedException();
		}else if(cmd == "help"){
			cout << "Available commands:" << endl
			<< "  list\t\t\t\t\tList all newsgroups" << endl
			<< "  list <newsgroup>\t\t\tList articles in newsgroup" << endl
			<< "  read <id>\t\t\t\tDisplay article" << endl
			<< "  create <newsgroup>\t\t\tCreate newsgroup" << endl
			<< "  create <title> <author> <body>\tCreate article" << endl
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

	void CommandHandler::createNg(vector<string> args) 
		throw(IllegalCommandException, 
		      ConnectionClosedException) 
	{
		mh.sendCode(Protocol::COM_CREATE_NG);
		mh.sendStringParameter(args.front());
		mh.sendCode(Protocol::COM_END);
	}	

	void CommandHandler::listNg() throw(IllegalCommandException, ConnectionClosedException) {
		mh.sendCode(Protocol::COM_LIST_NG);
		mh.sendCode(Protocol::COM_END);
	}	
}