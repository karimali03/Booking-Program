#include <iostream>
#include "user.h"
#include <map>
#include "tools.h"

using namespace std;

#ifndef admin__
#define admin__

class  admin: public user
{
public:
    admin(){
        type=1;
    }

};

#endif
