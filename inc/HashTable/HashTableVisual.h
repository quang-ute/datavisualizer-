#ifndef HASHTABLEVISUALIZATION_H
#define HASHTABLEVISUALIZATION_H

#include "raylib.h"
#include "GUI/Button.h"
#include "GUI/inputBox.h"
#include "HashTable.h"
#include <vector>
#include <string>

#define MAX_TABLE_SIZE 10
#define HASH_TABLE_WIDTH 800
#define HASH_TABLE_HEIGHT 600
#define BUTTON_WIDTH 100
#define BUTTON_HEIGHT 40
#define INPUT_BOX_WIDTH 200
#define INPUT_BOX_HEIGHT 30



class HashTableVisualization {
    public:
        HashTableVisualization();
        ~HashTableVisualization();
    
        void Init(int size);
        void Insert(int key);
        void Delete(int key);
        bool Find(int key);
        void Draw();
        void HandleInput();
        void HandleMouseInput();
    
    private:
        HashTable hashTable;
        Button insertButton;
        Button deleteButton;
        Button findButton;
        Button initButton;
        InputBox inputBox;
        int selectedKey;
        bool isInserting;
        bool isDeleting;
        bool isFinding;
        bool isInitializing;
        
    
        void DrawHashTable();
        void DrawNode(Node * node);
        void DrawLine(Vector2 start, Vector2 end);  
        void DrawArrow(Vector2 start, Vector2 end);
       
        // void HandleInsert();
        // void HandleDelete();
        // void HandleFind();
        // void HandleInit();
        // void drawLine(Node* node1, Node* node2);
        // void drawArrow(Vector2 start, Vector2 end);
        // void drawNode(Node* node);
    };
    

#endif // HASHTABLEVISUALIZATION_H