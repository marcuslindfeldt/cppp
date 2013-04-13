/** client.cc **/
#include "../com/protocol.h"
#include "../com/connection.h"
#include "../com/connectionclosedexception.h"
#include "../client/commandhandler.h"
#include "../com/messagehandler.h"
#include "../client/messageinterpreter.h"
#include "../com/protocol.h"

#include <iostream>
#include <string>
#include <cstdlib>    /* for exit() and atoi() */
#include <map>

using namespace std;
using com::Connection;
using com::ConnectionClosedException;
using com::Protocol;

/**
 * Input formatting helper functions.
 */

template <typename T>
struct input_t
{
	T& n;
	explicit input_t( T& n ): n( n ) {}
	input_t( const input_t <T> & i ): n( i.n ) {}
};

template <typename T>
inline
input_t <T>
input( T& n )
{
	input_t <T> result( n );
	return result;
}

template <typename T>
istream& operator >> ( istream& ins, const input_t <T> & input )
{
	// Read a line ended by newline
	string str;
	getline( ins, str );

	// Read it into the type that is the target
	istringstream ss( str );
	ss >> input.n;

	// Check to see that there is nothing left over
	if (!ss.eof())
		ins.setstate( ios::failbit );

	return ins;
}

/**
 * Help text helper struct.
 */

struct StringHelper{
	void initialHelp(char delim){
		cout << "\n\n\nWhat do you want to do: (enter the corresponding number, then hit enter)\n"
				"1. List newsgroups\n"
				"2. Create a new newsgroup?\n"
				"3. Delete a newsgroup\n"
				"4. List the articles in a newsgroup\n"
				"5. Create a new article\n"
				"6. Delete an article\n"
				"7. Get an article\n"
				<< endl;
		int tmp;
		cin >> input(tmp);
		while (!cin)
		{
			cin.clear();
			cout << "Please, enter only an valid integer.> " << flush;
			cin >> input(tmp);
		}
		cout << "Input is of the form: \n";
		switch(tmp){
		case com::Protocol::COM_LIST_NG:
			cout << """listnewsgroup""" << endl;;
			break;
		case com::Protocol::COM_CREATE_NG:
			cout << """createnewsgroup""" << delim << "name" << endl;
			break;
		case com::Protocol::COM_DELETE_NG:
			cout << """deletenewsgroup""" << delim << "name" << endl;
			break;
		case com::Protocol::COM_LIST_ART:
			cout << """listarticle""" << delim << "name" << endl;
			break;
		case com::Protocol::COM_CREATE_ART:
			cout << """createarticle""" << delim << "ArtIDnbr" << delim << "title" << delim << "author" << delim << "text" << endl;
			break;
		case com::Protocol::COM_DELETE_ART:
			cout << """deletearticle""" << delim << "groupIDnbr" << delim << "ArtIDNbr" << endl;
			break;
		case com::Protocol::COM_GET_ART:
			cout << """getarticle""" << delim << "groupIDnbr" << delim << "ArtIDNbr" << endl;
			break;
		default:
			throw com::IllegalCommandException();
			break;
		}
		cout << endl << endl;

	}
};


int main(int argc, char* argv[]) {
	if (argc != 3) {
		cerr << "Input must be: client-host-name and  port-number\n" << endl;
		exit(1);
	}
	//Changing of command-interface can be done from client.
	std::map< std::string, int > mymap;

    mymap["listnewsgroup"] = com::Protocol::COM_LIST_NG;
    mymap["createnewsgroup"] = com::Protocol::COM_CREATE_NG;
    mymap["deletenewsgroup"] = com::Protocol::COM_DELETE_NG;
    mymap["listarticle"] = com::Protocol::COM_LIST_ART;
    mymap["createarticle"] = com::Protocol::COM_CREATE_ART;
    mymap["deletearticle"] = com::Protocol::COM_DELETE_ART;
    mymap["getarticle"] = com::Protocol::COM_GET_ART;

	char delim = '-';
	com::Connection connection(argv[1], atoi(argv[2]));
	if (! connection.isConnected()) {
        cerr << "Connection attempt failed" << endl;
        exit(1);
    }
	com::Connection* connect = &connection;
	com::MessageHandler messageHandler(connect);
	client::MessageInterpreter msginterp;
	client::CommandHandler commandHandler;
	StringHelper help;
	cout << "Enter ""help"" for help on arguments" << endl;
	while(1){
		try{
			cout << endl;
			cout << "What do you want to do?" << endl;
			string tmp;
			cin >> input(tmp);
			if(cin && tmp == "help"){
				help.initialHelp(delim); //Always display the helper or only when prompted...hmmm...?
				cin >> input(tmp);
			}
			while (!cin)
			{
				cin.clear();
				cout << "Please, enter only an valid string.\n> " << flush;
				cin >> input(tmp);
			}
			commandHandler.interpretAndPerformCmd(messageHandler, tmp, mymap, delim);
			msginterp.interpretAnsAndBuildRes(messageHandler, std::cout);
		} catch(com::IllegalCommandException&){
			cout << "That was an illegal command!" << endl;
		} catch (com::ConnectionClosedException&) {
			cout << "The connection has been terminated" << endl;
			return(0);
		}
	}
}
