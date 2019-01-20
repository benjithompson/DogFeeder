#ifndef FeederRestApi_h
#define FeederRestApi_h

#include <aREST.h>

class FeederRestApi{

    public:

        //objects
        aREST _rest;

        //methods
        FeederRestApi();
        
        aREST getARestApi();
        int testFunction0(String command);
        int testFunction1(String command);


    private:
        
    };

#endif
