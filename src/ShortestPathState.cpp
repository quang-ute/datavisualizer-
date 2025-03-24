#include "ShortestPath/ShortestPathState.h"

ShortestPathState::ShortestPathState() : NodesBox(120,700,STBoxSize.x,STBoxSize.y,STBoxFontSize,STBoxColor,STBoxTextColor), EdgesBox(120,850,STBoxSize.x,STBoxSize.y,STBoxFontSize,STBoxColor,STBoxTextColor), StartNodesBox(120,700,STBoxSize.x,STBoxSize.y,STBoxFontSize,STBoxColor,STBoxTextColor){
    this->Random.setText("Random",STButtonFontSize);
    this->Random.setSize({120, 30});
    this->Random.setPosition({180,760});
    this->Random.setColor(panelNormal,panelHovered,panelPressed);
    this->Random.setRectangle();

    this->LoadFile.setText("Load File",STButtonFontSize);
    this->LoadFile.setSize({120, 30});
    this->LoadFile.setPosition({320,760});
    this->LoadFile.setColor(panelNormal,panelHovered,panelPressed);
    this->LoadFile.setRectangle();

    this->Apply.setText("Apply",STButtonFontSize);
    this->Apply.setSize({260, 30});
    this->Apply.setPosition({250,800});
    this->Apply.setColor(panelNormal,panelHovered,panelPressed);
    this->Apply.setRectangle();

    this->Weighted.setText("Weighted",STButtonFontSize);
    this->Weighted.setSize({120, 30});
    this->Weighted.setPosition({180,700});
    this->Weighted.setColor(panelNormal,panelHovered,panelPressed);
    this->Weighted.setRectangle();

    this->Unweighted.setText("Unweighted",STButtonFontSize);
    this->Unweighted.setSize({120, 30});
    this->Unweighted.setPosition({320,700});
    this->Unweighted.setColor(panelNormal,panelHovered,panelPressed);
    this->Unweighted.setRectangle();

    this->Directed.setText("Directed",STButtonFontSize);
    this->Directed.setSize({120, 30});
    this->Directed.setPosition({180,740});
    this->Directed.setColor(panelNormal,panelHovered,panelPressed);
    this->Directed.setRectangle();

    this->Undirected.setText("UnDirected",STButtonFontSize);
    this->Undirected.setSize({120, 30});
    this->Undirected.setPosition({320,740});
    this->Undirected.setColor(panelNormal,panelHovered,panelPressed);
    this->Undirected.setRectangle();
    
    this->Undirected.Selected();
    this->Unweighted.Selected();
    ST.deDirected();
    ST.deWeighted();

    NodesBox.setNameBox("Number Of Vertices");
    EdgesBox.setNameBox("Number Of Edges");
    StartNodesBox.setNameBox("Start Node");
}

void ShortestPathState::update(){
    ST.update();
    panel.update();
    if(panel.isCreateUsed()){
        Random.setActive();
        LoadFile.setActive();
        Apply.setActive();
        Weighted.deActive();
        Unweighted.deActive();
        Directed.deActive();
        Undirected.deActive();
    }
    else if(panel.isDijkstraUsed()){
        Random.deActive();
        LoadFile.deActive();
        Apply.deActive();
        Weighted.deActive();
        Unweighted.deActive();
        Directed.deActive();
        Undirected.deActive();
    }
    else if(panel.isSettingUsed()){
        Random.deActive();
        LoadFile.deActive();
        Apply.deActive();
        Weighted.setActive();
        Unweighted.setActive();
        Directed.setActive();
        Undirected.setActive();
    }
    if(Random.isPressed()){
        int numNodes=rand()%9+2;
        NodesBox.setText(std::to_string(numNodes));
        EdgesBox.setText(std::to_string(rand()%(numNodes*(numNodes-1))/2+1));
    }
    else if(LoadFile.isPressed()){
        
    }
    else if(Weighted.isPressed()){
        Weighted.Selected();
        Unweighted.deSelected();
        ST.setWeighted();
    }
    else if(Unweighted.isPressed()){
        Unweighted.Selected();
        Weighted.deSelected();
        ST.deWeighted();
    }
    else if(Directed.isPressed()){
        Directed.Selected();
        Undirected.deSelected();
        ST.setDirected();
    }
    else if(Undirected.isPressed()){
        Undirected.Selected();
        Directed.deSelected();
        ST.deDirected();
    }
    else if(IsKeyPressed(KEY_ENTER)||Apply.isPressed()){
        if(panel.isCreateUsed()&&NodesBox.GetText()!=""&&EdgesBox.GetText()!=""){
            ST.createGraph(std::stoi(NodesBox.GetText()),std::stoi(EdgesBox.GetText()));
        }
        else if(panel.isDijkstraUsed()&&StartNodesBox.GetText()!=""){
            ST.Dijkstra(std::stoi(StartNodesBox.GetText()));
        }
        resetBox();
    }
    else if(panel.isBackPressed()){
        ST.clearGraph();
        resetBox();
        Unweighted.Selected();
        Undirected.Selected();
        Weighted.deSelected();
        Directed.deSelected();
        ST.deDirected();
        ST.deWeighted();
    }
    else if(panel.isAnyButtonPressed()){
        resetBox();
    }
    if(panel.isCreateUsed()){
        NodesBox.Update();
        EdgesBox.Update();
        this->Random.update();
        this->LoadFile.update();
        this->Apply.update();
    }
    else if(panel.isDijkstraUsed()){
        StartNodesBox.Update();
    }
    else if(panel.isSettingUsed()){
        this->Weighted.update();
        this->Unweighted.update();
        this->Directed.update();
        this->Undirected.update();
    }
}

void ShortestPathState::draw(){
    ST.draw();
    panel.draw();
    DrawText("Shortest Path",GetScreenWidth()/2.0f-MeasureText("Shortest Path",dataTitleFontSize)/2.0f,40-dataTitleFontSize/2.0f,dataTitleFontSize, dataTitleTextColor);
    STCode.draw();
    if(panel.isCreateUsed()){
        NodesBox.Draw();
        EdgesBox.Draw();
        this->Random.drawRectangleRounded(100);
        this->LoadFile.drawRectangleRounded(100);
        this->Apply.drawRectangleRounded(100);
        this->Random.drawText(panelSubButtonTextColor);
        this->LoadFile.drawText(panelSubButtonTextColor);
        this->Apply.drawText(panelSubButtonTextColor);
    }
    else if(panel.isDijkstraUsed()){
        StartNodesBox.Draw();
    }
    else if(panel.isSettingUsed()){
        Weighted.drawRectangleRounded(100);
        Directed.drawRectangleRounded(100);
        Unweighted.drawRectangleRounded(100);
        Undirected.drawRectangleRounded(100);
        Weighted.drawText(panelSubButtonTextColor);
        Directed.drawText(panelSubButtonTextColor);
        Unweighted.drawText(panelSubButtonTextColor);
        Undirected.drawText(panelSubButtonTextColor);
    }
}

void ShortestPathState::resetBox(){
    NodesBox.resetBox();
    EdgesBox.resetBox();
    StartNodesBox.resetBox();
}

bool ShortestPathState::isBackPressed(){
    return panel.isBackPressed();
}