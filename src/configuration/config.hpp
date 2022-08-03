#ifndef CONFIG_H
#define CONFIG_H

#include "../structs/configparams.h"

class Params 
{
    private:

    public:
        static ConfigParams Read(std::string configFile = "./config.cfg");        

};

#endif