#ifndef AVLSLLPANEL_H
#define AVLPANEL_H

#include "GUI/Panel.h"

class AVLPanel : public Panel{
    public:
        AVLPanel();
        void draw() override;
        void update() override;
        bool isCreateUsed();
        bool isAddUsed();
        bool isRemoveUsed();
        bool isSearchUsed();
        bool isAnyButtonPressed() override;
    private: 
        Button Create;
        Button Add;
        Button Remove;
        Button Search;
        Button* isUsing=nullptr;
};

#endif