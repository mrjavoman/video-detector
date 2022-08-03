
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include "config.hpp"

/* Reads the given configuration file and builds a struct with the configuration parameters */
ConfigParams Params::Read(std::string configFile) {

    ConfigParams paramsData;
    // 
    std::cout << configFile << std::endl;

    if( std::ifstream is_file(configFile); is_file) {
        
        // Hash map to hold all read properties.
        std::unordered_map<std::string, std::string> configData;

        // Read all lines from config file.
        for( std::string line{}; std::getline(is_file, line); ) {

            // If line contains an equal sign we read it.
            if (line.find('=') != std::string::npos)  {
                
                // Split the line into key value pair and add it to the hash map
                std::istringstream iss{ line };
                if( std::string key{}, value{}; std::getline(std::getline(iss, key, '=') >> std::ws, value)) {
                    
                    configData[key] = value;
                }
            }
        }
        // Some debug output
        for (const auto& [id, value] : configData)
            std::cout << "ID: " << std::left << " " << id << " Value: " << value << '\n';
        // Set read data into struct        
        paramsData.pushoverUser = configData.count("pushoveruser") != 0 ? configData["pushoveruser"] : "";
        paramsData.pushoverToken = configData.count("pushovertoken") != 0 ? configData["pushovertoken"] : "";
        paramsData.classesFile = configData.count("classesfile") != 0 ? configData["classesfile"] : "";
        paramsData.confidenceThreshold = configData.count("confidence") != 0 ? std::stoi(configData["confidence"]) : 80;
        paramsData.NMSThreashold = configData.count("NMS") != 0 ? std::stod(configData["NMS"]) : 0.4;

        // For the detection classes split the set of         
        std::istringstream iss{ configData["detectionClasses"] };
        std::string detectionClass;
        while(getline(iss, detectionClass, ',')) {
            paramsData.detectionClasses.push_back(detectionClass);
        }

    } else {
        std::cerr << "Error opening configuration file ..." << std::endl;
    }

    return paramsData;
}