#pragma once
#include <string.h>
#include <vector>

class cfop
{
private:
    const int CUBIES_BOTTOM = 0;
    const int CUBIES_LEFT = 1;
    const int CUBIES_FRONT = 2;
    const int CUBIES_RIGHT = 3;
    const int CUBIES_BACK = 4;
    const int CUBIES_TOP = 5;

    std::string colours[6] = {"W","G","R","B","O","Y"};
    std::vector<std::string> solvePattern;
    
public:
    cfop();
    ~cfop();

    void addToSolvePattern(std::string newTurn);
    std::vector<std::string> getSolvePattern();
    
    bool solveCube(std::string cube[6][3][3]);
    void cross(std::string cube[6][3][3]);

};