#include "GUI/CodeBlock.h"

CodeBlock::CodeBlock() : highlightColor(highlightColor){}

void CodeBlock::update(){

}

void CodeBlock::draw(){
    drawHighlight(16);
    drawCode(1215,700,16,BLACK);
}

void CodeBlock::setCode(std::string code){
    this->code=code;
}

void CodeBlock::clearCode(){
    this->code="";
}

void CodeBlock::drawCode( int x, int y, int fontSize, Color color){
    std::stringstream stream(code);
    std::string line;
    int lineDis=fontSize+5;
    int pos=0;
    while(std::getline(stream,line)){
        DrawText(line.c_str(),x,y+pos,fontSize,color);
        pos+=lineDis;
    }
}

void CodeBlock::setHighlight(std::vector<int> ID){
    highlightID=ID;
}

void CodeBlock::drawHighlight(int fontSize){
    for (int x : highlightID){
        DrawRectangle(1200,700+x*(fontSize+5),400,fontSize+2.5f,YELLOW);
    }
}

void CodeBlock::clearHighlight(){
    highlightID.clear();
}
