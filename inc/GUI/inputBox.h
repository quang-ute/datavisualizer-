// InputBox.h
#ifndef INPUTBOX_H
#define INPUTBOX_H

#include <string>

#include "raylib.h"
#include "GUI/Resources.h"

class InputBox {
private:
    Rectangle box;
    std::string text;
    std::string nameBox;
    int maxLength;
    bool isActive;

    Color boxColor;
    Color textColor;
    float blinkTimer;
    bool showCursor;
    bool isMouseonBox;

public:
    InputBox(float x, float y, float width, float height, int maxLen, Color boxCol, Color txtCol);
    void Update();
    void Draw();
    std::string GetText() const;
    void resetBox();
    void setText(std::string text);
    void setNameBox(std::string nameBox);
    bool isAppear;
    void setPosition(Vector2 position);
    void clearText(){
        text="";
    };
};

#endif