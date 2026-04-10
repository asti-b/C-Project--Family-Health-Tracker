// #include<iostream>
// #include<cstring>
// using namespace std;
// class ElecBill{
//     private:
// int units;double bill; string name;
// public:
// void get(){
// cout<<"enter the name of the customer\n";
// cin.ignore();
// getline(cin,name);
// cout<<"enter the number of the units consumed by the customer\n";
// cin>>units;
// }
// double calc_bill(){
//     if (units<=100) bill =units *1.5;
//     else if(units<=200) bill= 100*1.5 + (units-100)*2.5;
//     else bill= (100*1.5 )+(100*2.5)+ ((units-200)*4);
//     return bill;
// }

// void put(){
//     cout<<"name \n"<<name<<endl;
//     cout<<"units \n"<<units<<endl;
//     cout<<"total bill \n"<<calc_bill()<<endl;

// }
// };
// int main (){
//     ElecBill e[2];

//     for (int i=0; i<2; i++){
//      e[i].calc_bill();
//     e[i].get();
//     e[i].put();
//     }
// }
// Q4. 
// 4. WAP in C++ to create a class Wall having private data members length and height.
// i. Create a parameterized constructor and a copy constructor to initialize these private
// data members.
// ii. Define a member function to return the area.
// Demonstrate the working of each member function.
// #include<iostream>
// using namespace std;
// class Wall{
// private:
// int length ,height;
// public:
// Wall(){
//  cout<<"enter the length of the wall\n";
//  cin>>length;
//   cout<<"enter the height of the wall\n";
// cin>>height;

// }
// Wall(Wall &obj){
//     length=obj.length;
//     height=obj.height;
//     cout <<"copy constructor"<<length<< height<<endl;
// }
// };
// int main(){
//     Wall obj;
//     Wall obj2(obj);
//     Wall obj3 = obj;
// }
// 5. Create a class String with two private data members:
//  char *s to store a string dynamically, and
//  int size to store the length of the string.
// Define the following:
// i. A parameterized constructor to initialize the string.
// ii. A copy constructor to perform deep copying.
// iii. A destructor to release dynamically allocated memory.
// iv. A member function to display the string.
// #include <iostream>
// #include <string>
// using namespace std;
// class String{
//     char *s;
//     int size;
//     public:
//     // int length(const char *s){
//     //     int l;
//     //     while(s!='\0'){
//     //         l++;
//     //     }
//     //     return l;
//     // }
//     String(const char *s ){
//         size= strlen(s);
//        this-> s=new char[size +1];
//        strcpy(this->s, s);

//     }
//     String(const String &obj){
//         size= obj.size;
//         s=new char [size+1];
//         strcpy(s,obj.s);
//     }
//     void display(){
//         cout<<"String: "<<s <<endl;
//     }
//     ~String(){
//     delete[] s;
// }
// };
 
// int main(){
// cout<<"input a string\n";
// String s1("asti bajaj");
// cout<< "original string";
// s1.display();
// String s2 (s1);
// cout<< "copied string";
// s2.display();
// // cin.ignore();
//  //string *s=new string("asti bajaj"); 
// // getline(cin, *s);
// //cin >> s;

// }
// 6. Create a class BankAccount with the following private data members:
//  char *accountHolder to store the account holder’s name dynamically, and
//  double balance to store the account balance.
// Define the following:
// i. A parameterized constructor to initialize the account details.
// ii. A copy constructor to perform deep copying of the account holder’s name.
// iii. A destructor to release dynamically allocated memory.
// iv. A member function to display account information.

#include<iostream>
using namespace std;
class BankAccount{
char *accountholder;
double balance;
public:
int length(const char *ac){
int l=0;
if (ac[l]!='\0'){
    l++;
}
return l;
}
void copy( char *dest, const char *alreadyinputted ){
int i=0;
while(alreadyinputted[i]!='\0'){
    dest [i] =alreadyinputted[i];
    i++;
} dest[i]='\0';
}
BankAccount(const char *ac, double ba){
int len= length(ac);
accountholder= new char[len+1];
copy(accountholder,ac);
balance= ba;
}
BankAccount(BankAccount &B){
    balance=B.balance;
    int l= length(B.accountholder);
    accountholder= new char[l+1];
    copy(accountholder, B.accountholder);
    
}
void display() {
        cout << "Name: " << accountholder << " Balance: " << balance << endl;
    }
~BankAccount(){
    delete[] accountholder;
}

};
int main(){
    BankAccount t("asti bajaj", 20400.98);
    cout<< "original string";
    t.display();
    BankAccount r(t);
     cout<< "not original string";
    r.display();

}
// #include <iostream>
// using namespace std;

// class Wall {
// private:
//     int *length;
//     int *height;

// public:
//     // Parameterized constructor
//     Wall(int l, int h) {
//         length = new int(l);
//         height = new int(h);
//     }

//     // ❌ Shallow Copy Constructor
//     Wall(const Wall &obj) {
//         length = obj.length;   // same memory address
//         height = obj.height;   // same memory address
//         cout << "Shallow copy constructor called\n";
//     }

//     void setLength(int l) {
//         *length = l;
//     }

//     void display() {
//         cout << "Length: " << *length
//              << " Height: " << *height << endl;
//     }

//     // Destructor
//     ~Wall() {
//         delete length;
//         delete height;
//     }
// };

// int main() {
//     Wall w1(10, 5);
//     Wall w2(w1);   // shallow copy
//     w2.setLength(20);

//     cout << "w1: ";
//     w1.display();   // ❗ ALSO changes
//     cout << "w2: ";
//     w2.display();

//     return 0;
// }
