/*
 * CS106L Assignment 0: Environment Setup!
 * Created by Fabio Ibanez
 *
 * If you're reading this welcome to CS106L! For this assignment you don't 
 * actually need to write any C++ code. Instead, you'll be setting up your
 * environment and getting familiar with the tools we'll be using in the course.
 * The code in this file will verify that your installation is correct and that 
 * the autograder is working properly.
 */

#include <iostream>
#include <sstream>
#include "autograder/utils.cpp"
#include <vector>
#include <algorithm>
#include<cctype>

std::string toUpper(std::string str) {
  std::transform(str.begin(), str.end(), str.begin(),
    [](unsigned char c) { return std::toupper(c); });
  return str;
}

int main() {
  std::vector<std::string> strs;
  std::vector<std::string> strings = {
    "Hello, world!",
    "CS106L is awesome!",
    "I love programming!",
    };
  std::vector<bool> flags = {
    true,
    false,
    true,
    };
  std::transform(strings.begin(), strings.end(), flags.begin(),std::back_inserter(strs),
    [](std::string str, bool flag) {
      return flag ? str : toUpper(str);
    });  
  for(auto & str : strs) {
    std::cout << str << std::endl;
  }
  return 0;
}