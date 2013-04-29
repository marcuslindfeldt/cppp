#include "commandhandler.h"

using namespace std;
using namespace com;

namespace client {

	void CommandHandler::parse(string& cmdstring) 
	throw(com::IllegalCommandException, 
	      com::ConnectionClosedException)
	{
		// explode string on whitespace
		stringstream ss(cmdstring);
		istream_iterator<string> begin(ss);
		istream_iterator<string> end;
		vector<string> args(begin, end);

		if(args.size() < 1) throw IllegalCommandException();
		
		string cmd = args[0];

		if(cmd == "list") {
			cout << "listing..." << endl;
		}else if(cmd == "read") {
			cout << "reading..." << endl;
		}else if(cmd == "create") {
			cout << "creating..." << endl;
		}else if(cmd == "delete") {
			cout << "deleting..." << endl;
		}else if(cmd == "exit") {
			throw ConnectionClosedException();
		}else if(cmd == "help"){
			cout << "Available commands:" << endl
			<< "  list\t\t\t\t\tList all newsgroups" << endl
			<< "  list <newsgroup>\t\t\tList articles in newsgroup" << endl
			<< "  read <id>\t\t\t\tDisplay article" << endl
			<< "  create <newsgroup>\t\t\tCreate newsgroup" << endl
			<< "  create <title> <author> <body>\tCreate article" << endl
			<< "  delete <ngid>\t\t\t\tDelete newsgroup" << endl
			<< "  delete <ngid> <id>\t\t\tDelete article" << endl;
		}else{
			throw IllegalCommandException();	
		}
	}
}