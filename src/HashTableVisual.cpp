#include "HashTable/HashTableVisual.h"
#include "raymath.h"
#include <iostream>
#include <algorithm>

HashTableVisualization::HashTableVisualization()
    : hashTable(MAX_TABLE_SIZE), 
      isInserting(false), isDeleting(false), isFinding(false), isInitializing(false), 
      inputBox(10, HASH_TABLE_HEIGHT - 50, INPUT_BOX_WIDTH, INPUT_BOX_HEIGHT, 32, GRAY, BLACK) {
    
    selectedKey = -1;
    inputBox.isAppear = false;

    // Thiết lập vị trí, kích thước, màu sắc cho các nút
    insertButton.setPosition({50, 700});
    insertButton.setSize({150, 50});
    insertButton.setText("Insert", 20);
    insertButton.setColor(DARKGRAY, GRAY, BLACK);

    deleteButton.setPosition({220, 700});
    deleteButton.setSize({150, 50});
    deleteButton.setText("Delete", 20);
    deleteButton.setColor(DARKGRAY, GRAY, BLACK);

    findButton.setPosition({390, 700});
    findButton.setSize({150, 50});
    findButton.setText("Find", 20);
    findButton.setColor(DARKGRAY, GRAY, BLACK);

    initButton.setPosition({560, 700});
    initButton.setSize({150, 50});
    initButton.setText("Init", 20);
    initButton.setColor(DARKGRAY, GRAY, BLACK);
}

HashTableVisualization::~HashTableVisualization() {
    // clear all nodes
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        Node* current = hashTable.getTable(i);
        while (current != nullptr) {
            std::cout << "Deleting node with value: " << current->data << std::endl;
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
    std::cout << "All nodes deleted successfully." << std::endl;
    
}

void HashTableVisualization::Init(int size) {
    //std::cout << "Initializing hash table..." << std::endl;
    // hashTable = HashTable(size);
    // MAX_TABLE_SIZE = size;
    // if(size >= 15){
    //     MAX_TABLE_SIZE = 15;
    //     hashTable = HashTable(15);
    // }
    // else{
    //     MAX_TABLE_SIZE = size;
    //     hashTable = HashTable(size);
    // }
    isInitializing = false;
    inputBox.isAppear = false;
}

void HashTableVisualization::Insert(int key) {
    std::cout << "Inserting key: " << key << std::endl;
    hashTable.Insert(key, "Value");
    isInserting = false;
    inputBox.isAppear = false;
}

void HashTableVisualization::Delete(int key) {
    std::cout << "Deleting key: " << key << std::endl;
    hashTable.Delete(key);
    isDeleting = false;
    inputBox.isAppear = false;
}

bool HashTableVisualization::Find(int key) {
    std::cout << "Finding key: " << key << std::endl;
    bool found = hashTable.Find(key);
    isFinding = false;
    inputBox.isAppear = false;
    return found;
}

void HashTableVisualization::HandleInput() {
    if(inputBox.isAppear) {
        inputBox.Update();
    }
    if (IsKeyPressed(KEY_ENTER) && inputBox.isAppear) {
        std::string text = inputBox.GetText();
        inputBox.clearText();
        if (!text.empty() && std::all_of(text.begin(), text.end(), ::isdigit)) {
            int key = std::stoi(text);
            if (isInserting) {
                Insert(key);
            } else if (isDeleting) {
                Delete(key);
            } else if (isFinding) {
                bool found = Find(key);
                std::cout << "Find result: " << (found ? "Found" : "Not Found") << std::endl;
            } else if (isInitializing) {
                Init(key);
            }
        }
        inputBox.isAppear = false;
    }
}

void HashTableVisualization::HandleMouseInput() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePoint = GetMousePosition();
        if (insertButton.isPressed()) {
            isInserting = true;
            inputBox.isAppear = true;
        } else if (deleteButton.isPressed()) {
            isDeleting = true;
            inputBox.isAppear = true;
        } else if (findButton.isPressed()) {
            isFinding = true;
            inputBox.isAppear = true;
        } else if (initButton.isPressed()) {
            isInitializing = true;
            inputBox.isAppear = true;
        }
    }
}

void HashTableVisualization::DrawHashTable() {
    int bucketSpacing = 50; // Khoảng cách giữa các bucket
    int nodeSpacing = 50;   // Khoảng cách giữa các node trong danh sách liên kết
    int startX = 20;        // Vị trí bắt đầu vẽ
    int startY = 50;        // Vị trí cho các bucket

    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        // Vẽ vị trí bucket (ô tròn nhỏ)
        Vector2 bucketPos = {(float)(startX + i * bucketSpacing), (float)startY};
        DrawCircle(bucketPos.x, bucketPos.y, 10, BLACK);
        DrawText(TextFormat("%d", i), bucketPos.x - 5, bucketPos.y + 15, 15, RED); // Số bucket màu đỏ
        
        // Vẽ danh sách liên kết (nếu có)
        Node * preNode;
        Node* current = hashTable.getTable(i);
        Vector2 prevPos = bucketPos; // Vị trí node trước đó để vẽ đường nối

        while (current != nullptr) {
            Vector2 nodePos = {prevPos.x, prevPos.y + nodeSpacing}; // Xuống dần theo chiều dọc
            DrawNode(current);
            current->position = nodePos; // Cập nhật vị trí node
            
            DrawLine({prevPos.x, prevPos.y}, {nodePos.x, nodePos.y}); // Nối đường thẳng
            DrawArrow({prevPos.x, prevPos.y}, {nodePos.x, nodePos.y}); // Nối mũi tên
            prevPos = nodePos; // Cập nhật node trước đó
            current = current->next;
        }
    }
}

void HashTableVisualization::DrawNode(Node *node) {
    float radius = 15; // Bán kính của node (hình tròn)
    
    // Vẽ hình tròn cho node
    DrawCircle(node->position.x, node->position.y, radius, BLACK);
    
    // Vẽ viền trắng nếu cần
    DrawCircleLines(node->position.x, node->position.y, radius, WHITE);

    // Vẽ dữ liệu của node (màu trắng, căn giữa)
    std::string text = std::to_string(node->data);
    int textWidth = MeasureText(text.c_str(), 15); // Lấy độ rộng chữ
    DrawText(text.c_str(), node->position.x - textWidth / 2, node->position.y - 7, 15, WHITE);
}
void HashTableVisualization::DrawLine(Vector2 start, Vector2 end) {
    DrawLineEx(start, end, 2, BLACK);
}

void HashTableVisualization::DrawArrow(Vector2 start, Vector2 end) {
    Vector2 dir = Vector2Normalize(Vector2Subtract(end, start));
    Vector2 left = Vector2Add(end, Vector2Rotate(dir, 225.0f));
    Vector2 right = Vector2Add(end, Vector2Rotate(dir, 135.0f));
    DrawLineEx(end, left, 2, BLACK);
    DrawLineEx(end, right, 2, BLACK);
}

void HashTableVisualization::Draw() {


    DrawHashTable();

    insertButton.drawRectangle({BUTTON_WIDTH, BUTTON_HEIGHT});
    deleteButton.drawRectangle({BUTTON_WIDTH, BUTTON_HEIGHT});
    findButton.drawRectangle({BUTTON_WIDTH, BUTTON_HEIGHT});
    initButton.drawRectangle({BUTTON_WIDTH, BUTTON_HEIGHT});

    if (inputBox.isAppear) {
        inputBox.Draw();
    }
}