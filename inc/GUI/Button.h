#ifndef BUTTON_H
#define BUTTON_H

#include "GUI/Resources.h"

class Button{
    public:
        Button();
        void setTexture(const char* path);
        void setPosition(Vector2 position);
        void setSize(Vector2 size);
        void setText(const char* text, int fontSize);
        void setRectangle();
        void setColor(Color normal, Color hovered, Color pressed);
        void update();
        
        void drawRectangle(Vector2 recSize);
        void drawRectangleRounded(int roundness);
        void drawRectangleRoundedLinesEx(int roundness, int segments, int lineThick, Color color);
        
        void drawTexture(Vector2 position);
        void drawText(Color color);

        Vector2 getSize();
        int getfontSize();
        Vector2 getPosition();

        bool isPressed();
        bool isHovered();
        void Selected();
        void deSelected();
        void setActive();
        void deActive();

    private:
        Rectangle rectangle;
        Color color;
        Color normal;
        Color hovered;
        Color pressed;
        Texture2D texture;
        Vector2 position;
        Vector2 size;
        bool isSelected = false;
        const char* text;
        int fontSize=0;

        bool isActive=true;
};

#endif