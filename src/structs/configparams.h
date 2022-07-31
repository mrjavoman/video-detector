#ifndef CONFIG_PARAMS_H
#define CONFIG_PARAMS_H

#include <iostream>
#include <vector>

struct ConfigParams 
{
    std::string pushoverUser;
    std::string pushoverToken;
    std::string classesFile;
    int confidenceThreshold;
    int NMSThreashold;
    std::vector<std::string> detectionClasses;
};

#endif