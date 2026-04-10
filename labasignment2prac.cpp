// #include<iostream>
// #include<cstring>
// using namespace std;
// class BankAccount{
//     private:

// string name;
// int acno;
// double balance;
// public:
// void assign(){
//     cout<<"enter the name of account holder\n";
//     cin>>name;
//     cout<<"enter the account number of account holder\n";
//     cin>>acno;
//     cout <<"enter the account balance\n";
//     cin>>balance;
// }
// void deposit(int amt){
// balance+=amt;
// }
// void withdraw(int amt){
//     if (balance >(amt +1000)){
//         balance-= amt;
//     }
//     else cout<<"insufficient balance\n";
// }
// void display(){

//     cout<<"Name: "<<name<<"\n"<<"Balance: "<<balance<<"\n";
// }
// };
// int main(){
//     BankAccount B;
//     int w;cout<<"enter the amount to be deposited\n";cin>>w;

//     int a;cout<<"enter the amount to be deposited\n";cin>>a;
//     B.assign();
//     B.deposit(a);
//     B.withdraw(w);
//     B.display();
// }
 #include<iostream>
 #include<cstring>
 using namespace std;
 class Vector{
     private:
     int size;
     float *arr;
     public:
     
     Vector (int n){
    size = n;
    arr = new float[size];
     }
     void input(){
    for(int i = 0; i < size; i++) {
        cin >> arr[i];
    }
}
    void addScalar(float x) {
    for(int i = 0; i < size; i++) {
        arr[i] += x;
    }
}
void multiplyScalar(float x) {
    for(int i = 0; i < size; i++) {
        arr[i] *= x;
    }
}
void display() {
    cout << "(";
    for(int i = 0; i < size; i++) {
        cout << arr[i];
        if(i != size - 1)
            cout << ", ";
    }
    cout << ")";
}
    ~Vector() {
    delete[] arr;
    }
 };
 int main() {
    int n;
    cout << "Enter size of vector: ";
    cin >> n;

    Vector v(n);

    v.input();

    float x;
    cout << "Enter scalar to add: ";
    cin >> x;
    v.addScalar(x);

    cout << "Enter scalar to multiply: ";
    cin >> x;
    v.multiplyScalar(x);

    v.display();
    return 0;
}