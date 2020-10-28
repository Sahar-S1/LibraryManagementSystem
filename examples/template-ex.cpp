#include <iostream>

using namespace std;

template <typename T>
void println(T var) {
    cout << var << endl;
}

int main() {
    println<int>(10);
    println<float>(10.393);
    println<char>('a');

    return 0;
}
