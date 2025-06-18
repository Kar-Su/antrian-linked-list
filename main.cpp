#include<iostream>
#include <stdexcept>
#include<string.h>
#include<ctime>

struct Node{
  int id;
  std::string name;
  int phoneNum;
  std::string desc;
  std::time_t time;
  Node *next;

  Node(): next(nullptr), time(std::time(NULL)){};
};

struct Queue{
  Node *head;
  Node *tail;

  Queue(): head(nullptr), tail(nullptr){};
  ~Queue(){
    Node *current = head;
    Node *nextNode = nullptr;

    while(head != nullptr){
      nextNode = current -> next;
      delete current;
      current = nextNode;
    }
    head = nullptr;
    tail = nullptr;
  }

  void _checkNull();
  void insertData(int key, std::string name, int phoneNum, std::string desc);
  void removeData();
  void popData();
  void pushData(std::string name, int phoneNum, std::string desc);
  void front();
  void back();
  void show();

};

int main(){

  return 0;
}

void Queue::_checkNull(){
  if(head == nullptr){
    throw std::logic_error("Error: Data Kosong");
  }
}

void Queue::pushData(std::string name, int phoneNum, std::string desc){
  Node *newNode = new Node();
  if(head == nullptr){
    head = newNode;
    return;
  }
  
  Node *tmp = head;
  while(tmp -> next != nullptr){
    tmp = tmp -> next;
  }
  tmp -> next = newNode;
}

void Queue::popData(){}

void Queue::removeData(){}

void Queue::show(){
    Node* current = head;
    while (current != nullptr)
    {
        std::cout << "nama: " << current->name << std::endl;
        std::cout << "No Telepon: " << current->phoneNum << std::endl;
        std::cout << "Deskripsi: " << current->desc << std::endl;
        std::cout << "Waktu Antri: " << ctime(&current->time) << std::endl;
        current = current->next;
    }
}

void Queue::insertData(int position, std::string name, int phoneNum, std::string desc) {
    time_t currentTimeStamp;
    Node* newNode = new Node();

    newNode->name = name;
    newNode->desc = desc;
    newNode->phoneNum = phoneNum;
    newNode->time = time(&currentTimeStamp);

    Node* current = head;

    for (int i = 1; i < position - 1 && current != nullptr; i++)
    {
      current = current->next;
    }

    if (current == nullptr) {
      delete newNode;
    }

    newNode->next = current->next;
    current->next = newNode;
}

void initAntrian(){}
