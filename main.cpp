//Christopher Settles
#include <iostream>
#include <vector>
#include <fstream>
#include "Control/Ray.h"
#include "Shapes/Sphere.h"
#include "Shapes/Plane.h"
#include "Control/Lighting/Light.h"
#include "Control/Lighting/DirectionalLight.h"
#include "Control/BoundingVolume.h"
#include "Shapes/triangle.h"
#include "parser.h"

using namespace std;
const float PI = 3.1415926;
const vec3 backgroundcolor = vec3(0, 204, 204);

void render(vec3 userstartdirection, vec3 userstartpoint, vector<Shape *> listOfShapes, vector<Light *> listofLights,
            unsigned raysPerPixel, bool perspective);

void outputPictureToFile(vector<vector<vec3>> pixels, string);

vec3 computeAverageColor(vector<vec3> colors);

void createShapesAndRender();

void getRays(const vec3 &userstartdirection, const vec3 &userstartpoint, unsigned int raysPerPixel, bool perspective,
             int width, int height, int j, int k, vector<Ray *> &rays);

int main() {

    clock_t t1,t2;
    t1=clock();
    createShapesAndRender();

    t2=clock();
    float diff ((float)t2-(float)t1);
    cout<<diff<<endl;
    return 0;
}

void createShapesAndRender() {//The user will tell the draw function that there are a list of spheres and capsules (shapes), and
    //How he wants to look at those shapes (Point and direction);
    vec3 userstartpoint = vec3(2, 0, 0);
    //The direction really states the distance to the screen as the x component
    vec3 userstartdirection = vec3(-360, 0, 0); //Can only have an x component
    //Can only look in the -x direction because we want to look left when y becomes more negative (look in negative x dir)
    vector<Shape *> listofshapes;
    vector<Light *> listoflights;

//    This will create a spiral of circles, but because it creates many circles it is slowwwww
//    for (float i = 0; i < PI*10; i+= PI/10) {
//    	listofshapes.push_back(new Sphere(vec3(-20  - 10*i, 20 *cos(i),  20 * sin(i)), 3, vec3(int(abs(i*30)) % 254, 0, 255)));//Blue Sphere
//    }

//    listofshapes.push_back(new Triangle(vec3(20,0,0), vec3(10,0,0), vec3(0,15,0), vec3(0,255,128)));
//    listofshapes.push_back(new Plane(Point(-40, 0, 10), Direction(-10, 0, 0), Direction(0, 100, 0), RGB(255, 120, 0)));

//    listofshapes.push_back(new triangle(vec3(-100,0,0), vec3(0,-10,0), vec3(0,10,10), vec3(0,128,255)));
//    listofshapes.push_back(new triangle(vec3(0,0,0), vec3(0,-10,0), vec3(0,0,10), vec3(0,128,255)));
    Parser parser("dragon.obj");

    vector <triangle> some_triangles = parser.parse();
    for(triangle& tri: some_triangles){
        cout <<tri.getPoint_A() <<' ' <<tri.getPoint_B() <<' ' << tri.getPoint_C() <<endl;

        tri.setPoint_A(vec3(tri.getPoint_A().x(), tri.getPoint_A().y(), tri.getPoint_A().z()));
        tri.setPoint_B(vec3(tri.getPoint_B().x(), tri.getPoint_B().y(), tri.getPoint_B().z()));
        tri.setPoint_C(vec3(tri.getPoint_C().x(), tri.getPoint_C().y(), tri.getPoint_C().z()));
        listofshapes.push_back(&tri);
    }
//    listofshapes.push_back(new Sphere(vec3(0, 0, 0), 10, vec3(255, 0, 0)));

//    const int NUMBER_OF_SPHERES = 27;
//    int cube = cbrt(NUMBER_OF_SPHERES);
//    for(int i = 0; i < cube; i++){
//        for (int j = 0; j < cube; j++){
//            for (int k = 0; k < cube; k++){
//                listofshapes.push_back(new Sphere(vec3(float(-50) - 10*i,
//                                                       float(-10) -5*j,
//                                                       float(-10) -5*k),
//                                       1, vec3((abs((i+j+k)*30)) % 254, 0, 255)));
//            }
//        }
//    }

//    for(int i = 0; i < cube; i++){
//        for (int j = 0; j < cube; j++){
//            for (int k = 0; k < cube; k++){
//                listofshapes.push_back(
//                        new Box(vec3(float(-50) - 10*i, float(-10) -5*j, float(-10) -5*k),
//                                vec3(float(-50) - 10*(i+1), float(-10) -5*(j+1), float(-10) -5*(k+1)),
//                                vec3((abs((i+j+k)*30)) % 254, 0, 255)));
//            }
//        }
//    }

//    listofshapes.push_back(new Sphere(vec3(-20, 0, 0), 4, vec3(0, 0, 255)));//Blue Sphere
//    listofshapes.push_back(new Sphere(vec3(-25, 10, 20), 3, vec3(0, 255, 0)));//Green Sphere
//    listofshapes.push_back(new Sphere(vec3(-20, 0, 2), 5, vec3(0, 255, 0)));//Green Sphere
//    listofshapes.push_back(new Sphere(vec3(-20, -10, 2), 3, vec3(255, 0, 0)));//Red Sphere
//    listofshapes.push_back(new Box(vec3(-20, 2, 3), vec3(-30, 20, 5), vec3(255, 0, 255)));

//    listofshapes.push_back(new Plane(vec3(-30, -10, 15), vec3(0, -5, 0), vec3(0, 0, 7), vec3(255, 120, 0)));
//    listofshapes.push_back(new Triangle(vec3(-20, 10, 0), vec3(0, 10, 0), vec3(0, 0, 10), vec3(0, 69, 96)));
    listoflights.push_back(new DirectionalLight(userstartdirection));
//    listofshapes.push_back(new Box(Point(-50, -50, 30), Direction(-10, 0, 0), Direction(0, 10, 0), Direction(0,0,10), Color(255, 20, 60)));
//    listofshapes.push_back(new Box(Point(-50, -10, -20), Direction(-10, 0, 0), Direction(0, 10, 0), Direction(0, 0, 10), Color(255, 20, 60)));

//    listofshapes.push_back(new Capsule(Point(-2, 0, 15), Point(-225, 0, 15), 3, Color(255, 0, 120)));//Pink Capsule Top
//    listofshapes.push_back(new Capsule(Point(-2,-15, 0), Point(-225,-15, 0), 3, Color(255, 0, 120)));//Pink Capsule Left
//    listofshapes.push_back(new Capsule(Point(-2, 15, 0), Point(-225, 15, 0), 3, Color(255, 0, 120)));//Pink Capsule Right
//    listofshapes.push_back(new Capsule(Point(-2, 0,-15), Point(-225, 0,-15), 3, Color(255, 0, 120)));//Pink Capsule Bottom

//    listofshapes.push_back(new Capsule(Point(-2, 0, 0),  Point(-225, 0, 0), 3, Color(255, 0, 120))); //Pink Capsule Center
//    listofshapes.push_back(new Capsule(Point(-2, -5, 2), Point(-2, 0, 2), 3,  Color(255, 0, 120)));//Pink Capsule
    unsigned numRays = 20;
    render(userstartdirection, userstartpoint, listofshapes, listoflights, numRays, true);
}

void render(vec3 userstartdirection, vec3 userstartpoint, vector<Shape *> listOfShapes, vector<Light *> listOfLights,
            unsigned raysPerPixel, bool perspective) {

    int width = 500, height = 500;
    vector<vector<vec3>> imagePixels(width, vector<vec3>(height));
    BoundingVolume bvh = BoundingVolume(listOfShapes);
    cout <<"Finished constructing BVH!" <<endl;

    for (int j = 0; j < height; j++) {
        for (int k = 0; k < width; k++) {
            vector<Ray *> rays;
            getRays(userstartdirection, userstartpoint, raysPerPixel, perspective, width, height, j, k, rays);

            vector<vec3> closestColors;
            for (auto &pixelRay : rays) {
                vec3 closestColor = backgroundcolor;

                Shape *closestShape = bvh.closestIntersectionShape(pixelRay);
//                for(auto closestShape: listOfShapes) {
                    int numLightsHit = 0;
                    if (closestShape != nullptr) {
//                        cout <<"Ray's dirs on this intersection: " <<pixelRay->getdir() <<endl;
                        for (auto &light : listOfLights) {
                            float ratio = light->getRatioOfLightOnShape(closestShape, pixelRay);
                            if (ratio > 0) {
                                numLightsHit++;
                            }
                            closestColor = ratio * closestShape->getColor();
                        }//Done going through all the lights
                        if (numLightsHit >= 1) {
                            closestColor /= numLightsHit;
                        }
                    }
//                }
                closestColors.push_back(closestColor);
            }
            imagePixels[j][k] = computeAverageColor(closestColors);
        }
    }

    string filename_type = perspective ? "perspective.pmm" : "orthographic.ppm";
    outputPictureToFile(imagePixels, filename_type);
}

void getRays(const vec3 &userstartdirection, const vec3 &userstartpoint, unsigned int raysPerPixel, bool perspective,
             int width, int height, int j, int k, vector<Ray *> &rays) {
    //The x dir doesn't change, j = y direction, k = z direction. The z direction is minus because 0,0,0 is
    //in the top left corner instead of bottom left (how a computer thinks)
    float lowy = j - width / 2;
    float highy = (j + 1) - width / 2;
    float lowz = -(k - height / 2);
    float highz = -((k + 1) - height / 2);

    //Generate the random rays that will shoot through each pixel. (currently, 20 rays shoot through one pixel)
    for (int i = 0; i < raysPerPixel; i++) {
        float randy = lowy + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (highy - lowy)));
        float randz = lowz + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (highz - lowz)));

        if (perspective) {
            rays.emplace_back(new Ray(vec3(userstartdirection.x(), randy, randz), userstartpoint));
        } else { //orthographic
            float pointy = randy / width * 50;
            float pointz = randz / height * 50;
            rays.emplace_back(new Ray(userstartdirection, vec3(userstartpoint.x(), pointy, pointz)));
        }
    }
}

void outputPictureToFile(vector<vector<vec3>> pixels, string filename) {
    ofstream myFile;
    myFile.open(filename);
    unsigned long width = pixels.size();           //This could be backwards.
    unsigned long height = pixels[0].size();
    myFile << "P3\n" << width << " " << height << "\n255\n";

    for (int i = 0; i < pixels.size(); i++) {
        for (int j = 0; j < pixels[i].size(); j++) {
            myFile << (int) pixels[i][j].r() << " " << (int) pixels[i][j].g() << " " << (int) pixels[i][j].b() << "\n";

        }
    }
    myFile.close();
}
vec3 computeAverageColor(vector<vec3> colors) {
    vec3 avg = vec3(0, 0, 0);
    for (auto &color: colors) {
        avg += vec3(color.r(), color.g(), color.b());
    }
    avg /= colors.size();
    return vec3(avg.x(), avg.y(), avg.z());
}
