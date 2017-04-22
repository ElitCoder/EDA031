#include "server.h"
#include "connection.h"
#include "connectionclosedexception.h"
#include "messagehandler.h"
#include "process.h"
#include "invalidprotocolexception.h"

#include <iostream>
#include <limits.h>
#include <algorithm>

using namespace std;

int main(int argc, const char **argv) {
    if(argc < 2) {
        cerr << "Usage: ./newsserver <port>\n";
        
        exit(1);
    }
    
    unsigned short port = -1;
    
    try {
        int intPort = atoi(argv[1]);
        
        if(intPort < 0 || intPort > USHRT_MAX) {
            throw exception();
        }
        
        port = intPort;
    } catch(exception &e) {
        cerr << "Invalid port number. " << e.what() << endl;
        
        exit(1);
    }
    
    bool usingMemory = true;
    
    if(argc > 2) {
        string databaseType = argv[2];
        transform(databaseType.begin(), databaseType.end(), databaseType.begin(), ::tolower);
        
        if(databaseType == "disk") {
            usingMemory = false;
        }
    }
    
    Server server(port);
    
    if(!server.isReady()) {
        cerr << "Server could not start.\n";
        
        exit(1);
    }
    
    else {
        cout << "Server started at port " << port << ".\n";
        cout << "Using database-type: " << (usingMemory ? "memory." : "disk.") << endl;
        cout << "---------------------------------------\n";
    }
    
    MessageHandler messageHandler;
    Process process(usingMemory);
    
    while(true) {
        auto conn = server.waitForActivity();
        
        if(conn != nullptr) {
            try {
                auto &packet = messageHandler.read(conn);
                auto &response = process.process(packet);
                
                messageHandler.send(conn, response);
                
            } catch(ConnectionClosedException &e) {
                server.deregisterConnection(conn);
                
                cout << "Closed client connection.\n";
            } catch(InvalidProtocolException &e) {
                server.deregisterConnection(conn);
                
                cout << "Invalid protocol from client - disconnecting.\n";
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