//Syed Usman Ali 40311926 & Louis Brillu 40304999
//Part 1 Class Design

#include "student.h"

#include <iomanip>

using namespace std;

student::student(){ // default constructor
    id = 0;
    firstName = "Default";
    lastName = "Default";
    dob = "00/00/0000";
    studentCourses = nullptr;
    numCourses = 0;
}

student::student(int id, string firstName, string lastName, string dob) { // parameterized constructor
    this->id = id;
    this->firstName = firstName;
    this->lastName = lastName;
    this->dob = dob;
    studentCourses = nullptr;
    numCourses = 0;
}

void student::enrollCourse(const course& currentCourse){
    course* newCourses = new course[numCourses + 1];
    for(int i = 0; i < numCourses; i++){
        newCourses[i] = studentCourses[i];
    }   
    newCourses[numCourses] = currentCourse;
    delete[] studentCourses;
    studentCourses = newCourses;
    numCourses++;
}

float student::average(){
    if(numCourses == 0) return 0.0;
    float sum = 0.0;
    for(int i = 0; i < numCourses; i++){
        sum += studentCourses[i].getFinalGrade();
    }
    return sum / numCourses;
} 

void student::display(){
    cout << "Student ID: " << id << endl;
    cout << "First Name: " << firstName << endl;
    cout << "Last Name: " << lastName << endl;
    cout << "Date of Birth: " << dob << endl;
    cout << fixed << setprecision(2);
    cout << "Average Grade: " << average() << "/100" << endl;
    cout << endl;
    cout << "Enrolled Courses for " << firstName << " " << lastName << ":" << endl;   

    for(int i = 0; i < numCourses; i++){
        cout << "Course " << (i + 1) << ":" << endl;
        studentCourses[i].display();
    }
    
}      

void student::displayCourses(){
    for(int i = 0; i < numCourses; i++){
        cout << "Course " << (i + 1) << ":" << endl;
        studentCourses[i].display();
    }

}

int student::getId(){
    return id;
}

string student::getFirstName(){
    return firstName;
}

string student::getLastName(){
    return lastName;
}   

string student::getDob(){
    return dob;
}   

course student::getCourse(int index){
    if(index >= 0 && index < numCourses){
        return studentCourses[index];
    }else{
        cout << "Invalid index." << endl;
        return course();
    }
}

int student::getNumCourses(){
    return numCourses;
}

void student::setFirstName(string newFirstName){
    firstName = newFirstName;
}

void student::setLastName(string newLastName){
    lastName = newLastName;
}

void student::setDOB(string newDOB){
    dob = newDOB;
}
