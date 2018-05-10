#include <iostream>
#include "parser.h"

using namespace std;

int main()
{
    cout << "Testing the object file parser" << endl;
    Parser parser("cow.obj");
    parser.parse();
    return 0;
}