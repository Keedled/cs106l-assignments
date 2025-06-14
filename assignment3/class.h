#pragma once


#include <string>
#include <iostream>
class Person {
public:
    std::string name;
    int age;
    //true : man else : woman
    bool sex;
    // default constructor
    Person();
    virtual ~Person();
    Person(std::string name, int age, bool sex):name(name), age(age),sex(sex){}
    Person(std::string name, int age, bool sex,int ID):name(name), age(age),sex(sex),ID(ID){}
    int getID() { return ID; }
    virtual std::string getOccupationID() = 0;
    virtual void SayHello() = 0;
    void SetID(int ID) ;
private:
    int ID;
    void changeID(int ID) ;
};

class Student : public Person {
public:
    std::string major;
    Student(std::string name, int age,bool sex, int ID, int StudentID,std::string major);
    std::string getOccupationID() override ;
    void SayHello() override ;
    ~Student() ;
private:
    int StudentID;
};

class Teacher : public Person {
public:
    std::string profession;
    Teacher(std::string name, int age,bool sex, int ID, int teacherID,std::string profession);
    std::string getOccupationID() override;
    void SayHello() override ;
    ~Teacher() ;
private:
    int TeacherID;
};
