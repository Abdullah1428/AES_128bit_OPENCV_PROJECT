/* 
    AES 128 Bit Project 
    implementation by Abdullah1428
    CS Project
*/

#include "AES.hpp"

// this program will return true if the user types a keyword that is
// present in the arguments passed else it will return 0;
int program_args(int argc,char **argv,const char * keyword)
{
    // i = 0 for the exe file
    for(int i=1;i<argc;i++)
    {
        if(!strcmp(argv[i],keyword))
        {
            return 1;
        }
    }
    return 0;
}