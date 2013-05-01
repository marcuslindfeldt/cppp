/** client.cc **/
#include "../com/protocol.h"
#include "../com/connection.h"
#include "../com/connectionclosedexception.h"
#include "../client/commandhandler.h"
#include "../com/messagehandler.h"
#include "../client/messageinterpreter.h"
#include "../com/protocol.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <cstdlib>    /* for exit() and atoi() */
#include <map>

using namespace std;
using namespace com;
using namespace client;

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cerr << "usage: client <host> <port>" << endl;
		exit(1);
	}

	// Create a connection 
	Connection* conn = new Connection(argv[1], atoi(argv[2]));
	if ( !conn->isConnected() ) {
        cerr << "Unable to connect" << endl;
        exit(1);
    }

	MessageHandler mh(conn);
	MessageInterpreter mi;
	CommandHandler ch(mh);

	while(true){
		// Display prompt
		cout << "news> ";
		try{
			// parse & perform command
			string cmd;
			getline(cin, cmd);
			if(ch.perform(cmd)){
				// if command successful, wait for result
				mi.interpretAnsAndBuildRes(mh, cout);
			}
		} catch(std::invalid_argument& e){
			cout << "Invalid argument, type \"help\" " 
				 << "for a list of available commands." << endl;
		} catch(IllegalCommandException){
			cout << "Command not defined, type \"help\" " 
				 << "for a list of available commands." << endl;
		} catch (ConnectionClosedException) {
			cout << "Bye" << endl;
			delete conn;
			exit(1);
		}
	}
}
