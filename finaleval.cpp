#include <iostream>
using namespace std;
int getlength (const char * str){
    int l=0;
while (str[l]!='\0'){
    l++;
}return l;
}
void copy( char * dest, const char *src){
    int i=0;
    while (src[i]!='\0'){
        dest[i]=src[i];
        i++;
    } dest[i]='\0';
}class StudentRecord{
    int rollNo;
    char *name;
    int *marks;
    int numSubjects;
    public :
    StudentRecord (int r, const char *n, int subcount){
        rollNo=r;
        numSubjects= subcount;
        name= new char [getlength(n)+1];
        copy(name,n);
        marks =new int [numSubjects];
    }
    int getRollNo () const {
        return rollNo;
    }
    void Readmarks (){
        for (int i=0;i <numSubjects;i++){
            cout <<"enter the marks of the student in subject "<<i+1<<endl;
            cin >>marks[i];
        }
    }
    void show(){
        int tot=0;
        cout <<"\n Roll No "<<rollNo<<" Name:"<<name;
    for (int i=0;i <numSubjects;i++){
        cout <<"Subject "<<i+1<<": "<<marks[i]<<endl;
        tot+=marks[i];
    }}
    ~StudentRecord (){
delete[] name;
delete[] marks ;
cout << "Memory deallocated for Roll No: " << rollNo << endl;
    }
    
};
int main (){
    int count ;
    cout <<"enter the total no of students \n";
    cin>> count;
    StudentRecord ** classList= new StudentRecord*[count];
    for (int i=0; i<count ;i++){
        char temp[50];
        int rno, sub;
        cout <<"for student "<<i+1<<"\n";
        cout <<"enter the roll no"<<endl;
        cin>>rno;
        cout <<"enter the name"<<endl;
        cin>>temp;
        cout <<"enter no of subjects"<<endl;
        cin >>sub;
        classList[i]= new StudentRecord(rno, temp,sub);
        classList[i]->Readmarks();}

        int searchroll;
        cout <<"enter the roll no to be searched\n";
        cin>> searchroll;
        for (int i=0; i<count ;i++){
            if (classList[i]->getRollNo()==searchroll){
                classList[i]->show();
                break;

            }
        }
    
    for (int i=0; i<count; i++){
        delete classList[i];
    }
    delete[] classList;
    return 0;
}