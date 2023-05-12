#include "Cube.h"
#include <iostream>
#include <fstream>
#include <string>  
#include <algorithm>
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

Cube::Cube(/* args */)
    :  cube{
    { {'W', 'W', 'W'}, {'W', 'W', 'W'}, {'W', 'W', 'W'} },// Top (white)
    { {'R', 'R', 'R'}, {'R', 'R', 'R'}, {'R', 'R', 'R'} },// Front (red)
    { {'B', 'B', 'B'}, {'B', 'B', 'B'}, {'B', 'B', 'B'} },// Back (blue)
    { {'G', 'G', 'G'}, {'G', 'G', 'G'}, {'G', 'G', 'G'} },// Left (green)
    { {'O', 'O', 'O'}, {'O', 'O', 'O'}, {'O', 'O', 'O'} },// Right(orange)
    { {'Y', 'Y', 'Y'}, {'Y', 'Y', 'Y'}, {'Y', 'Y', 'Y'} } //Bottom(yellow)
    }
{

}
void Cube::printCube() {
    std::ofstream myfile;
    myfile.open("Cube.csv");
    for( int i = 0; i < 6; ++i ){
        for( int x = 0; x < 3; ++x ){
            for( int y = 0; y < 3; ++y ){
                myfile << cube[i][x][y] << " ";
            }
            std::endl( myfile );
        }
        std::endl( myfile );
    }
    std::endl( myfile );
}

void Cube::shuffleCube() {
    //Convert to 1D array
    char tempArray[6*3*3];
    for( int i = 0; i < 6; ++i ){
        for( int x = 0; x < 3; ++x ){
            for( int y = 0; y < 3; ++y ){
            tempArray[i*3*3+ x*3+y] = cube[i][x][y];
            }
        }
    }

    //Shuffle 1D array
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(std::begin(tempArray), std::end(tempArray), std::default_random_engine(seed));

    //Convert back to 3D array
    for( int i = 0; i < 6; ++i ){
        for( int x = 0; x < 3; ++x ){
            for( int y = 0; y < 3; ++y ){
                cube[i][x][y] = tempArray[i*3*3+ x*3+y];
            }
        }
    }
}

Cube::~Cube()
{
}


int main(void) {
    Cube cubie;
    cubie.shuffleCube();
    cubie.printCube();

}