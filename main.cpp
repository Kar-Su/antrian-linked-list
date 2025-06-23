#include <iostream>
#include <string>
#include <ctime>
#include <map>
#include "custom.hpp"


enum Status { PENDING, PROSES, SELESAI };
std::map<Status, std::string> statusMap{
{PENDING, "Pending"},
{PROSES, "Proses"},
{SELESAI, "Selesai"},
};


// Struct data
struct Node{

    int id;
    std::string name;
    int phoneNum;
    std::string desc;
    std::time_t time;
    Status status;
    Node *next;

    Node(): time(std::time(NULL)), status(PENDING), next(nullptr){};
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
    void updateStatus(size_t index, Status newStatus);
    void showBasedOnStatus(Status status);
    void showmMenu();
    size_t size();
};

int main(){
    Queue test;
    char pilihan;
    do
    {
        test.showmMenu();
        std::cin >> pilihan;
        std::cin.ignore();
        switch (pilihan)
        {
        case '1':
            {
            clearScreen();
            std::string nama, desc;
            int telp;
            std::cout << "Nama: "; std::getline(std::cin, nama);
            std::cout << "No Telepon: "; std::cin >> telp; std::cin.ignore();
            std::cout << "Deskripsi: "; std::getline(std::cin, desc);
            test.push(nama, telp, desc);
            std::cout << "Data berhasil ditambahkan!\n";
            getch();
            }
            break;
        case '2':
            {
            clearScreen();
            test.pop();
            std::cout << "Data pertama dihapus!\n";
            getch();
            }
            break;
        case '3':
            {
            clearScreen();
            test.show();
            getch();
            }
            break;
        case '4':
            {
            clearScreen();
            std::cout << "Jumlah data: " << test.size() << std::endl;
            getch();
            }
            break;
        case '5':
            {
            clearScreen();
            size_t idx;
            std::cout << "Masukkan index yang ingin dihapus (mulai dari 1): ";
            std::cin >> idx; std::cin.ignore();
            test._remove(idx);
            getch();
            }
            break;
        case '6':
            {
            clearScreen();
            size_t idx;
            std::string nama, desc;
            int telp;
            std::cout << "Masukkan index untuk insert (mulai dari 1): ";
            std::cin >> idx; std::cin.ignore();
            std::cout << "Nama: "; std::getline(std::cin, nama);
            std::cout << "No Telepon: "; std::cin >> telp; std::cin.ignore();
            std::cout << "Deskripsi: "; std::getline(std::cin, desc);
            test._insert(idx, nama, telp, desc);
            getch();
            }
            break;
        case '7':
            {
            clearScreen();
            size_t idx;
            int pilihanStatus;
            std::cout << "Masukkan index data yang ingin diupdate statusnya (mulai dari 1): ";
            std::cin >> idx; std::cin.ignore();
            std::cout << "Pilih status baru:\n";
            std::cout << "1. Pending\n";
            std::cout << "2. Proses\n";
            std::cout << "3. Selesai\n";
            std::cout << "Pilihan: ";
            std::cin >> pilihanStatus; std::cin.ignore();
            Status newStatus;
            switch (pilihanStatus) {
                case 1: newStatus = PENDING; break;
                case 2: newStatus = PROSES; break;
                case 3: newStatus = SELESAI; break;
                default: 
                std::cout << "Pilihan tidak valid!\n";
                continue;
            }
            test.updateStatus(idx-1, newStatus);
            std::cout << "Status berhasil diupdate!\n";
            getch();
            }
            break;
        case '8':
            {
            clearScreen();
            int pilihanStatus;
            std::cout << "Pilih status untuk menampilkan data:\n";
            std::cout << "1. Pending\n";
            std::cout << "2. Proses\n";
            std::cout << "3. Selesai\n";
            std::cout << "Pilihan: ";
            std::cin >> pilihanStatus; std::cin.ignore();
            Status status;
            switch (pilihanStatus) {
                case 1: status = PENDING; break;
                case 2: status = PROSES; break;
                case 3: status = SELESAI; break;
                default: 
                std::cout << "Pilihan tidak valid!\n";
                continue;
            }
            test.showBasedOnStatus(status);
            getch();
            }
            break;
        case '0':
            clearScreen();
            std::cout << "Keluar program.\n";
            break;
        
        default:
            clearScreen();
            std::cout<<"Pilihan Tidak Tersedia";
            getch();
            break;
        }
    } while (pilihan != '0');

    return 0;
}


size_t Queue::size(){
    /* Fungsi yang mengembalikan jumlah elemen dari Queue.
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
    /* Fungsi untuk pengecekan apakah data kosong atau tidak
    */

    if(head == nullptr)
    {
        std::cerr << "Error: Require data not satisfied, abort function instead!" << std::endl;
        getch();
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
    getch();

    if(_isNull())
    {
        return;
    }
    else if(index == 0 || index >= size())
    {
        std::cerr << "Error: Unexpected behavior, use pop instead!" << std::endl;
        getch();
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
        std::cout << "Status antri: " << statusMap[current->status] << std::endl;
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
    getch();

    if(index >= size() || head == nullptr)
    {
        std::cerr << "Error: Unexpected Behavior, Use push instead!" << std::endl;
        getch();
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

void Queue::updateStatus(size_t index, Status newStatus) {
    if (_isNull()) 
    {
        std::cerr << "Data Kosong" << std::endl;
        getch();
        return;
    }

    Node* current = head;
    while (current != nullptr)
    {
        if (current != nullptr && index == 0) {
            current->status = newStatus;
            return;
        }
        current = current->next;
    }
}

void Queue::showBasedOnStatus(Status status) {
    if (_isNull()) 
    {
        std::cerr << "Data Kosong" << std::endl;
        getch();
        return;
    }

    Node* current = head;
    size_t i = 1;


    while (current != nullptr) {
        if (current->status == status) {
            std::cout << "Data ke-" << i << std::endl;
            std::cout << "Nama: " << current->name << std::endl;
            std::cout << "No Telepon: " << current->phoneNum << std::endl;
            std::cout << "Deskripsi: " << current->desc << std::endl;
            std::cout << "Status Antri: " << statusMap[current->status] << std::endl;
            std::cout << "Waktu Antri: " << ctime(&current->time) << std::endl;
        }
        current = current->next;
        ++i;
    }
}

void Queue::showmMenu() {
    clearScreen();
    std::cout << "\n=== MENU QUEUE LINKED LIST ===\n";
    std::cout << "1. Tambah Data (Push)\n";
    std::cout << "2. Hapus Data Pertama (Pop)\n";
    std::cout << "3. Tampilkan Semua Data\n";
    std::cout << "4. Hitung Jumlah Data\n";
    std::cout << "5. Hapus Data pada Index (Remove)\n";
    std::cout << "6. Insert Data pada Index\n";
    std::cout << "7. Update Status data pada Index\n";
    std::cout << "8. Tampilkan data berdasarkan status yang dipilih\n";
    std::cout << "0. Keluar\n";
    std::cout << "\n==============================\n";
    std::cout << "Pilih menu: ";
}
