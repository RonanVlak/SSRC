#pragma once

class Cube
{
private:
    
public:
    Cube(/* args */);
    ~Cube();
    enum CubeFace{
    FRONT,
    BACK,
    LEFT,
    RIGHT,
    UP,
    DOWN
    };
    void printCube();
    void shuffleCube();
    void rotateTopClockwise();
    void rotateTopCounterClockwise();
    void rotateBottomClockwise();
    void rotateBottomCounterClockwise();
    void rotateFrontClockwise();
    void rotateFrontCounterClockwise();
    void rotateBackClockwise();
    void rotateBackCounterClockwise();
    void rotateLeftClockwise();
    void rotateLeftCounterClockwise();
    void rotateRightClockwise();
    void rotateRightCounterClockwise();
    void rotateFaceClockwise(CubeFace);
    void rotateFaceCounterClockwise(CubeFace);
public:
    char cube[6][3][3];

};