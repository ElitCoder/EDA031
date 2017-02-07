#include "TagRemover.h"

#include <fstream>

using namespace std;

TagRemover::TagRemover(istream &in) {
    string file;
    in >> file;

    ifstream read(file, ios::binary);

    if(!read) {
        cout << "File does not exist.\n";

        return;
    }

    read.seekg(0, ios::end);
    auto size(read.tellg());
    read.seekg(0, ios::beg);

    char *data(new char[size]);
    read.read(data, size);

    read.close();

    m_html = data;
    delete[] data;
}

void TagRemover::print(ostream &out) const {
    string html(m_html);
    bool changed(true);

    while(changed) {
        changed = false;

        auto position = html.find_first_of("<");

        if(position != string::npos) {
            auto end = html.find_first_of(">");

            html.erase(position, end - position + (html[end + 1] == '\n'? 1 : 2));

            changed = true;
        }
    }

    changed = true;

    while(changed) {
        changed = false;

        auto position = html.find("&lt;");

        if(position != string::npos) {
            html.replace(position, 4, "<");

            changed = true;
        }

        position = html.find("&gt;");

        if(position != string::npos) {
            html.replace(position, 4, ">");

            changed = true;
        }

        position = html.find("&nbsp;");

        if(position != string::npos) {
            html.replace(position, 6, " ");

            changed = true;
        }

        position = html.find("&amp;");

        if(position != string::npos) {
            html.replace(position, 5, "&");

            changed = true;
        }
    }

    out << html;
}
