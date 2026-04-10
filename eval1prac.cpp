// 6. Create a class BankAccount with the following private data members:
//  char *accountHolder to store the account holder’s name dynamically, and
//  double balance to store the account balance.
// Define the following:
// i. A parameterized constructor to initialize the account details.
// ii. A copy constructor to perform deep copying of the account holder’s name.
// iii. A destructor to release dynamically allocated memory.
// iv. A member function to display account information.
//Q1
// #include <iostream>
// #include <string>
// using namespace std;
// class StudentRecord{
//     int rollNo;
//     char *name;
//     int *marks;
//     int numSubjects;
//     public:
//     int length (const char *n){
//         int l;
//         while(n[l]!='\0'){
//             l++;
//         }
//         return l;
//     }
//     StudentRecord(int rno, const char *n, int *m , int noOfSub){
//     rollNo= rno;
//     numSubjects=noOfSub;
//     int len= length(n);
//     name= new char[len+1];
//     strcpy(name, n);
//     marks =new int [numSubjects];
//     readMarks(numSubjects, marks);



//     }
//     void readMarks(int n, int *marks ){
//         cout <<"enter the marks of student in :";
//         for (int i=0; i<n; i++){
//              cin>> marks[i];
//         }
//     }
//      void showDetails(int n){
//         cout <<"Name: "<<name<<endl<< "Roll No: "<<rollNo<<endl;
//          for (int i=0; i<n; i++){
//              cout<< marks[i]<<endl;
//         }
//     }
//     ~StudentRecord ()
//     {
//         delete[] name;
//         delete[ ]marks;
//     }
// };
// int main(){

//     int r, noOfsub; 
//     string n ;
//     int *mark;
//     cout <<"enter the no of subjects for the student\n";
//     cin>> noOfsub;
//         cout <<"enter the rno of student\n";
//     cin>>r;
//     // cin.ignore();
//     // getline(cin,n);
// StudentRecord s1 ( r ,"asti" ,mark,noOfsub);
//    s1.showDetails(noOfsub);

// }
// #include <iostream>
// #include <string>
// using namespace std;
// class Moviecollection{
// struct Movie{
//     char *title;
//     int year;
//     float rating;
// };
// Movie *movies;
// int capacity;
// int count;
// public:
// Moviecollection( int cap){
// capacity=cap;
// count=0;
// movies = new Movie[capacity];
// }
// ~Moviecollection(){
//     for (int i=0; i<count ; i++){
//         delete[] movies[i].title;
//     }
//     delete[] movies ;
// }
// bool addMovie (const char *t, int y, float r ){
//     if (count <capacity){
//         movies[count].title= new char[strlen(t)+1];
//     strcpy(movies[count].title,t);
//         movies[count].year=y;
//         movies[count].rating=r;
//         count++;
//         return true ;
//     }
//     return false;
// }
// void showall() const{
//     for (int i=0;i<count ;i++){
//         cout << i + 1 << ". " << movies[i].title << " (" 
//                  << movies[i].year << ") - " << movies[i].rating << "/10" << endl;
        
//     }
// }
// void showBest() const {
//         if (count == 0) return;
//         int bestIdx = 0;
//         for (int i = 1; i < count; i++) {
//             if (movies[i].rating > movies[bestIdx].rating) {
//                 bestIdx = i;
//             }
//         }
//         cout << "Best Movie: " << movies[bestIdx].title << endl;
//     }
// };
// int main(){
//     int maxMovies;
//     cout << "Enter the maximum number of movies to store: ";
//     cin >> maxMovies;
//     //1. Dynamically create one MovieCollection object
//     Moviecollection* myCollection = new Moviecollection(maxMovies);
//     myCollection->addMovie("Inception", 2010, 8.8);
//     myCollection->addMovie("The Dark Knight", 2008, 9.0);
//     myCollection->addMovie("Interstellar", 2014, 8.6);
//     cout << "\n--- Full Movie Collection ---" << endl;
//     myCollection->showall();
//     // 4. Show best rated (Task: Show best rated movie)
//     cout << "\n--- Top Rated Selection ---" << endl;
//     myCollection->showBest();

//     // 5. Cleanup (Task: Exit/Delete the object)
//     // This triggers the Destructor to delete each title and the movies array
//     delete myCollection; 
    
//     cout << "\nMemory successfully deallocated. Program ending." << endl;

//     return 0;
// }
// Online C++ compiler to run C++ program online
// #include <iostream>
// #include <cstring>

//     // Write C++ code here
//     using namespace std;
//     class MovieCollection{
//         struct Movie {
// char* title;
// int year;
// float rating;};
//     Movie *m;
//     int capacity,count;
//     public:
//     MovieCollection(int cap){
//         capacity = cap;
//         m=new Movie  [capacity];
//     }
//     void addMovie(const char *t, int y, float r ){
//         if (count <capacity){
//        m[count].title=new char[strlen(t)+1];
//            strcpy(m[count].title,t);
//         m[count].year=y;
//         m[count].rating=r ;
//         count ++;
//     }
//         return;
//     }
//     void showall(){
//         for 
//         (int i=0; i<count; i++){
//             cout << i+1<< " title "<<m[i].title<<" year "<<m[i].year<<" rating "<<m[i].rating ;
//         }
//     }
//     ~MovieCollection(){
//          for (int i=0; i<count ; i++){
//         delete[] m[i].title;
//     }
//     delete[] m ;
//     }
//     };
    
//     int main() {    int maxMovies;
//     cout << "Enter the maximum number of movies to store: ";
//     cin >> maxMovies;
//     //1. Dynamically create one MovieCollection object
//     MovieCollection* myCollection = new MovieCollection(maxMovies);
//     myCollection->addMovie("Inception", 2010, 8.8);
//     myCollection->addMovie("The Dark Knight", 2008, 9.0);
//     myCollection->addMovie("Interstellar", 2014, 8.6);
//     return 0;
// }
// #include <iostream>
// #include <string>
// using namespace std;
// class Student{
//     private:
//     int rollNo;
//     char* name;
//     float cgpa;
//     public:
//     int length(const char *ac){
//         int l=0;
//         while (ac[l]!='\0'){
//             l++;
//         }
//         return l;
//     }
//     void copy(char *dest,const char*src, int l){
// int i=0;
// while(src[i] != '\0'){            dest[i]=src[i];
//       dest[i] = src[i];
//         i++;  }
//         dest[i] = '\0';
//     }
//     Student(int rno, const char* n, float cg){
//         name=new char [length(n)+1];
//         copy (name, n, length(n));
//         rollNo= rno;
//         cgpa =cg;
//     }
//     void display(){
//         cout <<"ROLL NO.\n"<<rollNo<<"\n NAME\n"<<name<<"\nCGPA"<<cgpa;
//     }
//     int getrollnumber(){
//         return rollNo;
//     }
//     ~Student (){
//         delete[] name;
//     }
// };
// int main(){
//     int n;
//     cout <<"enter the number of objects"<<endl;
//     cin>>n;
//     Student** s= new Student *[n];
//     for (int i=0; i<n; i++){
//            int rno;
//         float cg;
//         char temp[50];
//         cout << "\nEnter details for student " << i + 1 << endl;
//         cout << "Roll No: ";
//         cin >> rno;
//         cout << "Name: ";
//         cin >> temp;
//         cout << "CGPA: ";
//         cin >> cg;

//         s[i] = new Student(rno, temp, cg);

//     }
//     cout << "\n--- Student Records ---\n";
//     for (int i = 0; i < n; i++) {
//         s[i]->display();
//         cout << endl;
//     }

//     // Free memory
//     for (int i = 0; i < n; i++) {
//         delete s[i];
//     }
//     delete[] s;

//     return 0;

// }
// #include<iostream>
// using namespace std;
// class StudentResult{
//     int *marks;
//     int noOfSub;
//     public:
//     StudentResult(int n){
//         noOfSub=n;
//         marks = new int [noOfSub];
//     }
//     void inputMarks() {
//         for (int i = 0; i < noOfSub; i++) {
//             do {
//                 cout << "Enter marks for subject " << i + 1 << ": ";
//                 cin >> marks[i];
//             } while (marks[i] < 0 || marks[i] > 100);
//         }
//     }

//     void calculate (int n){
//         cout<<"Marks of the student is\n";
//         int sum=0;
//         for (int i=0; i<n; i++){
//             cout <<marks[i]<<endl;
//             sum+=marks[i];
//         }
//         cout<<"total marks are: "<<sum;
//         float avg = (float)sum / noOfSub;
//         cout <<"average marks are: "<< avg;
//         if (avg >= 75) cout << "\nGrade: A";
//         else if (avg >= 60) cout << "\nGrade: B";
//         else if (avg >= 50) cout << "\nGrade: C";
//         else cout << "\nGrade: F";
//     }
//     ~StudentResult(){
//     //      for (int i=0; i<noOfSub; i++){
//     //         delete marks[i];
//     delete []marks; }

// };
// int main(){
//     cout<<"enter the number of subjects \n";int n;
//     cin>>n;
//     StudentResult t(n);
// //      cout<<"enter the number of students \n";int no;
// //     cin>>no;
// //     StudentResult** S= new StudentResult*[no];
// //     for (int i = 0; i < no; i++) {
// //         S[i]=new StudentResult(n);
// //        S[i]->inputMarks();  }

// //  cout << "\n--- Student Records ---\n";
// //     for (int i = 0; i < n; i++) {
// //         S[i]->calculate( no);
// //         cout << endl;
// //     }
// // for (int i = 0; i < no; i++) {
// //         delete S[i];
// //     }
// //     delete[] S;

//     return 0;}
#include <iostream>
using namespace std;

class StartupMessage{
    char *message ;
    public:
    int length(char *pre){
        int l=0;
        while(pre[l]!='\0'){
            l++;
        }
        return l;}
        void copy (char *dest, char *src){
            int i=0;
            while (src[i]!='\0'){
                dest[i]=src[i];
                i++;
            }dest[i]='\0';
        }
 StartupMessage( const char * pre ){
    int len=length(pre);
    message= new char [len+1];
    copy(message,pre);
 }
 void display(){
    cout<<"current message is :"<<message<<endl;
 }
 void update(){
    // cout <<"enter the string to be updated ";
    // char arr[50];
    // cin>>arr;
    // copy(message, arr);
    cout << "Enter new startup message: ";
        cin.ignore();
        char temp[100];
        cin.getline(temp, 100);

        delete[] message;
        int len = length(temp);
        message = new char[len + 1];
        copy(message, temp);
    cout << "Startup message updated successfully.\n";
 }
 void reset(){
    // cout <<"enter the string to be updated ";
    // char arr[50];
    // cin>>arr;
    // copy(message, arr);
    const char *defaultMsg = "System is starting... Please wait.";

        delete[] message;
        int len = length(defaultMsg);
        message = new char[len + 1];
        copy(message, defaultMsg);

        cout << "Startup message reset successfully.\n";
 }
 void exit(){
    cout <<"exiting the program "<<endl;
 }
 ~StartupMessage(){
    delete[] message;
 }
};
int main(){
    cout <<"enter the choice ";
    int ch;
    cin>>ch;
    switch(ch){
        case 1:    StartupMessage s("system is starting please wait");
        break;
        case2
    }
}