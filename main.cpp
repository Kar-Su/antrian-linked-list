#include<iostream>
#include <stdexcept>
#include<string.h>
#include<ctime>
#include<cstdlib>

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
  void _insert(size_t index, std::string name, int phoneNum, std::string desc);
  void remove();
  void pop();
  void push(std::string name, int phoneNum, std::string desc);
  void front();
  void back();
  void show();
  size_t size();

};

int main(){

  return 0;
}

void Queue::_checkNull(){
  if(head == nullptr){
    std::cerr << "Error: Require data not satisfied, abort program instead." << std::endl;
    exit(EXIT_FAILURE);
  }
}

void Queue::push(std::string name, int phoneNum, std::string desc){
  Node *newNode = new Node();
  time_t currentTimeStamp;

  newNode->name = name;
  newNode->phoneNum = phoneNum;
  newNode->desc = desc;
  newNode->time = time(&currentTimeStamp);


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

void Queue::pop(){
  _checkNull();
  Node *tmp = head -> next;
  delete head;
  head = tmp;
}

void Queue::remove(){}

void Queue::show(){
    _checkNull();
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

void Queue::_insert(size_t index, std::string name, int phoneNum, std::string desc) {
    std::cerr << "Warning: Insert bukan merupakan fungsi murni dari Queue" << std::endl; 
    time_t currentTimeStamp;
    Node* newNode = new Node();

    newNode->name = name;
    newNode->desc = desc;
    newNode->phoneNum = phoneNum;
    newNode->time = time(&currentTimeStamp);

    Node* current = head;

    for (size_t i = 0; i < index && current != nullptr; i++)
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
