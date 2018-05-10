#ifndef PARSER
#define PARSER
#include <iostream>
#include <vector>
#include <fstream>
#include "Shapes/triangle.h"

using namespace std;

class Parser
{
    fstream file;

  public:
    Parser(string filename);
    vector<triangle> parse();
    vector<string> split(string input, char delimiter);
};
#endif