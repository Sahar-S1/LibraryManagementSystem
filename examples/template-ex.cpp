#include <iostream>

using namespace std;

template <typename T> void println(T var) {
    cout << var << endl;
}

int main() {
    println(1);
    println(22.25);
    println("Hii");
    println(false);

    return 0;
}
