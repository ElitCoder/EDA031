#include "server.h"
#include "connection.h"
#include "connectionclosedexception.h"
#include "messagehandler.h"

#include <iostream>

using namespace std;

int main(int argc, const char **argv) {
    if(argc < 2) {
        cerr << "Usage: ./newsserver <port>\n";
        
        exit(1);
    }
    
    unsigned short port = -1;
    
    try {
        port = stoi(argv[1]);
    } catch(exception &e) {
        cerr << "Invalid port number. " << e.what() << endl;
        
        exit(1);
    }
    
    Server server(port);
    
    if(!server.isReady()) {
        cerr << "Server could not start.\n";
        
        exit(1);
    }
    
    MessageHandler messageHandler;
    
    while(true) {
        auto conn = server.waitForActivity();
        
        if(conn != nullptr) {
            try {
                messageHandler.read(conn);
            } catch(ConnectionClosedException &e) {
                server.deregisterConnection(conn);
                
                cout << "Closed client connection.\n";
            }
        }
        
        else {
            conn = make_shared<Connection>();
            server.registerConnection(conn);
            
            cout << "New client connected.\n";
        }
    }
    
    return 0;
}