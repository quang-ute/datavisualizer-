#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include "raylib.h"
#include "GUI/Button.h"
#include "GUI/inputBox.h"
#include "Node.h"
#include "HashTable.h"


class HashTable{
public:
    HashTable(int size);
    ~HashTable();

    void Insert(int key, const std::string& value);
    void Delete(int key);
    bool Find(int key) const;
    void InitTable(int size);
    Node * getTable(int index);
    //void Draw();

private:
    std::vector<Node*> table;
    int size;
};