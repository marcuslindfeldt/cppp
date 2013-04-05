/** client.cc **/
#include "../src/com/connection.h"
#include "../src/com/connectionclosedexception.h"
#include "../src/client/commandhandler.h"
#include "../src/com/messagehandler.h"

#include <iostream>
#include <string>
#include <cstdlib>    /* for exit() and atoi() */

using namespace std;
using com::Connection;
using com::ConnectionClosedException;

struct StringHelper{
	StringHelper();
	void initialHelp(){
		cout << "What do you want to do: (enter the corresponding number, then hit enter)\n"
				"1. List newsgroups\n"
				"2. Create a new newsgroup?\n"
				"3. Delete a newsgroup\n"
				"4. List the articles in a newsgroup\n"
				"5. Create a new article\n"
				"6. Delete an article\n"
				"7. Get an article\n"
				<< endl;
		string tmp;
		while (getline( cin, tmp ) && !tmp.empty())
		{
			//TODO make output here depending on input.
		}

	}
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Input must be: client-host-name and  port-number" << endl;
        exit(1);
    }

    Connection connection(argv[1], atoi(argv[2]));
    if (! connection.isConnected()) {
        cerr << "Connection attempt failed" << endl;
        exit(1);
    }
    com::MessageHandler messageHandler(connection);
    client::CommandHandler commandHandler(messageHandler);
    StringHelper help;

    help.initialHelp(); //Always display the helper or only when prompted...hmmm...?
    string tmp;
    while (getline( cin, tmp ) && !tmp.empty()) { //tmp is empty on enter(?). Break out these string functions into the helper?
        try {
        	//TODO read the full string here.
        }
        catch (ConnectionClosedException&) {
            cerr << "Server closed down!" << endl;
            exit(1);
        }
    }

}
