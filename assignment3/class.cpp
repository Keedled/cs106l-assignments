#include "class.h"
#include <string>

Person::~Person() {
    std::cout << "Destructor called for " << ID << std::endl;
}
void Person::SetID(int ID) {
    changeID(ID);
}
void Person::changeID(int ID) {
    this->ID = ID;
}

Student::Student(std::string name, int age, bool sex, int ID, int StudentID,std::string major):
    Person(name, age, sex,ID), StudentID(StudentID), major(major){}

std::string Student::getOccupationID(){
    std::string ID_ = "StudentID:"+std::to_string(StudentID)+"\nID:"+std::to_string(getID())+"\n";
    return ID_;
}

void Student::SayHello() {
    std::cout << "Hello, I am a student. My name is " << name << ", my age is " << age << ", and my major is " << major << "." << std::endl;
}

Student::~Student() {
    std::cout << "Destructor called for :" << StudentID << std::endl;
}


Teacher::Teacher(std::string name, int age, bool sex, int ID, int TeacherID,std::string profession):
    Person(name, age, sex,ID), TeacherID(TeacherID), profession(profession){}
std::string Teacher::getOccupationID(){
    std::string ID_ = "TeacherID:"+std::to_string(TeacherID)+"\nID:"+std::to_string(getID())+"\n";
    return ID_;
}
void Teacher::SayHello() {
    std::cout << "Hello, I am a teacher. My name is " << name << ", my age is " << age << ", and my  is " << profession << "." << std::endl;
}
Teacher::~Teacher() {
    std::cout << "Destructor called for :" << TeacherID << std::endl;
}