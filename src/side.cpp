#pragma once
#include <iostream>
#include <string>
#include "cubie.cpp"

class side
{
private:
    cubie cubies[8];
    std::string orientation = "";
public:
    side();
    side(cubie cubies[8], std::string _orientation);
    ~side();

    void setSide(cubie cubies[8]);
    cubie getCubie(int nr);

    void setOrientation(std::string _orientation);
    std::string getOrientation();
};

side::side(){
    for(int i = 0; i < 9; i++){
        cubies[i].setColours("XXX");
    }
    orientation = "";
}

side::side(cubie _cubies[5], std::string _orientation){
    for(int i = 0; i < 9; i++){
        cubies[i].setColours(_cubies[i].getColours());
    }
    orientation = _orientation;
}

side::~side()
{
}

cubie side::getCubie(int nr){
    return cubies[nr];
}

void side:: setOrientation(std::string _orientation){
    orientation = _orientation;
}
std::string side::getOrientation(){
    return orientation;
}