#ifndef SLLPANEL_H
#define SLLPANEL_H

#include "GUI/Panel.h"

class SLLPanel : public Panel{
    public:
        SLLPanel();
        void draw() override;
        void update() override;
        bool isCreateUsed();
        bool isAddUsed();
        bool isRemoveUsed();
        bool isSearchUsed();
        bool isUpdateUsed();
        bool isAnyButtonPressed() override;
    private: 
        Button Create;
        Button Add;
        Button Remove;
        Button Update;
        Button Search;
        Button* isUsing=nullptr;
};

#endif

    