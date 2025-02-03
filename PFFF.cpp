#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
using namespace std;

#define MAXstu 200
#define MAXdars 10

struct student 
{
    string name;
    string id;
    string field;
    string namedars[MAXdars]; 
    int vadars[MAXdars];     
    int nomdars[MAXdars];       
    float GPA;
    int darscount;    
};

student stu[MAXstu];
int stucount = 0;

void regstu() 
{
    if (stucount >= MAXstu) 
    {
        cout << "Completion capcity!" << endl;
        return;
    }
    cin.ignore();
    cout << "Name: ";
    getline(cin, stu[stucount].name);
    cout << "Field of study: ";
    getline(cin, stu[stucount].field);
    cout << "ID: ";
    getline(cin, stu[stucount].id);
    stu[stucount].GPA = 0.0;
    stu[stucount].darscount = 0;
    cout << "Successful registeration" << endl;
    stucount++;
}

void regdars() 
{
    string studentID;
    cout << "ID: ";
    cin >> studentID;
    for (int i = 0; i < stucount; i++) 
    {
        if (stu[i].id == studentID) 
        {
            int totalCredits = 0;
            for (int j = 0; j < stu[i].darscount; j++) 
            {
                totalCredits += stu[i].vadars[j];
            } 
            if (totalCredits >= 20) 
            {
                cout << "Maximum 20!" << endl;
                return;
            }
            if (stu[i].darscount >= MAXdars) 
            {
                cout << "Completion capcity!" << endl;
                return;
            }
            
            cin.ignore();
            cout << "Course name:";
            getline(cin, stu[i].namedars[stu[i].darscount]);
            cout << "Course count";
            cin >> stu[i].vadars[stu[i].darscount];
            if (totalCredits + stu[i].vadars[stu[i].darscount] > 20) 
            {
                cout << "Oversize course" << endl;
                return;
            }
            cout << "Cours grad";
            cin >> stu[i].nomdars[stu[i].darscount];
            stu[i].darscount++;
            cout << "added" << endl;
            return;
        }
    }
    cout << "Student Not found!" << endl;
}
float GPAcalc(int stuindex) 
{
    int dcount = stu[stuindex].darscount;
    float totalGradePoints = 0.0;
    int totalCredits = 0;
    for (int j = 0; j < dcount; j++) 
    {
        totalGradePoints += stu[stuindex].nomdars[j] * stu[stuindex].vadars[j];
        totalCredits += stu[stuindex].vadars[j];
    }
    if (totalCredits == 0)
        return 0.0;
    return totalGradePoints / totalCredits;
}

void report() 
{
    string studentID;
    cout << "ID";
    cin >> studentID;
    for (int i = 0; i < stucount; i++) 
    {
        if (stu[i].id == studentID) 
        {
            stu[i].GPA = GPAcalc(i);
            cout << "\nRepor card\n";
            cout << "Name: " << stu[i].name << "\n";
            cout << "Field of study: " << stu[i].field << "\n";
            cout << "GPA: " << fixed << setprecision(2) << stu[i].GPA << "\n";
            cout << "course:\n";
            for (int j = 0; j < stu[i].darscount; j++) 
            {
                cout << stu[i].namedars[j] << " | " << stu[i].vadars[j] << " Course count |Course Grad: " << stu[i].nomdars[j] << "\n";
            }
            return;
        }
    }
    cout << "Student Not found!" << endl;
}

void list(string filtermajor = "") 
{
    student liststu[MAXstu];
    for (int i = 0; i < stucount; i++) 
    {
        liststu[i] = stu[i];
        liststu[i].GPA = GPAcalc(i);
    }
    for (int i = 0; i < stucount - 1; i++) 
    {
        for (int j = i + 1; j < stucount; j++) 
        {
            if (liststu[i].GPA < liststu[j].GPA) 
            {
                student temp = liststu[i];
                liststu[i] = liststu[j];
                liststu[j] = temp;
            }
        }
    }
    cout << "\n Student list \n";
    cout << setw(20) << "Name" << setw(15) << "ID " << setw(15) << "Field of study" << setw(10) << "GPA" << "\n";
    cout << "......................................................................\n";
    for (int i = 0; i < stucount; i++) 
    {
        if (filtermajor.length() == 0 || liststu[i].field == filtermajor)
            cout << setw(20) << liststu[i].name << setw(15) << liststu[i].id << setw(15) << liststu[i].field << setw(10) << fixed << setprecision(2) << liststu[i].GPA << "\n";
    }
}
    
int main() 
{
    int choice;
    do 
    {
        cout << "\nmenu\n";
        cout << "1. reg student\n2. reg Course\n3. student list\n4. report card\n5. Exit\n";
        cout << " choice: ";
        cin >> choice;
        switch (choice) 
        {
            case 1:regstu();break;
            case 2:regdars();break;
            case 3: 
            {
                int filterOption;
                cout << "Filter by fiield?\n";
                cout << "1. Yes\n0. No\n";
                cin >> filterOption;
                if (filterOption == 1) 
                {
                    cin.ignore();
                    string major;
                    cout << "Field of study:";
                    getline(cin, major);
                    list(major);
                }else 
                {
                    list();
                }
                break;
            }
            case 4:report();break;
            case 5:cout << "exit\n";break;
            default:cout << "Invalide\n";break;
        }
    }while (choice != 5);
    return 0;
}
