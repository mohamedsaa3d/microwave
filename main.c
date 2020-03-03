//-----------------------------------------------------------//
//         ######################################            //
//         ##### MicroWave Embedded Project #####            //
//         ######################################            //
//                 By  :   Mohamed Saad                      //
//                 Date:   3 March 2020                      //
//-----------------------------------------------------------//

#include "Libraries/MCU_init.h"
#include "Libraries/scheduler.h"

extern u8 CONFIG_FLAG;

void main() //The main function
{
    // Starting the Tasks scheduler
    SCHEDULER_START();

    while(1);

    
}
