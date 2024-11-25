/**
 * @file Simulation.cpp
 * @brief This file contains the implementation of the Simulation class, which is used to run the simulation
 * 
 * @algorithm: this simulation will take in an input file, parse the information, and create the bodies in the simulation
 * it will then assign openMP threads to handle each body, and each thread will handle the calculations for that body
 * each thread will also handle the output of that body to a file
 * 
 * @author: Cole McGregor, Hawk Lindner, Brandon Trama
 * @requirements: FileManager class, which is used to parse the input file for the creation of bodies in the simulation, and the output of the bodies to a file
 * @dependencies: body.cpp, filemanager.cpp
 */

#include <vector>
#include <string>
#include <omp.h>
#include "Body.h" // Include your Body class header
#include "FileManager.h" // Include your FileManager class header

using namespace std;

class Simulation {
    public:
        vector<Body> bodies; // vector of bodies in the simulation
        string inputFile; // input file for the simulation
        string outputFile; // output file for the simulation
        FileManager fileManager; // file manager for the simulation

        Simulation(const string& inputFile, const string& outputFile)
            : inputFile(inputFile), outputFile(outputFile) {
                // load the bodies from the input file
                bodies = fileManager.loadConfig(inputFile);
            }
        
        void run(double timeStep, int numSteps) {
            #pragma omp parallel
            {   
                for (int step = 0; step < numSteps; step++) {
                    // divide the work among threads
                    #pragma omp for
                    for (int i = 0; i < bodies.size(); i++) {
                        /**
                         * calculate forces on each body
                        */
                        }
                    }

                    // update the bodies' positions and velocities
                    #pragma omp for
                    for (int i = 0; i < bodies.size(); i++) {
                        bodies[i].update(timeStep);
                    }

                    // a single thread will output the results to the output file every 100 steps
                    #pragma omp single
                    {
                        if (step % 100 == 0) {
                            fileManager.outputResults(outputFile, bodies);
                        }
                    }
            }
        }
};

int main() {
    const string inputFile = "input.txt";
    const string outputFile = "output.txt";

    // create the sim
    Simulation sim(inputFile, outputFile);
    // set number of threads (default is number of cores)
    omp_set_num_threads(omp_get_max_threads());
    // run the sim
    sim.run(0.01, 1000);

    return 0;
}
