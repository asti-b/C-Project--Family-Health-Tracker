#include <iostream>
using namespace std;

class Cricketer {
public:
    string name;
    int runs;
    float avg;

    Cricketer(string name, int runs, float avg) {
        this->name = name;
        this->runs = runs;
        this->avg = avg;
    }
};

int main() {
    // Creating objects using the constructor
    Cricketer c1("Virat Kohli", 25000, 55.2);
    Cricketer c2("Rohit Sharma", 18000, 47.8);

    int x = 4;
    int &y = x;
    int *b=&x;

    // Printing the memory addresses of variables x and y
    cout << &x << endl;
    cout << &y << endl;
    cout << y << endl;
     cout << &b << endl;
    cout << b<< endl;
     cout << *b << endl;


    return 0;
}