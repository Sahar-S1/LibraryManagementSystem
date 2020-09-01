#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main() {
    cout << "Output String Stream" << endl;

    ostringstream sout;

    sout << "Hii, ";
    sout << "How are you doing" << endl;
    sout << 25.55;

    cout << sout.str();

    /* .................................. */
    
    cout << "\n\nOutput String Stream" << endl;

    istringstream sin(sout.str());

    string buffer;
    while( getline(sin, buffer) ) {
        cout << buffer << endl;
    }

    
    /* .................................. */
    
    cout << "\n\nOutput String Stream with Deleiminator" << endl;

    istringstream sin2("19203A0013,Anurag Dubey,CO3IA,pass");

    string buffer2;
    while( getline(sin2, buffer2, ',') ) {
        cout << buffer2 << endl;
    }

    return 0;
}
