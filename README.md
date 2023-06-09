# SSRC
This code was designed to be used with an ESP32 using the platform.io extension for Visual Studio Code.

When the algorithm is initialized it needs a configuration for a starting cube, this can be done as follows:
```cpp
cfop algorithm;
std::string cube[6][3][3] = =
	{ {   { "W1", "W2", "W3" }, { "W4", "W5", "W6" }, { "W7", "W8", "W9" }  },
	  {   { "O1", "O2", "O3" }, { "O4", "O5", "O6" }, { "O7", "O8", "O9" }  },
	  {   { "B1", "B2", "B3" }, { "B4", "B5", "B6" }, { "B7", "B8", "B9" }  },
	  {   { "R1", "R2", "R3" }, { "R4", "R5", "R6" }, { "R7", "R8", "R9" }  },
	  {   { "G1", "G2", "G3" }, { "G4", "G5", "G6" }, { "G7", "G8", "G9" }  },
	  {   { "Y1", "Y2", "Y3" }, { "Y4", "Y5", "Y6" }, { "Y7", "Y8", "Y9" }  },
	};

algorithm.setCube(cube);
```
To generate a randomly shuffled cube:
```cpp
algorithm.shuffleCube();
```
To start solving the cube use this method: 
```cpp
algorithm.solveCube();
```
