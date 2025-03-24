#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "raylib.h"

class Node{
    public:
        int data;
        Node * next;
        Vector2 position;
        Vector2 size;
        Color color;
        Node(int data, Vector2 position, Vector2 size, Color color) {
            this->data = data;
            this->position = position;
            this->size = size;
            this->color = color;
            this->next = NULL;
        }
        Node(int data){
            this->data = data;
            this->next = NULL;
        }
};