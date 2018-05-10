#ifndef PARSER
#define PARSER
#include <iostream>
#include <vector>
#include <fstream>
#include "Shapes/Triangle.h"

using namespace std;

class Parser
{
    fstream file;

  public:
    Parser(string filename);
    vector<triangle> parseTrianglesFromObj();
    vector<string> split(string input, char delimiter);
};
#endif