#pragma once

class Cube
{
private:
    
public:
    Cube(/* args */);
    ~Cube();

    void printCube();
    void shuffleCube();
public:
    char cube[6][3][3];
};