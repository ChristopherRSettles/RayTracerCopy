//Parser written by Pradyumna Shome. All credit to him.
#include <iostream>
#include <sstream>
#include "parser.h"

using std::stof;
using std::stoi;

Parser::Parser(string filename)
{
    file = fstream(filename.c_str(), fstream::in);
    if (file.is_open())
    {
        cout << "File is open." << endl;
    }
    else
    {
        cerr << "Unable to open file." << endl;
    }
}
// Returns a vector of strings when split by a delimiter
vector<string> Parser::split(string input, char delimiter)
{
    vector<string> tokens;
    stringstream stream(input);
    string token;
    while (getline(stream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

vector<triangle> Parser::parseTrianglesFromObj()
{
    char VERTEX_DESCRIPTOR = 'v';
    char FACE_DESCRIPTOR = 'f';
    char COMMENT_DESCRIPTOR = '#';
    vector<triangle> triangles;
    vector<vec3> vertices;
    string line;
    while (getline(file, line))
    {
        char lineDescriptor = line[0];
        if (lineDescriptor == VERTEX_DESCRIPTOR)
        {
            vector<string> lineTokens = split(line, ' ');

            // Each line consists of v followed by three numbers, the three numbers go into the vertex constructor
            vec3 vertex(stof(string(lineTokens[1]).c_str()), stof(string(lineTokens[2]).c_str()), stof(string(lineTokens[3]).c_str()));
            vertices.push_back(vertex);
        }
        else if (lineDescriptor == FACE_DESCRIPTOR)
        {
            vector<string> lineTokens = split(line, ' ');
            // Each face selects three vertices to form the triangle from
            int firstVertexIndex = stoi(string(lineTokens[1]).c_str()) - 1;
            int secondVertexIndex = stoi(string(lineTokens[2]).c_str()) - 1;
            int thirdVertexIndex = stoi(string(lineTokens[3]).c_str()) - 1;
            triangle tri(vertices[firstVertexIndex], vertices[secondVertexIndex], vertices[thirdVertexIndex], vec3(244,92,66));
            triangles.push_back(tri);
        }
        else if (lineDescriptor == COMMENT_DESCRIPTOR)
        {
            // Ignore comments
            continue;
        }
        else
        {
            cerr << "Undefined reference to symbol." << endl;
        }
    }
    return triangles;
}
