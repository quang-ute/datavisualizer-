#ifndef STPANEL_H
#define STPANEL_H

#include "GUI/Panel.h"

class STPanel : public Panel{
    public:
        STPanel();
        void draw() override;
        void update() override;
        bool isCreateUsed();
        bool isDijkstraUsed();
        bool isSettingUsed();
        bool isAnyButtonPressed() override;
    private: 
        Button Create;
        Button Dijkstra;
        Button Setting;
        Button* isUsing=nullptr;
};

#endif