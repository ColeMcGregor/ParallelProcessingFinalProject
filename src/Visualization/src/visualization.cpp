#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <random>       // Assigning colors

#include "vector.h"
#include "Body.h"
#include "Star.h"
#include "Planet.h"
#include "Moon.h"
#include "BlackHole.h"
#include "FileReader.h"

using namespace std;

/*
    g++ -std=c++11 -o vis visualization.cpp FileReader.cpp Body.cpp Star.cpp Planet.cpp Moon.cpp BlackHole.cpp vector.cpp -framework OpenGL -framework GLUT -I/usr/local/include
*/

// Global declarations
vector<Star> stars;
vector<Planet> planets;
vector<Moon> moons;
vector<BlackHole> blackholes;

//for graphics dont worry ill ocmment more later
void display() {
    // Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    // Set camera view
    gluLookAt(  0.0, 0.0, 100.0,
                0.0, 0.0, 0.0,
                0.0, 1.0, 0.0);

    //rendering stars
    cout << stars.size()<<endl;
    for (const auto& star : stars) {
        glPushMatrix();
        glColor3f(1.0, 1.0, 0.0); // Yellow for stars
        Vector pos = star.getPosition();
        double rad = star.getRadius();
        glTranslatef(pos.x, pos.y, pos.z);
        glutSolidSphere(rad, 100, 100); // Larger sphere for stars
        glPopMatrix();
    }

    //     // Render planets
    for (const auto& planet : planets) {
        glPushMatrix();
        glColor3f(0.0, 0.0, 1.0); // Blue for planets
        Vector pos = planet.getPosition();
        double rad = planet.getRadius();
        glTranslatef(pos.x, pos.y, pos.z);
        glutSolidSphere(rad, 100, 100); // Medium sphere for planets
        glPopMatrix();
    }

    // // Render moons
    // for (const auto& moon : moons) {
    //     glPushMatrix();
    //     glColor3f(0.5, 0.5, 0.5); // Gray for moons
    //     glTranslatef(moon.position.x, moon.position.y, moon.position.z);
    //     glutSolidSphere(0.5, 20, 20); // Small sphere for moons
    //     glPopMatrix();
    // }

    // // Render black holes
    // for (const auto& blackhole : blackholes) {
    //     glPushMatrix();
    //     glColor3f(0.0, 0.0, 0.0); // Black for black holes
    //     glTranslatef(blackhole.position.x, blackhole.position.y, blackhole.position.z);
    //     glutSolidSphere(3.0, 30, 30); // Large sphere for black holes
    //     glPopMatrix();
    // }
    
    // You can do similar rendering for planets, moons, and black holes here...

    glutSwapBuffers(); // Swap the buffers for smooth rendering
}
//graphics again dont worry
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
} 

void calculateScale() {
    GLdouble projMatrix[16];
    glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);

    // Perspective: Extract FOV and aspect ratio from projection matrix
    if (projMatrix[5] != 0) { // projMatrix[5] = cot(FOV/2)
        double fov = 2.0 * atan(1.0 / projMatrix[5]) * (180.0 / M_PI);
        double aspect = projMatrix[0] / projMatrix[5];

        std::cout << "Projection Matrix: Perspective" << std::endl;
        std::cout << "FOV: " << fov << " degrees, Aspect Ratio: " << aspect << std::endl;

        double z = -100.0; // The camera is looking at this depth
        double verticalScale = 2.0 * std::abs(z) * tan(fov * M_PI / 180.0 / 2.0); // Vertical scale
        double horizontalScale = verticalScale * aspect; // Horizontal scale

        std::cout << "At depth z = " << z << ":" << std::endl;
        std::cout << "Vertical Scale: " << verticalScale << std::endl;
        std::cout << "Horizontal Scale: " << horizontalScale << std::endl;
    }
}

int main(int argc, char** argv) {

    try {
        // Create a FileReader to read the output file generated by the simulation
        FileReader reader(argv[1]);
        int timestep = reader.readTimeStep();
        auto [localBodies, localStars, localPlanets, localMoons, localBH] = reader.readBodies();

        
        stars = move(localStars);
        planets = move(localPlanets);

        // Output summary of the read data
        cout << "Timestep: " <<timestep<<endl;
        cout << "Number of bodies: " << localBodies.size() << endl;
        cout << "Number of stars: " << stars.size() << endl;
        cout << "Number of planets: " << planets.size() << endl;
        cout << "Number of moons: " << moons.size() << endl;
        cout << "Number of black holes: " << blackholes.size() << endl;

    //graphics from here down
        glutInit(&argc,argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize(800, 600);
        glutCreateWindow("N-Body Simulation");
        glutReshapeFunc(reshape); 



        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0,800.0/600.0, 1.0,200.0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        calculateScale();

        glutReshapeFunc(reshape);
        glutDisplayFunc(display); // Register display callback 
        glutMainLoop();
        
    } catch (const std::exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
