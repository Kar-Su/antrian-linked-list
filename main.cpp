#include<iostream>
#include<string.h>
#include<ctime>
#include<cstdlib>
using namespace std;

// Struct data
struct Node{
  int id;
  std::string name;
  int phoneNum;
  std::string desc;
  std::time_t time;
  Node *next;

  Node(): time(std::time(NULL)), next(nullptr){};
};

// Struct Queue menggunakan linkedlist
struct Queue{
  Node *head;
  Node *tail;

  // Constructor untuk mendefinisikan default head dan tail;
  Queue(): head(nullptr), tail(nullptr){};
  // Destructor untuk handle memory safety
  ~Queue(){
    while(head != nullptr)
    {
      Node *tmp = head;
      head = head->next;
      delete tmp;
    }
    tail = nullptr;
    std::cout << "Success handle memory safety" << std::endl;
  }

  // Mendefinisasikan fungsi dari Queue
  // Note: fungsi yang bukan original dari Queue didefinisasikan dengan tanda "_"
  bool _isNull();
  void _insert(const size_t index, const std::string &name, const int phoneNum, const std::string &desc);
  void _remove(size_t index);
  void pop();
  void push(const std::string &name, const int phoneNum, const std::string &desc);
  // void front();
  // void back();
  void show();
  size_t size();
};

int main(){
  Queue test;
  int pilihan;
  do {
    std::cout << "\n=== MENU QUEUE LINKED LIST ===\n";
    std::cout << "1. Tambah Data (Push)\n";
    std::cout << "2. Hapus Data Pertama (Pop)\n";
    std::cout << "3. Tampilkan Semua Data\n";
    std::cout << "4. Hitung Jumlah Data\n";
    std::cout << "5. Hapus Data pada Index (Remove)\n";
    std::cout << "6. Insert Data pada Index\n";
    std::cout << "0. Keluar\n";
    std::cout << "\n==============================\n";
    std::cout << "Pilih menu: ";
    std::cin >> pilihan;
    std::cin.ignore(); // flush newline

    if (pilihan == 1) {
      std::string nama, desc;
      int telp;
      std::cout << "Nama: "; std::getline(std::cin, nama);
      std::cout << "No Telepon: "; std::cin >> telp; std::cin.ignore();
      std::cout << "Deskripsi: "; std::getline(std::cin, desc);
      test.push(nama, telp, desc);
      std::cout << "Data berhasil ditambahkan!\n";
    } else if (pilihan == 2) {
      test.pop();
      std::cout << "Data pertama dihapus!\n";
    } else if (pilihan == 3) {
      test.show();
    } else if (pilihan == 4) {
      std::cout << "Jumlah data: " << test.size() << std::endl;
    } else if (pilihan == 5) {
      size_t idx;
      std::cout << "Masukkan index yang ingin dihapus (mulai dari 1): ";
      std::cin >> idx; std::cin.ignore();
      test._remove(idx-1);
    } else if (pilihan == 6) {
      size_t idx;
      std::string nama, desc;
      int telp;
      std::cout << "Masukkan index untuk insert (mulai dari 1): ";
      std::cin >> idx; std::cin.ignore();
      std::cout << "Nama: "; std::getline(std::cin, nama);
      std::cout << "No Telepon: "; std::cin >> telp; std::cin.ignore();
      std::cout << "Deskripsi: "; std::getline(std::cin, desc);
      test._insert(idx-1, nama, telp, desc);
    } else if (pilihan == 0) {
      std::cout << "Keluar program.\n";
    } else {
      std::cout << "Pilihan tidak valid!\n";
    }
  } while (pilihan != 0);
  return 0;
}


size_t Queue::size(){
  /* 
    Fungsi yang mengembalikan jumlah elemen dari Queue.
    Dengan cara melakukan pengecekan berulang pada setian node next.
  */

  size_t i = 0;
  Node *current = head;
  while(current != nullptr)
  {
    ++i;
    current = current -> next;
  }
  return i;
}


bool Queue::_isNull(){
  /* 
   Fungsi untuk pengecekan apakah data kosong atau tidak
  */

  if(head == nullptr)
  {
    std::cerr << "Error: Require data not satisfied, abort function instead!" << std::endl;
    return true;
  }
  return false;
}


void Queue::push(const std::string &name, const int phoneNum, const std::string &desc){
  /*
    Fungsi untuk melakukan push data
    */

  Node *newNode = new Node();
  time_t currentTimeStamp;

  newNode->name = name;
  newNode->phoneNum = phoneNum;
  newNode->desc = desc;
  newNode->time = time(&currentTimeStamp);

  // Handle jika pertama kali push(index 0)
  if(head == nullptr){
    head = newNode;
    tail = newNode;
    return;
  }
  
  Node *current = head;
  while(current -> next != nullptr){
    current = current -> next;
  }
  current -> next = newNode;
}


void Queue::pop(){
  /*
    Fungsi untuk melakukan pop data
  */


  if(_isNull())
  {
    return;
  }

  Node *tmp = head;
  // Handle jika yang di pop merupakan data terakhir
  if(tmp == tail)
  {
    tail = nullptr;
  }
  head = head->next;
  delete tmp;
}


void Queue::_remove(const size_t index){
  /*
    Fungsi untuk melakukan remove pada indeks tertentu
    Fungsi ini memiliki behavior dimana dia tidak bisa melakukan fungsionalitas yang sama dengan pop
  */

  std::cerr << "Warning: Remove isn't a original function from Queue" << std::endl;

  if(_isNull())
  {
    return;
  }
  else if(index == 0 || index > size())
  {
    std::cerr << "Error: Unexpected behavior, use pop instead!" << std::endl;
    return;
  }
  
  Node *current = head;

  for(size_t i = 1; i < index && current != nullptr; i++) // i dimulai dari satu karena current dimulai dari head
  {
    current = current->next;
  }
  
  if(current->next == tail)
  {
    tail = current;
  }
  Node *tmp = current->next;
  current->next = tmp->next;
  delete tmp;
}


void Queue::show(){
  /*
    Fungsi untuk menampilkan keseluruhan data
  */

  if(_isNull())
  {
    return;
  }
  Node* current = head;
  size_t i = 1;
  while (current != nullptr)
  {
    std::cout << "Data ke-" << i << std::endl;
    std::cout << "nama: " << current->name << std::endl;
    std::cout << "No Telepon: " << current->phoneNum << std::endl;
    std::cout << "Deskripsi: " << current->desc << std::endl;
    std::cout << "Waktu Antri: " << ctime(&current->time) << std::endl;
    current = current->next;
    ++i;
  }
}


void Queue::_insert(const size_t index, const std::string &name, const int phoneNum, const std::string &desc) {
  /*
    Fungsi untuk memasukkan data pada indeks tertentu
    Fungsi ini memiliki behavior dimana dia tidak bisa melakukan fungsionalitas yang sama dengan push
  */

  std::cerr << "Warning: Insert isn't a original function from Queue" << std::endl;

  if(index >= size() - 1 || head == nullptr)
  {
    std::cerr << "Error: Unexpected Behavior, Use push instead!" << std::endl;
    return;
  }

  time_t currentTimeStamp;
  Node* newNode = new Node();

  newNode->name = name;
  newNode->desc = desc;
  newNode->phoneNum = phoneNum;
  newNode->time = time(&currentTimeStamp);

  Node* current = head;
  
  for(size_t i = 1; i < index && current != nullptr; i++) // i dimulai dari satu karena current dimulai dari head
  {
    current = current->next;
  }

  newNode->next = current->next;
  current->next = newNode;
}
