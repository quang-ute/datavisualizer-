#ifndef SLLARROW_H
#define SLLARROW_H

#include "GUI/Arrow.h"
class SLLArrow : public Arrow{
    public:
        SLLArrow(Vector2 pos);
        void setLabel(const std::string &text);
        void setNull();
        bool checkNull();
        void setTargetDestination(Vector2 targetDes) override;
        void moveNode(Vector2 targetPos, Vector2 targetDes);
        void draw() override;
    private:
        std::string label;         
        bool isNull=false;  
};

#endif