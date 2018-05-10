//Christopher Settles
#include <iostream>
#include <vector>
#include <fstream>
#include "Control/Ray.h"
#include "Shapes/Sphere.h"
#include "Shapes/Plane.h"
#include "Shapes/Triangle.h"
#include "Control/Lighting/Light.h"
#include "Control/Lighting/DirectionalLight.h"
#include "Control/BoundingVolume.h"

using namespace std;
const double PI = 3.1415926;
const vec3 backgroundcolor = vec3(0, 204, 204);

void drawImage(vec3 userstartdirection, vec3 userstartpoint, vector<Shape *> listOfShapes, vector<Light *> listofLights,
               unsigned raysPerPixel, bool perspective);

void outputPictureToFile(vector<vector<vec3>> pixels);


vec3 computeAverageColor(vector<vec3> colors);

int main() {

    //The user will tell the draw function that there are a list of spheres and capsules (shapes), and
    //How he wants to look at those shapes (Point and direction);
    vec3 userstartpoint = vec3(20, 0, 0);
    //The direction really states the distance to the screen as the x component
    vec3 userstartdirection = vec3(-360, 0, 0); //Can only have an x component
    //Can only look in the -x direction because we want to look left when y becomes more negative (look in negative x dir)
    vector<Shape *> listofshapes;
    vector<Light *> listoflights;

    //Examples of shapes

//    This will create a spiral of circles, but because it creates many circles it is slowwwww
//    for (double i = -PI* 4; i < PI*4; i+= 0.40) {
//    	listofshapes.push_back(new Sphere(vec3(-20  - 10*i, 20 *cos(i),  20 * sin(i)), 3, vec3(0, 0, 255)));//Blue Sphere
//    }

    listofshapes.push_back(new Sphere(vec3(-20, 10, 0), 4, vec3(0, 0, 255)));//Blue Sphere
    listofshapes.push_back(new Sphere(vec3(-25, 10, 20), 3, vec3(0, 255, 0)));//Green Sphere
//    listofshapes.push_back(new Sphere(vec3(-20, 0, 2), 5, vec3(0, 255, 0)));//Green Sphere
    listofshapes.push_back(new Sphere(vec3(-20, -10, 2), 3, vec3(255, 0, 0)));//Red Sphere



    listofshapes.push_back(new Plane(vec3(-30, -10, 15), vec3(0, -5, 0), vec3(0, 0, 7), vec3(255, 120, 0)));
    listofshapes.push_back(new Triangle(vec3(-20, 10, 0), vec3(0, 10, 0), vec3(0, 0, 10), vec3(0, 69, 96)));
    listoflights.push_back(new DirectionalLight(vec3(-10, 20, 0)));
//    listofshapes.push_back(new Box(Point(-50, -50, 30), Direction(-10, 0, 0), Direction(0, 10, 0), Direction(0,0,10), Color(255, 20, 60)));
//    listofshapes.push_back(new Box(Point(-50, -10, -20), Direction(-10, 0, 0), Direction(0, 10, 0), Direction(0, 0, 10), Color(255, 20, 60)));

//    listofshapes.push_back(new Capsule(Point(-2, 0, 15), Point(-225, 0, 15), 3, Color(255, 0, 120)));//Pink Capsule Top
//    listofshapes.push_back(new Capsule(Point(-2,-15, 0), Point(-225,-15, 0), 3, Color(255, 0, 120)));//Pink Capsule Left
//    listofshapes.push_back(new Capsule(Point(-2, 15, 0), Point(-225, 15, 0), 3, Color(255, 0, 120)));//Pink Capsule Right
//    listofshapes.push_back(new Capsule(Point(-2, 0,-15), Point(-225, 0,-15), 3, Color(255, 0, 120)));//Pink Capsule Bottom

//    listofshapes.push_back(new Capsule(Point(-2, 0, 0),  Point(-225, 0, 0), 3, Color(255, 0, 120))); //Pink Capsule Center
//    listofshapes.push_back(new Capsule(Point(-2, -5, 2), Point(-2, 0, 2), 3,  Color(255, 0, 120)));//Pink Capsule
    unsigned numRays = 20;
    drawImage(userstartdirection, userstartpoint, listofshapes, listoflights, numRays, true);
    return 0;
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

void drawImage(vec3 userstartdirection, vec3 userstartpoint, vector<Shape *> listOfShapes, vector<Light *> listOfLights,
               unsigned raysPerPixel, bool perspective) {
    int width = 500, height = 500;
    vector<vector<vec3>> imagePixels(width, vector<vec3>(height));

    for (int j = 0; j < height; j++) {
        for (int k = 0; k < width; k++) {
            //The x dir doesn't change, j = y direction, k = z direction. The z direction is minus because 0,0,0 is
            //in the top left corner instead of bottom left (how a computer thinks)
            float lowy = j - width / 2;
            float highy = (j + 1) - width / 2;
            float lowz = -(k - height / 2);
            float highz = -((k + 1) - height / 2);

            //Generate the random rays that will shoot through each pixel. (currently, 20 rays shoot through one pixel)
            vector<Ray *> rays;
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
            BoundingVolume bvh = BoundingVolume(listOfShapes);
            vector<vec3> closestColors;
            for (auto &pixelRay : rays) {
                vec3 closestColor = backgroundcolor;

                Shape *closestShape = bvh.closestIntersectionShape(pixelRay);

                int numLightsHit = 0;
                if (closestShape != nullptr) {
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
                closestColors.push_back(closestColor);
            }
            imagePixels[j][k] = computeAverageColor(closestColors);
        }
    }

    string filename_type = perspective ? "perspective.pmm" : "orthographic.ppm";
    outputPictureToFile(imagePixels, filename_type);
}

vec3 computeAverageColor(vector<vec3> colors) {
    vec3 avg = vec3(0, 0, 0);
    for (auto &color: colors) {
        avg += vec3(color.r(), color.g(), color.b());
    }
    avg /= colors.size();
    return vec3(avg.x(), avg.y(), avg.z());
}
