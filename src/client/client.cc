/** client.cc **/
#include "../com/connection.h"
#include "../com/connectionclosedexception.h"
#include "commandhandler.h"
#include "../com/messagehandler.h"
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
  mutable T& n;
  explicit input_t( T& n ): n( n ) { }
  input_t( const input_t <T> & i ): n( i.n ) { }
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
istream& operator >> ( istream& ins, const input_t <T> & i )
  {
  // Read a line (terminated by ENTER|NEWLINE) from the user
  string s;
  getline( ins, s );

  // Get rid of any trailing whitespace
  s.erase( s.find_last_not_of( " \f\n\r\t\v" ) + 1 );

  // Read it into the target type
  istringstream ss( s );
  ss >> i.n;

  // Check to see that there is nothing left over
  if (!ss.eof())
    ins.setstate( ios::failbit );

  return ins;
  }

/**
 * Help text helper struct.
 */

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
		                cout << """listNewsGroup""";
		                break;
		            case com::Protocol::COM_CREATE_NG:
		                cout << """createNewsGroup"" name";
		                break;
		            case com::Protocol::COM_DELETE_NG:
		                cout << """deleteNewsGroup"" name";
		                break;
		            case com::Protocol::COM_LIST_ART:
		                cout << """listArticle"" name";
		                break;
		            case com::Protocol::COM_CREATE_ART:
		                cout << """createArticle"" ArtIDnbr title author text";
		                break;
		            case com::Protocol::COM_DELETE_ART:
		                cout << """deleteArticle"" groupIDnbr ArtIDNbr";
		                break;
		            case com::Protocol::COM_GET_ART:
		                cout << """getArticle"" groupIDnbr ArtIDNbr";
		                break;
		            default:
		                throw com::IllegalCommandException();
		                break;
		        }
        cout << endl;

	}
};


int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Input must be: client-host-name and  port-number" << endl;
        exit(1);
    }
    //Changing of command-interface can be done from client.
    std::map< std::string, com::Protocol > mymap;
    mymap["listNewsGroup"] = com::Protocol::COM_LIST_NG;
    mymap["createNewsGroup"] = com::Protocol::COM_CREATE_NG;
    mymap["deleteNewsGroup"] = com::Protocol::COM_DELETE_NG;
    mymap["listArticle"] = com::Protocol::COM_LIST_ART;
    mymap["createArticle"] = com::Protocol::COM_CREATE_ART;
    mymap["deleteArticle"] = com::Protocol::COM_DELETE_ART;
    mymap["getArticle"] = com::Protocol::COM_GET_ART;

    Connection connection(argv[1], atoi(argv[2]));
    if (! connection.isConnected()) {
        cerr << "Connection attempt failed" << endl;
        exit(1);
    }
    com::MessageHandler messageHandler(connection);
    client::CommandHandler commandHandler(messageHandler);
    StringHelper help;

    while(1){
    help.initialHelp(); //Always display the helper or only when prompted...hmmm...?
    string tmp;
    cin >> input(tmp);
      while (!cin)
        {
        cin.clear();
        cout << "Please, enter only an valid string.> " << flush;
        cin >> input(tmp);
        }
      commandHandler.interpretAndPerformCmd(tmp, mymap);
    }
}
