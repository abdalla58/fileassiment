#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;
class employee{
    char Employee_ID[13];
    char Employee_Dept_ID[13];
    char Employee_Name[50];
    char Employee_postion[50];
    fstream emp;


public:
    employee(){}
    void addemp(char id[],char d_id[],char name[], char position[]){
      strcpy(Employee_ID,id) ;
        strcpy_s(Employee_Dept_ID,d_id);
        strcpy_s(Employee_Name,name);
        strcpy_s(Employee_postion,position);
       emp.open("employee.txt",ios::out);
        emp<<Employee_ID<<","<<Employee_Dept_ID<<","<<Employee_Name<<","<<Employee_postion<<"#";
      //  emp.close();

    }
};
class department{
    char Dept_ID[30];
    char Dept_Name[50];
    char Dept_Manger[50];
    fstream dept;


public:
    void adddept(char id[], char name[], char mang[] ){
        strcpy(Dept_ID,id) ;
        strcpy_s(Dept_Name,name);
        strcpy_s(Dept_Manger,mang);

        dept.open("employee.txt",ios::out);
        dept<<Dept_ID<<","<<Dept_Name<<","<<Dept_Manger<<"#";
        // dept.close();

    }
};

int main() {
    employee e;
    department d;
    e.addemp("12","is","ahmed","student");
    d.adddept("1","is","ahmed");

    return 0;
}
