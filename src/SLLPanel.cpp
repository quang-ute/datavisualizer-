#include "SLL/SLLPanel.h"

SLLPanel::SLLPanel(){
    this->Create.setText("Create",panelButtonFontSize);
    this->Create.setSize(panelButtonSize);
    this->Create.setPosition({Create.getSize().x/2.0f+(Create.getSize().y/2.0f-Create.getfontSize()/2.0f), 650+(Create.getSize().y/2.0f-Create.getfontSize()/2.0f)});
    this->Create.setColor(panelNormal,panelHovered,panelPressed);
    this->Create.setRectangle();

    this->Add.setText("Add",panelButtonFontSize);
    this->Add.setSize(panelButtonSize);
    this->Add.setPosition({Add.getSize().x/2.0f+(Add.getSize().y/2.0f-Add.getfontSize()/2.0f), 700+(Add.getSize().y/2.0f-Add.getfontSize()/2.0f)});
    this->Add.setColor(panelNormal,panelHovered,panelPressed);
    this->Add.setRectangle();

    this->Remove.setText("Remove",panelButtonFontSize);
    this->Remove.setSize(panelButtonSize);
    this->Remove.setPosition({Remove.getSize().x/2.0f+(Remove.getSize().y/2.0f-Remove.getfontSize()/2.0f), 750+(Remove.getSize().y/2.0f-Remove.getfontSize()/2.0f)});
    this->Remove.setColor(panelNormal,panelHovered,panelPressed);
    this->Remove.setRectangle();

    this->Search.setText("Search",panelButtonFontSize);
    this->Search.setSize(panelButtonSize);
    this->Search.setPosition({Search.getSize().x/2.0f+(Search.getSize().y/2.0f-Search.getfontSize()/2.0f), 800+(Search.getSize().y/2.0f-Search.getfontSize()/2.0f)});
    this->Search.setColor(panelNormal,panelHovered,panelPressed);
    this->Search.setRectangle();

    this->Update.setText("Update",panelButtonFontSize);
    this->Update.setSize(panelButtonSize);
    this->Update.setPosition({Update.getSize().x/2.0f+(Update.getSize().y/2.0f-Update.getfontSize()/2.0f), 850+(Update.getSize().y/2.0f-Update.getfontSize()/2.0f)});
    this->Update.setColor(panelNormal,panelHovered,panelPressed);
    this->Update.setRectangle();
}

bool SLLPanel::isAnyButtonPressed(){
    return Create.isPressed()||Add.isPressed()||Remove.isPressed()||Update.isPressed()||Search.isPressed();
}

void SLLPanel::draw(){
    drawController();
    this->Back.drawRectangleRounded(100);
    this->Create.drawRectangleRounded(100);
    this->Create.drawText(panelButtonTextColor);
    this->Add.drawRectangleRounded(100);
    this->Add.drawText(panelButtonTextColor);
    this->Remove.drawRectangleRounded(100);
    this->Remove.drawText(panelButtonTextColor);
    this->Update.drawRectangleRounded(100);
    this->Update.drawText(panelButtonTextColor);
    this->Search.drawRectangleRounded(100);
    this->Search.drawText(panelButtonTextColor);
}

void SLLPanel::update(){
    updateController();
    if(this->Create.isPressed()){
        this->Create.Selected();
        if(isUsing&&isUsing!=&Create) this->isUsing->deSelected();
        this->isUsing = &this->Create;
    }
    else if(this->Add.isPressed()){
        this->Add.Selected();
        if(isUsing&&isUsing!=&Add) this->isUsing->deSelected();
        this->isUsing = &this->Add;
    }
    else if(this->Remove.isPressed()){
        this->Remove.Selected();
        if(isUsing&&isUsing!=&Remove) this->isUsing->deSelected();
        this->isUsing = &this->Remove;
    }
    else if(this->Update.isPressed()){
        this->Update.Selected();
        if(isUsing&&isUsing!=&Update) this->isUsing->deSelected();
        this->isUsing = &this->Update;
    }
    else if(this->Search.isPressed()){
        this->Search.Selected();
        if(isUsing&&isUsing!=&Search) this->isUsing->deSelected();
        this->isUsing = &this->Search;
    }
    if(isBackPressed()){
        if(isUsing) this->isUsing->deSelected();
        isUsing=nullptr;
    }
    this->Back.update();
    this->Create.update();
    this->Add.update(); 
    this->Remove.update();
    this->Update.update();
    this->Search.update();
}

bool SLLPanel::isCreateUsed(){
    return (isUsing == &Create);
}

bool SLLPanel::isAddUsed(){
    return (isUsing == &Add);
}

bool SLLPanel::isRemoveUsed(){
    return (isUsing == &Remove);
}

bool SLLPanel::isSearchUsed(){
    return (isUsing == &Search);
}

bool SLLPanel::isUpdateUsed(){
    return (isUsing==&Update);
}