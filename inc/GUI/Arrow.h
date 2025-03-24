#ifndef ARROW_H
#define ARROW_H

#include <string>
#include <cmath>

#include "raylib.h"
#include "GUI/Resources.h"
class Arrow{
     public:
          Arrow(Vector2 pos);
          
          virtual void setTargetDestination(Vector2 targetDes);
          void setDestination(Vector2 destination);
          void setPosition(Vector2 position);
          void setTargetPosition(Vector2 targetPos);
          Vector2 getPosition();
          Vector2 getDestination();
          void setColor(Color color);

          virtual void drawArrow(Vector2 position, Vector2 destination);
          virtual void update();
          virtual void draw();
     protected:
          Vector2 position;          
          Vector2 destination;       
          Vector2 targetDestination; 
          Vector2 targetPosition;
          Color color=BLACK;
};

#endif 