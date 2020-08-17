#include <iostream>
using namespace std;

int main (void) {
    int someInt = 0;
    cin >> someInt;
    if (someInt == 42) {
      cout << "The answer to the ultime question of life, the universe and everything!";
      return 0;
    }
    cout << "Hello world!";
    return 0;
}
