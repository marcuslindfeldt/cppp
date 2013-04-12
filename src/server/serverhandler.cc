#include <iostream>
#include <cstdlib>
#include "server.h"
#include "../database/inmemorydatabase.h"
#include "../database/filesystemdatabase.h"

#include "messageinterpreter.h"
#include "../com/messagehandler.h"
#include "../com/connection.h"

using namespace server;
using namespace com;
using namespace database;
using namespace std;

int main (int argc, char** argv){

    if(argc != 3) {
        cerr << "Wrong arguments provided, usage: myserver port-number " << endl;
        exit(1);
    }
    Server server(atoi(argv[1]));
    if(!server.isReady()) {
        cerr << "Server init failed" << endl;
        exit(1);
    }
    string typeOfDb = argv[1];
    Database* db;
    if(typeOfDb == "memdb" ){
        db = new InMemoryDatabase();

    }
    else if(typeOfDb == "filedb"){
        string basedir("../../data");
        db = new FilesystemDatabase(basedir);

    }
    else {
        cerr << "Database type does not exist" << endl;
    }

    cout << "Server running at port: " << argv[2] << endl;
    while(true){
        Connection* conn = server.waitForActivity();
        MessageHandler mh (conn);
        MessageInterpreter mi(mh, db);
        try {
            if(conn != 0) {
                cout << "Connection established" << endl;
                try {
                mi.interpretAndPerformCmd();

                }
                catch(IllegalCommandException&){
                server.deregisterConnection(conn);
                delete conn;

                }
            }
            else {
                server.registerConnection(new Connection);
                cout << "New Client connected" << endl;
            }
        } catch (ConnectionClosedException&) {
            server.deregisterConnection(conn);
            delete conn;
            cout << "Client closed connection" << endl;
        }
    }

}
