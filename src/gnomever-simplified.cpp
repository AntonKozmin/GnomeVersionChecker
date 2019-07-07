//============================================================================
// Bob: "you i i i i i everything else . . . . . . . . . . . . . ."
// A simple version but too much big after compilation
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

int main()
{
    string GnomeVerFILE=R"(/usr/share/gnome/gnome-version.xml)";
    ifstream fs(GnomeVerFILE);
    if (fs.is_open())
    {
        string outLine,resLine;
        regex numregex(R"(>[0-9]\d*<)");
        smatch sm;

        for (string str; getline(fs, str);) outLine+=str;

        while(regex_search(outLine, sm, numregex))
        {
            string ts=sm.str();
            ts.erase(0,1);
            ts.pop_back();
            resLine+=ts;
            resLine.append(1,'.');
            outLine=sm.suffix();
        }
        resLine.pop_back();
        cout<<resLine<<endl;
    }
    else cout << "?.?.?"<<endl;
    return 0;
}
