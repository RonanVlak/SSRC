#pragma once
#include <iostream>
#include <string>

class cubie
{
private:
    std::string colours = "XXX";
public:
    cubie();
    cubie(std::string _colours);
    ~cubie();
    void setColours(std::string _colours);
    std::string getColours();
};

cubie::cubie(){
    colours = "XXX"; // initialize with no value
}

cubie::cubie(std::string _colours)
{
    colours = _colours;
}

cubie::~cubie()
{
}

/*
Colour Definition:
W = White
B = Blue
R = Red
G = Green
Y = Yellow
O = Orange
X = Undefined
Example:
WBX
WBR
*/
void cubie::setColours(std::string _colours){
    colours = _colours;
}

std::string cubie::getColours(){
    return colours;
}