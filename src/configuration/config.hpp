#ifndef CONFIG_H
#define CONFIG_H

#include "../structs/configparams.h"

class Params 
{
    private:

    public:
        ConfigParams Read(std::string params = "config.cfg");        

};

#endif