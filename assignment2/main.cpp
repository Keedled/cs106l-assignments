/*
 * CS106L Assignment 2: Marriage Pact
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 *
 * Welcome to Assignment 2 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 */
#include <random>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>
#include <cctype>

std::string kYourName = "Mike John"; // Don't forget to change this!

/**
 * Takes in a file name and returns a set containing all of the applicant names as a set.
 *
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 * @returns         A set of all applicant names read from the file.
 *
 * @remark Feel free to change the return type of this function (and the function
 * below it) to use a `std::unordered_set` instead. If you do so, make sure
 * to also change the corresponding functions in `utils.h`.
 */
std::set<std::string> get_applicants(std::string filename) {
     std::ifstream ifs(filename);
     std::set<std::string> Set;
     std::string str;
     while(std::getline(ifs,str))
     {
        Set.insert(str);
     }
     return Set;
}
std::string Helper(std::string str){
    std::string s;
    for(auto c:str){
      if(c<='Z'&&c>='A')
      s.push_back(c);
    }
    return s;
}
/**
 * Takes in a set of student names by reference and returns a queue of names
 * that match the given student name.
 *
 * @param name      The returned queue of names should have the same initials as this name.
 * @param students  The set of student names.
 * @return          A queue containing pointers to each matching name.
 */
std::queue<const std::string*> find_matches(std::string name, std::set<std::string>& students) {
    std::queue<const std::string*> Queue;
    std::string std_ori;
    std_ori = Helper(name);
    for(auto it = students.begin();it!=students.end();it++){
        if(!std_ori.compare(Helper(*it))){//如果首字母相等的话
          Queue.push(&(*it));//压入队列中
        }
    }
    return Queue;
}


/**
 * Takes in a queue of pointers to possible matches and determines the one true match!
 *
 * You can implement this function however you'd like, but try to do something a bit
 * more complicated than a simple `pop()`.
 *
 * @param matches The queue of possible matches.
 * @return        Your magical one true love.
 *                Will return "NO MATCHES FOUND." if `matches` is empty.
 */
std::string get_match(std::queue<const std::string*>& matches) {
    if(matches.empty()){
       return "NO MATCHES FOUND.";
    }
    else{
        std::random_device rd;
        std::mt19937 gen(rd());
        int minn = 0;
        int maxn = matches.size()-1;
        std::uniform_int_distribution<> dis(minn, maxn);
        int randomNum = dis(gen);
        for(int i =0;i<randomNum-1;i++){
            matches.pop();
        }
        return *(matches.front());
    } 
}

/* #### Please don't remove this line! #### */
#include "autograder/utils.hpp"
int main(){
    return run_autograder();
}