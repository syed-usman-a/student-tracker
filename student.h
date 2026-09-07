//Syed Usman Ali 40311926 & Louis Brillu 40304999
//Part 1 Class Design

#ifndef STUDENT_H
#define STUDENT_H

#include "course.h"

#include <string>
#include <iostream>

using namespace std;

class student{
    private:
        int id;
        string firstName, lastName;
        string dob;
        course* studentCourses; // pointer
        int numCourses;

    public:
        student();
        student(int id, string firstName, string lastName, string dob);
        void enrollCourse(const course&);
        float average();
        void display();
        void displayCourses();

        int getId();
        string getFirstName();
        string getLastName();
        string getDob();
        course getCourse(int index);
        int getNumCourses();

        void setFirstName(string newFirstName);
        void setLastName(string newLastName);
        void setDOB(string newDOB);
  
};

#endif // STUDENT_H