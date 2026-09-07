//Part 1 Class Design


#include "course.h"

#include <iostream>
#include <fstream>

using namespace std;

course::course(){ // default constructor
    code = "Default";
    title = "Default";
    credits = 0;
    finalGrade = 0;

}

course::course(string code, string title, int credits) { // parameterized constructor
    this->code = code;
    this->title = title;
    this->credits = credits;
    finalGrade = 0;
    
}

void course::setGrade(float g){ // sets vaidated final grade, but still checks just in case
    if(g >= 0 && g <= 100){
        finalGrade = g;
    }else{
        cout << "Invalid grade. Please enter a value between 0 and 100." << endl;
    }                   


}

void course::display(){
    cout << "Course Code: " << code;
    cout << ", Course Title: " << title << endl;
    cout << "Credits: " << credits;
    cout << ", Final Grade: " << finalGrade << endl;
    cout << endl;       
}

string course::getCode() {
    return code;
}

string course::getTitle() {
    return title;
}  

int course::getCredits() {
    return credits;
}

float course::getFinalGrade() {
    return finalGrade;
}
