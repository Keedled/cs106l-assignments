/*
 * CS106L Assignment 5: TreeBook
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 */

#include <iostream>
#include <string>

class User
{
public:
  User(const std::string& name);
  void add_friend(const std::string& name);
  std::string get_name() const;
  size_t size() const;
  void set_friend(size_t index, const std::string& name);

  /** 
   * STUDENT TODO:
   * Your custom operators and special member functions will go here!
   */
  friend std::ostream& operator<<(std::ostream& os, const User& user);

  ~User();//析构函数
  User(const User& user);//拷贝构造函数，Student student2 = student1; // 调用拷贝构造函数
  User& operator=(const User& user);//拷贝赋值运算符 调用拷贝赋值运算符 student2 = sstudent1;
  User(User&& user)=delete;
  User& operator=(User&& user)=delete;

  User& operator+=(User& rhs);
  bool operator<(const User& rhs) const;

private:
  std::string _name;
  std::string* _friends;
  size_t _size;
  size_t _capacity;
};