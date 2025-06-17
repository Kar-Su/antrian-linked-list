#include<iostream>
#include<string.h>
#include<ctime>

struct LinkedList{
  int id;
  std::string name;
  int phoneNum;
  std::string desc;
  LinkedList *next;
  std::time_t time;

  LinkedList(): next(nullptr), time(std::time(NULL)){};
};

namespace queue{
  LinkedList *head = nullptr;
  void insertData();
  void removeData();
  void popData();
  void pushData();
  void front();
  void back();
  void show();
}

int main(){

  return 0;
}

void queue::pushData(){}

void queue::removeData(){}

void queue::popData(){}

void queue::show(){}
