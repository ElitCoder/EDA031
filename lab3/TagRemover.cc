#include "TagRemover.h"

#include <fstream>

using namespace std;

void TagRemover::remove(ifstream &file, string &input) {
    while(true) {
        while(input.find("<") != string::npos) {
            auto position = input.find("<");
            
            if(position != string::npos) {
                auto end = input.find(">");
                
                if(end != string::npos) {
                    input.erase(position - 1, end - position + 2);
                }
                
                else {
                    input.erase(position - 1, input.length() - position + 1);
                    
                    output += input;
                    
                    string nextLine = input;
                    
                    while(nextLine.find(">") == string::npos) {
                        output += '\n';
                        
                        getline(file, nextLine);
                    }
                    
                    nextLine.erase(0, nextLine.find(">") + 2);
                    input = nextLine;
                    
                    continue;
                }
            }
        }
        
        break;
    }
}

void TagRemover::transform() {
    while(true) {
        bool found(false);
        
        auto position = output.find("&lt;");
        
        if(position != string::npos) {
            output.replace(position, 4, "<");
            
            found = true;
        }
        
        position = output.find("&gt;");
        
        if(position != string::npos) {
            output.replace(position, 4, ">");
            
            found = true;
        }
        
        position = output.find("&nbsp;");
        
        if(position != string::npos) {
            output.replace(position, 6, " ");
            
            found = true;
        }
        
        position = output.find("&amp;");
        
        if(position != string::npos) {
            output.replace(position, 5, "&");
            
            found = true;
        }
        
        if(!found) {
            break;
        }
    }
}

TagRemover::TagRemover(istream &in) {
    string input;
    
    cout << "Enter HTML file: ";
    in >> input;
    
    ifstream file(input);
    
    if(!file) {
        cout << "The file does not exist.\n";
        
        return;
    }
    
    while(getline(file, input)) {
        remove(file, input);
        
        output += input;
        output += '\n';
    }
    
    file.close();
    
    transform();
}

void TagRemover::print(ostream &out) {
    out << output;
}
