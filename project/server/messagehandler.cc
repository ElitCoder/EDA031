#include "messagehandler.h"
#include "protocol.h"

#include <iostream>

using namespace std;

void MessageHandler::read(const shared_ptr<Connection> &conn) {
    unsigned char command = conn->read();
    
    cout << "Received command: " << command << endl;
    
    switch(command) {
        case Protocol::COM_LIST_NG:
            {
                cout << "Recevied list-command.\n";
            }
            break;
    }
    
    process(conn);
}

void MessageHandler::process(const shared_ptr<Connection> &conn) {
}