#include "HashTable/HashTable.h"

HashTable::HashTable(int size) {
    this->size = size;
    table.resize(size);
    
    for (int i = 0; i < size; ++i) {
        table[i] = nullptr;
    }
}

HashTable::~HashTable() {
    for (int i = 0; i < size; ++i) {
        Node* current = table[i];
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
}

Node * HashTable::getTable(int index){
    return table[index];
}

void HashTable::Insert(int key, const std::string& value) {
    int index = key % size;
    Node* newNode = new Node(key);
    Node * current = table[index];
    if (current == nullptr) {
        table[index] = newNode;
    } else {
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }

    newNode->position = {100.0f, 100.0f + static_cast<float>(index) * 50.0f};
    newNode->size = {600, 40};
    newNode->color = LIGHTGRAY;

}

void HashTable::Delete(int key) {
    int index = key % size;
    Node* current = table[index];
    Node* prev = nullptr;
    while (current != nullptr) {
        if (current->data == key) {
            if (prev == nullptr) {
                table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
}

bool HashTable::Find(int key) const {
    int index = key % size;
    Node* current = table[index];
    while (current != nullptr) {
        if (current->data == key) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void HashTable::InitTable(int size) {
    srand(time(0)); // Khởi tạo seed theo thời gian thực để có số ngẫu nhiên khác nhau mỗi lần chạy

    for (int i = 0; i < size; ++i) {
        int randomSizeList = 0 + rand() % (7 - 0 + 1);
        for (int j = 0; j < randomSizeList; ++j) {
            int randomKey = 0 + rand() % (100 - 0 + 1);
            Insert(randomKey, "Value");
        }
    }
}