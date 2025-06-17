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
  void show(LinkedList* head);
}

int main(){

  return 0;
}

void queue::pushData(){}

void queue::popData(){}

void queue::removeData(){}

void queue::show(LinkedList* head){
    if (head == nullptr) {
        std::cout << "Data kosong" << std::endl;
        return;
    }

    LinkedList* current = head;
    while (current != nullptr)
    {
        std::cout << "nama: " << current->name << std::endl;
        std::cout << "No Telepon: " << current->phoneNum << std::endl;
        std::cout << "Deskripsi: " << current->desc << std::endl;
        std::cout << "Waktu Antri: " << ctime(&current->time) << std::endl;
        current = current->next;
    }
}

void initAntrian(){}
