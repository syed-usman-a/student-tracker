//Part 1 Class Design
#ifndef COURSE_H
#define COURSE_H

#include <string>

using namespace std;

//Part 1 Class Design
class course {
private:
    string code, title;
    int credits;
    float finalGrade;

public:
    course();
    course(string fcode, string ftitle, int fcredits);
    void setGrade(float g);
    void display();

    string getCode();
    string getTitle();
    int getCredits();
    float getFinalGrade();
};

#endif // COURSE_H
