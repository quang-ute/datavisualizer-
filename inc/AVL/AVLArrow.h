#ifndef AVLARROW_H
#define AVLARROW_H

#include "GUI/Arrow.h"

class AVLArrow : public Arrow{
    public:
        AVLArrow(Vector2 pos);
        void update() override;
        void draw() override;
};

#endif