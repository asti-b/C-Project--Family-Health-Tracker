#include <iostream>
using namespace std;
int main(){
    int i;int *arr;
    int p[]={1,2,3,4,5};
    arr=p;
    for (i=0; i<5; i++){
        cout<< (arr[i]);
    }
    cout <<endl;
    for (i=0; i<5; i++){
        cout<< (i[arr]); 
    }
    cout <<endl;
    // for (i=0; i<5; i++){
    //     cout<< (arr+i);//prints address of all
    //     arr++; 
    // }
    cout <<endl;
    for (i=0; i<5; i++){
        cout<< (*(arr+i));
        
    }
    cout <<endl;
    for (i=0; i<5; i++){
        cout<< *arr;
        arr++; 
    }
    cout <<endl;
}