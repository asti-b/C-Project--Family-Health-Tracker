// // 1. Define a structure Student with members: rollNo, name, marks in 3 subjects. Write a
// // program to:
// //  Input details of n students
// //  Calculate total and average marks
// //  Display the result for a given rollNo OR name
// #include <iostream>
// using namespace std;
// struct Student
// {
// int rno;string name; int m1,m2,m3;
// };//remember ;
// int main(){
//     cout<<"enter the number of students \n";
//     int n;
//     cin>>n;
//     Student S[n]; int i;
//     for(i=0; i<n; i++){
//         cout <<"enter the roll number of the student\n";
//         cin>>S[i].rno;
//         cin.ignore();
//         cout <<"enter the name of the student\n";
//         getline(cin,S[i].name);

//         cout <<"enter the marks of the student in first subject\n";
//         cin>>S[i].m1;
//         cout <<"enter the marks of the student in second subject\n";
//         cin>>S[i].m2;
//         cout <<"enter the marks of the student in third subject\n";
//         cin>>S[i].m3;
//     }
// }
// 2. Create a structure Employee containing: empId, name, basicSalary. Calculate and display:
//  HRA (20% of basic)
//  DA (10% of basic)
//  Gross Salary
//  Name of employee with highest paid salary
//  Basic salary of an employee given his Id OR name
#include <iostream>
#include <string>
using namespace std;
struct Employee{
string empId;
string name;
double basicSalary;

};
double hra( Employee s){
return (0.2* s.basicSalary);
}
double da( Employee s){
return (0.1* s.basicSalary);
}
double grosssalary( Employee s){
return s.basicSalary+ da(s)+hra(s);
}
int main(){
        int n;
    cout << "Enter number of employees: ";
    cin >> n;

    Employee E[n];

    // input employee details
    for (int i = 0; i < n; i++) {
        cout << "\nEnter Employee ID: ";
        cin >> E[i].empId;

        cout << "Enter Name: ";
        cin >> E[i].name;

        cout << "Enter Basic Salary: ";
        cin >> E[i].basicSalary;
    }
cout <<"basic details of the employee are:\n";
for (int i=0; i<n; i++){
    cout <<"employee name: "<<E[i].name<<endl;
    cout<<"HRA: "<<hra(E[i])<<endl;
    cout<<"DA: "<<da(E[i])<<endl;
    cout<<"GROSS: "<<grosssalary(E[i])<<endl;
}
int m=0;
//maximum paid employee
for (int i=0; i<n; i++){
if (grosssalary(E[i])>grosssalary(E[m])){
    m=i;
}
}
cout <<"the highest paid employee is "<<E[m].name<<" the salary is "<<grosssalary(E[m])<<endl;
cout <<"enter the id or name of the employee\n";
int id ;
cin >>id ;
for (int i=0; i<n; i++){
    if (E[i].empId== E[id].empId){
        cout << "Basic Salary of " << E[i].name
                 << " is " << E[i].basicSalary << endl;
            break;
    }
}
}