//Part 2 File I/O and Exception Handling
//Part 3 Operations

#include "course.h"
#include "student.h"

#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>

using namespace std;


//These getters could have been implemented as one function and have the type be changed after it was returned. But to make the function calls clearer and more readable, I have implemented them as separate functions.
string getString(string fileline, int& i) {
    string string = "";
    for(int j=i; j<fileline.length() && fileline[j] == ' '; j++){
        i++;    
    }
    
    for (int j = i; j < fileline.length() && fileline[j] != ','; j++) {
        string = string + fileline[j];
        i++;
    }
    i++;
    return string;
}
int getInt(string fileline, int& i) {
    string intStr = ""; 
    for(int j=i; j<fileline.length() && fileline[j] == ' '; j++){
        i++;    
    }

    for (int j = i; j < fileline.length() && fileline[j] != ','; j++) {
        intStr = intStr + fileline[j];
        i++;
    }
    i++;
    return stoi(intStr);
}
string getIntAsString(string fileline, int i) {
    string intStr = ""; 
    for(int j=i; j<fileline.length() && fileline[j] == ' '; j++){
        i++;    
    }

    for (int j = i; j < fileline.length() && fileline[j] != ','; j++) {
        intStr = intStr + fileline[j];
        i++;
    }
    i++;
    return intStr;
}
float getFloat(string fileline, int& i) {
    string floatStr = "";
    for(int j=i; j<fileline.length() && fileline[j] == ' '; j++){
        i++;    
    }

    for (int j = i; j < fileline.length() && fileline[j] != ','; j++) {
        floatStr = floatStr + fileline[j];
        i++;
    }
    i++;
    return stof(floatStr);
}
string getFloatAsString(string fileline, int i){
    string floatStr = ""; 
    for(int j=i; j<fileline.length() && fileline[j] == ' '; j++){
        i++;    
    }

    for (int j = i; j < fileline.length() && fileline[j] != ','; j++) {
        floatStr = floatStr + fileline[j];
        i++;
    }
    i++;
    return floatStr;
} 

//Used to count the number of files to determine the number of students.
int countLines(string filename) {
    int count = 0;
    string fileline;
    ifstream infile(filename);
    while(getline(infile, fileline)){
        count++;
    }
    infile.close();
return count;
}


//Part 2. of the project, includes all the exception handling, file reading, file writing.
void createStudents(string filename, student* students) {
    string fileline, firstName, lastName, dob;
    int id, studentsIndex;
    studentsIndex = 0;
    try{
    ifstream infile(filename);
    if(!infile){
        throw "Error opening file.";
    }else{
        while(getline(infile, fileline)){
            for (int j = 0; j < fileline.length(); j++) {
                id = getInt(fileline, j);
                firstName = getString(fileline, j);
                lastName = getString(fileline, j);
                dob = getString(fileline, j);       
            }
            students[studentsIndex] = student(id, firstName, lastName, dob);
            studentsIndex++;
        }
    }
    infile.close();
    }catch(...){
        cout << "An error occurred while trying to open the students file." << endl;
        system("pause");
        exit(1);
    }
}
course createCourse(string filename, string regCode, float finalGrade){
    string fileline, courseCode, title;
    int credits;
    
    try{
        ifstream incoursefile(filename);
        if(!incoursefile){
            throw "Error opening file.";
        }else{
            while(getline(incoursefile, fileline)){
                for (int i = 0; i < fileline.length(); i++) {
                    courseCode = getString(fileline, i);
                    title = getString(fileline, i);
                    credits = getInt(fileline, i);                    
                }
                if(courseCode == regCode) {
                    break;
                }
            }
        }
        incoursefile.close();    

    }catch(...){
        cout << "An error occurred while trying to open course file" << endl;
        system("pause");
        exit(1);
    }   
    course Course(courseCode, title, credits);
    Course.setGrade(finalGrade);  
return Course;
}
void registerCourses(string coursefilename, string registrationsfilename, student* students, int numStudents) {
    string coursefileline, registrationsfileline, regCode, courseCode, title;
    int courseIndex, credits, id;
    float finalGrade;
    int studentIndex = 0;

    try{
        ifstream incoursefile(coursefilename);
        if(!incoursefile){
            throw "Error opening file.";
        }else{
            try{
                ifstream inregistrationsfile(registrationsfilename);
                if(!inregistrationsfile){
                    throw "Error opening registrations file.";
                }else{
                    while(getline(inregistrationsfile, registrationsfileline)){
                        for (int i = 0; i < registrationsfileline.length(); i++) {
                            id = getInt(registrationsfileline, i);
                            courseCode = getString(registrationsfileline, i);
                            finalGrade = getFloat(registrationsfileline, i);
                            try{
                                if(finalGrade < 0 || finalGrade > 100) {
                                    throw "Invalid grade. Please check the registration file.";
                                }
                            }catch(const char* exception) {
                                cout << "Invalid final grade " << finalGrade << "/100 for student with ID #" << id << ", And course code " << courseCode << "." << endl;
                                system("pause");
                                exit(1);
                            }   
                        }
                        for(int studentIndex = 0; studentIndex < numStudents; studentIndex++) {
                            if(students[studentIndex].getId() == id) {
                                course Course = createCourse(coursefilename, courseCode, finalGrade);
                                students[studentIndex].enrollCourse(Course);
                                break;
                            }
                        }
                    }
                }
                inregistrationsfile.close();
            }catch(const char* exception) {
                cout << exception << endl;
                system("pause");
                exit(1);
            }   
        }
        incoursefile.close();
    }catch(...){
        cout << "An error occurred while trying to open the course file." << endl;
        system("pause");
        exit(1);
    }

}
void createNewFile(string newFileName, string output){
    try{
        ofstream outfile(newFileName);
        if(!outfile){
            throw "Could not open file.";
        }else{
            outfile << output;
        }
    outfile.close();
    }catch(...){
        cout << "New file could not be opened";
    }

}

//Part 3. Functions that were specified to be implemented in the required project operations
void generateReport(student* students, int numStudents){
    ofstream reportFile("report.txt");
    try{
        if(!reportFile) {
            cout << "Error opening report file." << endl;
            return;
        }else{
            reportFile << "------------Student Report------------" << endl;
            for(int i = 0; i < numStudents; i++) {
                students[i].display();
                reportFile << "Student ID: " << students[i].getId() << endl;
                reportFile << "First Name: " << students[i].getFirstName() << endl;
                reportFile << "Last Name: " << students[i].getLastName() << endl;
                reportFile << "Date of Birth: " << students[i].getDob() << endl;
                reportFile << fixed << setprecision(2);
                reportFile << "Average Grade: " << students[i].average() << "/100" << endl;
                reportFile << endl;
                reportFile << "Enrolled Courses for " << students[i].getFirstName() << " " << students[i].getLastName() << ": " << endl;
                if(students[i].getNumCourses() == 0) {
                    reportFile << "Not enrolled in any courses currently." << endl;
                }else{
                    for(int j = 0; j < students[i].getNumCourses(); j++) {
                        reportFile << "Course " << (j + 1) << ":" << endl;
                        course Course = students[i].getCourse(j);
                        reportFile << "  Course Code: " << Course.getCode() << endl;
                        reportFile << "  Course Title: " << Course.getTitle() << endl;
                        reportFile << "  Credits: " << Course.getCredits() << endl;
                        reportFile << "  Final Grade: " << Course.getFinalGrade() << endl;
                        reportFile << endl;
                    }
                }
            }
            cout << "Report generated successfully." << endl;
        }
        reportFile.close();
    }catch(...) {
        cout << "An error occurred while trying to open the report file." << endl;
        system("pause");
        exit(1);
    }
}
int studentSearch(student* students, int numStudents, int studentID) {
    int foundIndex;
    foundIndex = -1;
        for(int i = 0; i < numStudents; i++) {
            if(students[i].getId() == studentID) {
                foundIndex = i;
                return i;
            }
        }

return foundIndex;
}
void highestAverageStudent(student* students, int numStudents) {
    if(numStudents == 0) {
        cout << "No students available." << endl;
        return;
    }
    int highestIndex = 0;
    float highestAverage = students[0].average();
    for(int i = 1; i < numStudents; i++) {
        float currentAverage = students[i].average();
        if(currentAverage > highestAverage) {
            highestAverage = currentAverage;
            highestIndex = i;
        }
    }
    cout << students[highestIndex].getFirstName() << " " << students[highestIndex].getLastName() << " with ID number #" << students[highestIndex].getId() << " is the student with the highest average grade of " << students[highestIndex].average() << "/100.00." << endl;
} 
void modifyStudentName(student* students, int numStudents, string& studentFileName){
    string idstr, output = "", newStudentFileName = studentFileName, newName, fileline, firstname, lastname, dob;
    int id, studentIndex, studentID;
    try{
        ifstream infile(studentFileName);
        if(!infile){
            throw "Error opening file.";
        }else{
            for(int i=0; i<numStudents; i++){
                cout << students[i].getId() << ", " << students[i].getFirstName() << ", " << students[i].getLastName() << ", " << students[i].getDob() << "." << endl;
            }
            cout << "Enter the ID number of the student whose first name you would like to change: ";
            cin >> studentID;
            studentIndex = studentSearch(students, numStudents, studentID);
            if(studentIndex ==-1){
                cout << "Student does not exist, returning to the menu." << endl;
            }else{
                cout << "Enter the new name: ";
                cin >> newName;
                while(getline(infile, fileline)){
                    for (int j = 0; j < fileline.length(); j++) {
                        idstr = getIntAsString(fileline, j);
                        id = getInt(fileline, j);
                        output = output + idstr + ", ";
                        firstname = getString(fileline, j);
                        if (id == students[studentIndex].getId()){
                            firstname = newName;
                            students[studentIndex].setFirstName(newName);
                        }
                        output = output + firstname + ", ";
                        lastname = getString(fileline, j);
                        output = output + lastname + ", ";
                        dob = getString(fileline, j);
                        output = output + dob + "\n";
                    }
                }
                cout << "Note: Using a different file name will make the program use the new file for any further actions." << endl;
                cout << "Please enter the name of your new file(don't forget to add .txt), Or if you want the current file to be overridden, please enter 0: ";
                cin >> newStudentFileName;
                if(newStudentFileName == "0"){
                    createNewFile(studentFileName, output);
                }else{
                    studentFileName = newStudentFileName;
                    createNewFile(newStudentFileName, output);
                }
            }
            infile.close();
        }
    }catch(...){
        cout << "An error occurred while trying to open the students file." << endl;
        system("pause");
        exit(1);
    }
}
void modifyStudentLastName(student* students, int numStudents, string& studentFileName){
    string idstr, output = "", newStudentFileName = studentFileName, newLastName, fileline, firstname, lastname, dob;
    int id, studentIndex, studentID;
    try{
        ifstream infile(studentFileName);
        if(!infile){
            throw "Error opening file.";
        }else{
            for(int i=0; i<numStudents; i++){
                cout << students[i].getId() << ", " << students[i].getFirstName() << ", " << students[i].getLastName() << ", " << students[i].getDob() << "." << endl;
            }
            cout << "Enter the ID number of the student whose last name you would like to change: ";
            cin >> studentID;
            studentIndex = studentSearch(students, numStudents, studentID);
            if(studentIndex ==-1){
                cout << "Student does not exist, returning to the menu." << endl;
            }else{
             cout << "Enter the new last name: ";
                cin >> newLastName;
                while(getline(infile, fileline)){
                    for (int j = 0; j < fileline.length(); j++) {
                        idstr = getIntAsString(fileline, j);
                        id = getInt(fileline, j);
                        output = output + idstr + ", ";
                        firstname = getString(fileline, j);
                        output = output + firstname + ", ";
                        lastname = getString(fileline, j);
                        if (id == students[studentIndex].getId()){
                            lastname = newLastName;
                            students[studentIndex].setLastName(newLastName);
                        }
                        output = output + lastname + ", ";
                        dob = getString(fileline, j);
                        output = output + dob + "\n";
                    }
                }
                cout << "Note: Using a different file name will make the program use the new file for any further actions." << endl;
                cout << "Please enter the name of your new file(don't forget to add .txt), Or if you want the current file to be overridden, please enter 0: ";
                cin >> newStudentFileName;
                if(newStudentFileName == "0"){
                    createNewFile(studentFileName, output);
                }else{
                    studentFileName = newStudentFileName;
                    createNewFile(newStudentFileName, output);
                }
            }
            infile.close();
        }
    }catch(...){
        cout << "An error occurred while trying to open the students file." << endl;
        system("pause");
        exit(1);
    }
}
void modifyStudentDOB(student* students, int numStudents, string& studentFileName){
    string idstr, output = "", newStudentFileName = studentFileName, newDOB, fileline, firstname, lastname, dob;
    int id, studentIndex, studentID;
    try{
        ifstream infile(studentFileName);
        if(!infile){
            throw "Error opening file.";
        }else{
            for(int i=0; i<numStudents; i++){
                    cout << students[i].getId() << ", " << students[i].getFirstName() << ", " << students[i].getLastName() << ", " << students[i].getDob() << "." << endl;
                }
            cout << "Enter the ID number of the student whose date of birth you would like to change: ";
            cin >> studentID;
            studentIndex = studentSearch(students, numStudents, studentID);
            if(studentIndex ==-1){
                cout << "Student does not exist, returning to the menu." << endl;
            }else{
                
                cout << "Enter the new DOB: ";
                cin.clear();
                cin >> newDOB;
                while(getline(infile, fileline)){
                    for (int j = 0; j < fileline.length(); j++) {
                        idstr = getIntAsString(fileline, j);
                        id = getInt(fileline, j);
                        output = output + idstr + ", ";
                        firstname = getString(fileline, j);
                        output = output + firstname + ", ";
                        lastname = getString(fileline, j);
                        output = output + lastname + ", ";
                        dob = getString(fileline, j);
                        if (id == students[studentIndex].getId()){
                            dob = newDOB;
                            students[studentIndex].setDOB(newDOB);
                        }
                        output = output + dob + "\n";
                    }
                }
                cout << "Note: Using a different file name will make the program use the new file for any further actions." << endl;
                cout << "Please enter the name of your new file(don't forget to add .txt), Or if you want the current file to be overridden, please enter 0: ";
                cin >> newStudentFileName;
                if(newStudentFileName == "0"){
                    createNewFile(studentFileName, output);
                }else{
                    studentFileName = newStudentFileName;
                    createNewFile(newStudentFileName, output);
                }
            }
            infile.close();
        }
    }catch(...){
        cout << "An error occurred while trying to open the students file." << endl;
        system("pause");
        exit(1);
    }
}


int main(){
    string studentFileName;
    string courseFileName;
    string registrationsFileName;

    //User is allowed to input the file name, to demonstrating possible errors which are caught by the implemented exception handeling
    cout << "Please enter the file name of your students file (Make sure to include .txt!) or 0 to use given sample files: ";
    cin >> studentFileName;
    if(studentFileName == "0"){
        studentFileName = "students.txt";
    }
    cout << "Please enter the file name of your courses file (Make sure to include .txt!): ";
    cin >> courseFileName;
    if(courseFileName == "0"){
        courseFileName = "courses.txt";
    }
    cout << "Please enter the file name of your registrations file (Make sure to include .txt!): ";
    cin >> registrationsFileName;
    if(registrationsFileName == "0"){
        registrationsFileName = "registrations.txt";
    }

    //initializes students array using the amount of line in students file as number of students assuming each line is a student with a unique ID
    int numStudents = countLines(studentFileName);
    student* students = new student[numStudents];
    
    //Menu
    bool cont = true;
    while(cont) {
    
        //Part 2 File I/O and exception handling
        createStudents(studentFileName, students);
        registerCourses(courseFileName, registrationsFileName, students, numStudents);
        int foundStudentID;
        int choice;
        cout << "{<---------<--Main Menu-->---------->}" << endl; 
        cout << "1. Generate Report" << endl;
        cout << "2. Display student with highest average grade" << endl;   
        cout << "3. Display Student Information by ID Search." << endl;
        cout << "4. Modify student first name" << endl;
        cout << "5. Modify student last name" << endl;
        cout << "6. Modify student DOB" << endl;
        cout << "7. Exit" << endl;
        // edit values in file too

        cout << "Enter your choice: ";
        cin >> choice;
        switch(choice) {
            case 1: 
                generateReport(students, numStudents);
                cout << endl;
                break;
            
            case 2:
                highestAverageStudent(students, numStudents);
                cout << endl;
                break;
                   
            case 3:
                int searchStudentId;
                for(int i=0; i<numStudents; i++){
                    cout << students[i].getId() << ", " << students[i].getFirstName() << ", " << students[i].getLastName() << ", " << students[i].getDob() << "." << endl;
                }
                cout << "Enter the ID of the student you want to search for: ";
                cin >> searchStudentId;
                foundStudentID = studentSearch(students, numStudents, searchStudentId);
                    if(foundStudentID == -1) {
                        cout << "\nStudent with ID number " << searchStudentId << " was not found." << endl;
                    }else{
                        cout << "\nStudent with ID number " << searchStudentId << " was found. Here are their details below..." << endl;
                        students[foundStudentID].display();
                    }
                cout << endl;  
                break;

            case 4:
                modifyStudentName(students, numStudents, studentFileName);
                cout << endl;
                break;

            case 5:
                modifyStudentLastName(students, numStudents, studentFileName);
                cout << endl;
                break;
            
            case 6: 
                modifyStudentDOB(students, numStudents, studentFileName);
                cout << endl;
                break;

            case 7:
                delete[] students; //free allocated memory for students
                cont = false;
                cout << "Exiting the program." << endl;
                system("pause");
                exit(0);
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                cout << endl;
        }
    }   
            
return 0;
}