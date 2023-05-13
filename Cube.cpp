#include "Cube.h"
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
const int ROWS = 3;
const int COLUMNS = 3;
const int FACES = 6;

Cube::Cube(/* args */)
    : cube{
          {{'W', 'W', 'W'}, {'W', 'W', 'W'}, {'W', 'W', 'W'}}, // Top (white)
          {{'R', 'R', 'R'}, {'R', 'R', 'R'}, {'R', 'R', 'R'}}, // Front (red)
          {{'B', 'B', 'B'}, {'B', 'B', 'B'}, {'B', 'B', 'B'}}, // Back (blue)
          {{'G', 'G', 'G'}, {'G', 'G', 'G'}, {'G', 'G', 'G'}}, // Left (green)
          {{'O', 'O', 'O'}, {'O', 'O', 'O'}, {'O', 'O', 'O'}}, // Right(orange)
          {{'Y', 'Y', 'Y'}, {'Y', 'Y', 'Y'}, {'Y', 'Y', 'Y'}}  // Bottom(yellow)
      }
{
}
void Cube::printCube()
{
    std::ofstream myfile;
    myfile.open("Cube.csv");
    for (int i = 0; i < 6; ++i)
    {
        for (int x = 0; x < 3; ++x)
        {
            for (int y = 0; y < 3; ++y)
            {
                myfile << cube[i][x][y] << " ";
            }
            std::endl(myfile);
        }
        std::endl(myfile);
    }
    std::endl(myfile);
}

void Cube::shuffleCube()
{
    srand(time(0));
    int rotateNum = rand() % 100 + 50;

    for (int i = 0; i < rotateNum; i++) {
        int dir = rand() % 1;
        if(dir == 0) {
            rotateFaceClockwise(static_cast<CubeFace>(rand() % 5));
        }
        else if(dir == 1) {
            rotateFaceCounterClockwise(static_cast<CubeFace>(rand() % 5));
        }
    }
}



void Cube::rotateFaceClockwise(CubeFace face)
{
    // Rotate the given face clockwise
    char tmp[ROWS][COLUMNS];
    for (int row = 0; row < ROWS; ++row)
    {
        for (int col = 0; col < COLUMNS; ++col)
        {
            tmp[row][col] = cube[face][COLUMNS - col - 1][row];
        }
    }
    for (int row = 0; row < ROWS; ++row)
    {
        for (int col = 0; col < COLUMNS; ++col)
        {
            cube[face][row][col] = tmp[row][col];
        }
    }

    // Update the surrounding faces
    char tmpRow[COLUMNS];
    switch (face)
    {
    case FRONT:
        // Rotate adjacent rows on UP face
        for (int col = 0; col < COLUMNS; ++col)
        {
            tmpRow[col] = cube[UP][2][col];
            cube[UP][2][col] = cube[LEFT][COLUMNS - col - 1][2];
            cube[LEFT][COLUMNS - col - 1][2] = cube[DOWN][0][COLUMNS - col - 1];
            cube[DOWN][0][COLUMNS - col - 1] = cube[RIGHT][col][0];
            cube[RIGHT][col][0] = tmpRow[col];
        }
        break;
    case BACK:
        // Rotate adjacent rows on UP face
        for (int col = 0; col < COLUMNS; ++col)
        {
            tmpRow[col] = cube[UP][0][COLUMNS - col - 1];
            cube[UP][0][COLUMNS - col - 1] = cube[RIGHT][col][2];
            cube[RIGHT][col][2] = cube[DOWN][2][col];
            cube[DOWN][2][col] = cube[LEFT][COLUMNS - col - 1][0];
            cube[LEFT][COLUMNS - col - 1][0] = tmpRow[col];
        }
        break;
    case LEFT:
        // Rotate adjacent rows on UP face
        for (int row = 0; row < ROWS; ++row)
        {
            tmpRow[row] = cube[UP][ROWS - row - 1][0];
            cube[UP][ROWS - row - 1][0] = cube[BACK][row][COLUMNS - 1];
            cube[BACK][row][COLUMNS - 1] = cube[DOWN][row][0];
            cube[DOWN][row][0] = cube[FRONT][ROWS - row - 1][0];
            cube[FRONT][ROWS - row - 1][0] = tmpRow[row];
        }
        break;
    case RIGHT:
        // Rotate adjacent rows on UP face
        for (int row = 0; row < ROWS; ++row)
        {
            tmpRow[row] = cube[UP][row][COLUMNS - 1];
            cube[UP][row][COLUMNS - 1] = cube[FRONT][row][COLUMNS - 1];
            cube[FRONT][row][COLUMNS - 1] = cube[DOWN][row][COLUMNS - 1];
            cube[DOWN][row][COLUMNS - 1] = cube[BACK][ROWS - row - 1][0];
            cube[BACK][ROWS - row - 1][0] = tmpRow[row];
        }
        break;
    case UP:
        // Rotate adjacent rows on LEFT face
        for (int col = 0; col < COLUMNS; ++col)
        {
            tmpRow[col] = cube[LEFT][0][col];
            cube[LEFT][0][col] = cube[BACK][0][col];
            cube[BACK][0][col] = cube[RIGHT][0][col];
            cube[RIGHT][0][col] = cube[FRONT][0][col];
            cube[FRONT][0][col] = tmpRow[col];
        }
        break;
    case DOWN:
        // Rotate adjacent rows on LEFT face
        for (int col = 0; col < COLUMNS; ++col)
        {
            tmpRow[col] = cube[LEFT][ROWS - 1][col];
            cube[LEFT][ROWS - 1][col] = cube[FRONT][ROWS - 1][col];
            cube[FRONT][ROWS - 1][col] = cube[RIGHT][ROWS - 1][col];
            cube[RIGHT][ROWS - 1][col] = cube[BACK][ROWS - 1][COLUMNS - col - 1];
            cube[BACK][ROWS - 1][COLUMNS - col - 1] = tmpRow[col];
        }
        break;
    }
}

void Cube::rotateFaceCounterClockwise(CubeFace face)
{
    // Rotate the given face counter-clockwise
    char tmp[ROWS][COLUMNS];
    for (int row = 0; row < ROWS; ++row)
    {
        for (int col = 0; col < COLUMNS; ++col)
        {
            tmp[row][col] = cube[face][col][ROWS - row - 1];
        }
    }
    for (int row = 0; row < ROWS; ++row)
    {
        for (int col = 0; col < COLUMNS; ++col)
        {
            cube[face][row][col] = tmp[row][col];
        }
    }

    // Update the surrounding faces
    char tmpRow[COLUMNS];
    switch (face)
    {
    case FRONT:
        // Rotate adjacent rows on UP face
        for (int col = 0; col < COLUMNS; ++col)
        {
            tmpRow[col] = cube[UP][2][COLUMNS - col - 1];
            cube[UP][2][COLUMNS - col - 1] = cube[RIGHT][col][0];
            cube[RIGHT][col][0] = cube[DOWN][0][col];
            cube[DOWN][0][col] = cube[LEFT][COLUMNS - col - 1][2];
            cube[LEFT][COLUMNS - col - 1][2] = tmpRow[col];
        }
        break;
    case BACK:
        // Rotate adjacent rows on UP face
        for (int col = 0; col < COLUMNS; ++col)
        {
            tmpRow[col] = cube[UP][0][col];
            cube[UP][0][col] = cube[LEFT][COLUMNS - col - 1][0];
            cube[LEFT][COLUMNS - col - 1][0] = cube[DOWN][2][COLUMNS - col - 1];
            cube[DOWN][2][COLUMNS - col - 1] = cube[RIGHT][col][2];
            cube[RIGHT][col][2] = tmpRow[col];
        }
        break;
    case UP:
        // Rotate adjacent rows on BACK face
        for (int col = 0; col < COLUMNS; ++col)
        {
            tmpRow[col] = cube[BACK][0][col];
            cube[BACK][0][col] = cube[RIGHT][0][col];
            cube[RIGHT][0][col] = cube[FRONT][0][col];
            cube[FRONT][0][col] = cube[LEFT][0][col];
            cube[LEFT][0][col] = tmpRow[col];
        }
        break;
    case DOWN:
        // Rotate adjacent rows on FRONT face
        for (int col = 0; col < COLUMNS; ++col)
        {
            tmpRow[col] = cube[FRONT][2][col];
            cube[FRONT][2][col] = cube[RIGHT][2][col];
            cube[RIGHT][2][col] = cube[BACK][2][COLUMNS - col - 1];
            cube[BACK][2][COLUMNS - col - 1] = cube[LEFT][2][COLUMNS - col - 1];
            cube[LEFT][2][COLUMNS - col - 1] = tmpRow[col];
        }
        break;
    case LEFT:
        // Rotate adjacent columns on UP face
        for (int row = 0; row < ROWS; ++row)
        {
            tmpRow[row] = cube[UP][row][0];
            cube[UP][row][0] = cube[BACK][ROWS - row - 1][COLUMNS - 1];
            cube[BACK][ROWS - row - 1][COLUMNS - 1] = cube[DOWN][row][0];
            cube[DOWN][row][0] = cube[FRONT][row][0];
            cube[FRONT][row][0] = tmpRow[row];
        }
        break;
    case RIGHT:
        // Rotate adjacent columns on UP face
        for (int row = 0; row < ROWS; ++row)
        {
            tmpRow[row] = cube[UP][row][COLUMNS - 1];
            cube[UP][row][COLUMNS - 1] = cube[FRONT][row][COLUMNS - 1];
            cube[FRONT][row][COLUMNS - 1] = cube[DOWN][row][COLUMNS - 1];
            cube[DOWN][row][COLUMNS - 1] = cube[BACK][ROWS - row - 1][0];
            cube[BACK][ROWS - row - 1][0] = tmpRow[row];
        }
        break;
    }
}

Cube::~Cube()
{
}



int main(void)
{
    Cube cubie;
    cubie.shuffleCube();
    cubie.printCube();
}