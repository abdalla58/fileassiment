#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include<bits/stdc++.h>
using namespace std;
class employee{
public:
    char Employee_ID[13];
    char Employee_Dept_ID[13];
    char Employee_Name[50];
    char Employee_postion[50];
    fstream emp;


public:
    employee(){}
    employee(const employee &obj){}
    void addemp(char id[],char d_id[],char name[], char position[]){
        strcpy(Employee_ID,id) ;
        strcpy_s(Employee_Dept_ID,d_id);
        strcpy_s(Employee_Name,name);
        strcpy_s(Employee_postion,position);
        emp.open("employee.txt",ios::out);
        emp<<Employee_ID<<","<<Employee_Dept_ID<<","<<Employee_Name<<","<<Employee_postion<<"#";
        emp.close();

    }
};
struct PIndex {
    int RRN;
    char Employee_ID[13];
    bool operator<(const PIndex &r) const { // for the sort function
        return strcmp(Employee_ID, r.Employee_ID) < 0;
    }
};
struct SIndex {
    char Employee_Dept_ID[13];
    char Employee_Name[50];
    bool operator<(const SIndex &r) const { // for the sort function
        if (strcmp(Employee_Name, r.Employee_Name) == 0)
            return strcmp(Employee_Dept_ID, r.Employee_Dept_ID) < 0;
        return strcmp(Employee_Name, r.Employee_Name) < 0;
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
        dept.close();

    }
};
struct PIndexdept {
    int RRN;
    char Dept_ID[30];
    bool operator<(const PIndexdept &r) const { // for the sort function
        return strcmp(Dept_ID, r.Dept_ID) < 0;
    }
};
struct SIndexdept {
    char Dept_ID[30];
    char Dept_Name[50];
    bool operator<(const SIndexdept &r) const { // for the sort function
        if (strcmp(Dept_Name, r.Dept_Name) == 0)
            return strcmp(Dept_ID, r.Dept_ID) < 0;
        return strcmp(Dept_Name, r.Dept_Name) < 0;
    }
};
employee GetEmployee(int RNN, fstream &infile) {
    employee employee;
    infile.seekg(RNN * 40, ios::beg);
    infile.read((char*) &employee, sizeof employee);
    return employee;
}
int GetRecordRRN(PIndex PrmIndxArray[], int numRec, string ID) {
    int RRN = -1;
    int low = 0, mid, high = numRec - 1;

    while (low <= high) {
        mid = (low + high) / 2;
        if (ID < PrmIndxArray[mid].Employee_ID)
            high = mid - 1;
        else if (ID > PrmIndxArray[mid].Employee_ID)
            low = mid + 1;
        else {
            RRN = PrmIndxArray[mid].RRN;
            break;
        }
    }
    return RRN;
}

string GetEmployeeID(SIndex ScndIndxArray[], int numRec, string Name) {
    string ID = "";
    int low = 0, mid, high = numRec - 1;

    while (low <= high) {
        mid = (low + high) / 2;
        if (Name < ScndIndxArray[mid].Employee_Name)
            high = mid - 1;
        else if (Name > ScndIndxArray[mid].Employee_Name)
            low = mid + 1;
        else {
            ID = ScndIndxArray[mid].Employee_Dept_ID;
            break;
        }
    }
    return ID;
}
void WritePrimIndex(PIndex PrmIndxArray[], int numRec, fstream&outfile) {
    for (int i = 0; i < numRec; i++)
        outfile.write((char*) &PrmIndxArray[i], sizeof PrmIndxArray[i]);
}
void ReadPrimIndex(PIndex PrmIndxArray[], int numRec, fstream& inFile) {
    for (int i = 0; i < numRec; i++)
        inFile.read((char*) &PrmIndxArray[i], sizeof PrmIndxArray[i]);
}
void WriteScndIndex(SIndex ScndIndxArray[], int numRec, fstream&outfile) {
    for (int i = 0; i < numRec; i++)
        outfile.write((char*) &ScndIndxArray[i], sizeof ScndIndxArray[i]);
}
void ReadScndIndex(SIndex ScndIndxArray[], int numRec, fstream& inFile) {
    for (int i = 0; i < numRec; i++)
        inFile.read((char *) &ScndIndxArray[i], sizeof ScndIndxArray[i]);
}
int AddStudents() {   //// To be updated
    fstream file, PrimIndex, ScndIndex;

    file.open("employee.txt", ios::out);
    PrimIndex.open("Primary.txt", ios::out);
    ScndIndex.open("Secondry.txt", ios::out);

    int numRec;
    cout << "Enter Number Of Input Records:";
    cin >> numRec;
    PIndex *PrmIndxArray = new PIndex[numRec];
    SIndex *ScndIndxArray = new SIndex[numRec];
    employee *employees = new employee[numRec];

    for (int i = 0; i < numRec; i++) {
        employee emp;
        cout << endl << "Enter employee " << i + 1 << " ID (Max 13 Letters):";
        cin >> emp.Employee_ID;
        cout << "Enter employee " << i + 1 << " Name (Max 13 Letters) :";
        cin >> emp.Employee_Name;
        cout << "Enter employee " << i + 1 << " department ID (Max 50 Letters) :";
        cin >> emp.Employee_Dept_ID;
        cout << "Enter employee " << i + 1 << " employee position (Max 50 Letters) :";
        cin >> emp.Employee_postion;
        //employees[i] = emp;

        PrmIndxArray[i].RRN = i;
        strcpy(PrmIndxArray[i].Employee_ID, emp.Employee_ID);

        strcpy(ScndIndxArray[i].Employee_Dept_ID, emp.Employee_Dept_ID);
        strcpy(ScndIndxArray[i].Employee_Name, emp.Employee_Name);
        file.write((char*) &(employees[i]), sizeof(employees[i]));
    }
    sort(PrmIndxArray, PrmIndxArray + numRec);
    sort(ScndIndxArray, ScndIndxArray + numRec);
    WritePrimIndex(PrmIndxArray, numRec, PrimIndex);
    WriteScndIndex(ScndIndxArray, numRec, ScndIndex);

    file.close();
    PrimIndex.close();
    ScndIndex.close();
    return numRec;
}

void SearchById(int numRec) {
    fstream file, PrimIndex;

    file.open("emp.txt", ios::in);
    PrimIndex.open("Primary.txt", ios::in);

    PIndex *PrmIndxArray = new PIndex[numRec];
    employee *employees = new employee[numRec];

    ReadPrimIndex(PrmIndxArray, numRec, PrimIndex);

    //printing index files
    /*
     cout<<"Primary index"<<endl;
     for(int i =0;i<numRec;i++){
     cout<<"RRN : "<<PrmIndxArray[i].RRN<<"  ID:"<<PrmIndxArray[i].ID<<endl;
     }
     */

    char ID[10];
    employee emp;
    int RRN;
    cout << endl << "Enter Target Stundent ID : ";
    cin >> ID;

    RRN = GetRecordRRN(PrmIndxArray, numRec, ID);
    cout << RRN << endl;
    //emp = GetEmployee(RRN, file);
    cout << endl << "emp ID : " << emp.Employee_ID << "  Name: " << emp.Employee_Name
         << "  department id: " << emp.Employee_Dept_ID << "position: "<<emp.Employee_postion << endl;

    file.close();
    PrimIndex.close();
}

void SearchByName(int numRec) {  //// To be updated
    fstream file, PrimIndex, ScndIndex;

    file.open("Students.txt", ios::in);
    PrimIndex.open("Primary.txt", ios::in);
    ScndIndex.open("Secondry.txt", ios::in);

    PIndex *PrmIndxArray = new PIndex[numRec];
    SIndex *ScndIndxArray = new SIndex[numRec];
    employee *employees = new employee[numRec];

    ReadPrimIndex(PrmIndxArray, numRec, PrimIndex);
    ReadScndIndex(ScndIndxArray, numRec, ScndIndex);

    //printing index files
    cout << "Primary index" << endl;
    for (int i = 0; i < numRec; i++) {
        cout << "RRN : " << PrmIndxArray[i].RRN << "  ID:" << PrmIndxArray[i].Employee_ID
             << endl;
    }
    cout << endl << "secondary index" << endl;
    for (int i = 0; i < numRec; i++) {
        cout << "ID : " << ScndIndxArray[i].Employee_Dept_ID << "  Name:"
             << ScndIndxArray[i].Employee_Name << endl;
    }

    char Name[20];
    string ID;
    employee emp;
    int RRN;
    cout << endl << "Enter Target employee Name : ";
    cin >> Name;

    ID = GetEmployeeID(ScndIndxArray, numRec, Name);
    if (ID == "") {
        cout << endl << "employee name not exist" << endl;
        return;
    }
    RRN = GetRecordRRN(PrmIndxArray, numRec, ID);

    //emp = GetEmployee(RRN, file);
    cout << endl << "emp ID : " << emp.Employee_ID << "  Name: " << emp.Employee_Name
         << "  department id: " << emp.Employee_Dept_ID << "position: "<<emp.Employee_postion << endl;

    file.close();
    PrimIndex.close();
    ScndIndex.close();
}
int main() {
    employee e;
    department d;
    e.addemp("12","is","ahmed","student");
    d.adddept("1","is","ahmed");

    return 0;
}
