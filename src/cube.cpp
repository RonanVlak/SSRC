#pragma once
#include <string>
//#include "side.cpp"
#include "motor.cpp"
//#include "cubie.cpp"
#include "cfop.cpp"

/*
    Constants:
    const int CUBIES_BOTTOM = 0;
    const int CUBIES_LEFT = 1;
    const int CUBIES_FRONT = 2;
    const int CUBIES_RIGHT = 3;
    const int CUBIES_BACK = 4;
    const int CUBIES_TOP = 5;
*/

class cube
{
private:
    //side sides[5];
    std::string colours[6] = {"W","G","R","B","O","Y"};
    std::string sideColours[6][3][3];
    // to be added: list in which the solving moves are stored
public:
    cube();
    ~cube();

    void solveCube();

    // to be removed: serves as example
    void turnCube(char axis, int layer, bool clockwise);
};

cube::cube()
{
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 3; j++){
            for(int k = 0; k < 3; k++){
                sideColours[i][j][k] = colours[i];
            }
        }
    }
}

cube::~cube()
{
}

void cube::solveCube(){
    cfop cfop = new cfop();

    bool succesfull = cfop.solveCube(this->sideColours);
}

// THIS SERVES AS EXAMPLE CODE THAT NEEDS TO BE CHANGED
void cube::turnCube(char axis, int layer, bool clockwise) {
    int cube[3][3][3];
    int temp[3][3];
    int numLayers = 3; // the number of layers in the axis
    int layerIndex = layer - 1; // convert layer to 0-based index

    // determine the slice of the cube that will be turned
    switch (axis) {
        case 'x':
            for (int i = 0; i < numLayers; i++) {
                for (int j = 0; j < 3; j++) {
                    temp[i][j] = cube[layerIndex][i][j];

                }
            }
            break;
        case 'y':
            for (int i = 0; i < numLayers; i++) {
                for (int j = 0; j < 3; j++) {
                    temp[i][j] = cube[i][layerIndex][j];
                }
            }
            break;
        case 'z':
            for (int i = 0; i < numLayers; i++) {
                for (int j = 0; j < 3; j++) {
                    temp[i][j] = cube[i][j][layerIndex];
                }
            }
            break;
        default:
            // invalid axis, do nothing
            return;
    }

    // rotate the slice of the cube
    if (clockwise) {
        for (int i = 0; i < numLayers; i++) {
            for (int j = 0; j < 3; j++) {
                cube[layerIndex][i][j] = temp[2-j][i];
            }
        }
    } else {
        for (int i = 0; i < numLayers; i++) {
            for (int j = 0; j < 3; j++) {
                cube[layerIndex][i][j] = temp[j][2-i];
            }
        }
    }
}