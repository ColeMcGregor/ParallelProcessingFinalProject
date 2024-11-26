#include <vector>
#include <string>
#include "body.h"
#include "vector.h"

class FileManager {
public:
    void loadConfig(const string& filePath, vector<Body>& bodies, double& timestep, double& gravityMultiplier, int& iterations);
    void FileManager::outputResults(const string& filePath);
};
