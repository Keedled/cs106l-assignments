/*
 * CS106L Assignment 3: Make a Class
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 */
#include <iostream>
#include <string>
#include "class.h"
#include <vector>
void sandbox() {
  // STUDENT TODO: Construct an instance of your class!
  std::vector<Person*> people{
      new Student("John", 20, true, 1, 12345, "Computer Science"),
      new Teacher("Jane", 30, false, 2, 54321, "Mathematics")
  };
  for(auto* person : people) {
      std::cout << person->getOccupationID() << std::endl;
      person->SayHello();
  }
}