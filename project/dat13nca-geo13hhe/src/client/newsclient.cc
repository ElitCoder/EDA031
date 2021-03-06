#include "connection.h"
#include "commander.h"
#include "process.h"
#include "input.h"
#include "connectionclosedexception.h"
#include "invalidinputexception.h"

#include <iostream>
#include <limits.h>

using namespace std;

int main(int argc, char **argv) {
    if(argc != 3) {
        cerr << "Usage: ./newsclient host port\n";
        
        exit(1);
    }
    
    unsigned short port = 0;
    
    try {
        int intPort = stoi(argv[2]);
        
        if(intPort < 0 || intPort > USHRT_MAX) {
            throw exception();
        }
        
        port = intPort;
    } catch(exception &e) {
        cerr << "Invalid port number. " << e.what() << endl;
        
        exit(1);
    }
    
    shared_ptr<Connection> conn(new Connection(argv[1], port));
    
    if(!conn->isConnected()) {
        cerr << "Connection attempt failed.\n";
        
        exit(1);
    }
    
    Commander commander(conn);
    Process process(conn);
    
    while(true) {
        cout << "Welcome to the news!\n\n";
        cout << "Available commands:\n";
        cout << "1. List newsgroups.\n";
        cout << "2. Create a newsgroup.\n";
        cout << "3. Delete a newsgroup.\n";
        cout << "4. List articles in newsgroup.\n";
        cout << "5. Create an article.\n";
        cout << "6. Delete an article.\n";
        cout << "7. Get an article.\n";
        cout << "8. Quit.\n";
        cout << "\n: ";
        
        try {
            int input = Input::getInt();
            cout << endl;
        
            switch(input) {
                case 8: exit(1);
                    break;
                    
                case 1: commander.listNewsgroups();
                    break;
                    
                case 2: commander.createNewsgroup();
                    break;
                    
                case 3: commander.deleteNewsgroup();
                    break;
                    
                case 4: commander.listArticles();
                    break;
                    
                case 5: commander.createArticle();
                    break;
                    
                case 6: commander.deleteArticle();
                    break;
                    
                case 7: commander.getArticle();
                    break;
                    
                default:
                    {
                        cout << "Invalid input, write something understandable. (press enter to continue)";
                        cin.get();
                        
                        cout << "\n";
                        
                        continue;
                    }
            }
        } catch(InvalidInputException &e) {
            cout << "\nInvalid input format, please try again. (press enter to continue)";
            cin.get();
            
            cout << "\n";
            
            continue;
        }
        
        try {
            process.process();
            
            cin.get();
            cout << endl;
        } catch(ConnectionClosedException &e) {
            cout << "\n\n** Lost connection to server **\n\n";
            
            exit(1);
        }
    }
}