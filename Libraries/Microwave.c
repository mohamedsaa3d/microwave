#include "Microwave.h"

u8 GLOBAL_RESET=0;
extern u16 GLOBAL_ADC_BUFFER;

extern Task* QUEUE_PTR;

SENSORS_STRUCT SENSORS = {.TEMPERATURE=0,
                          .DOOR=0,
                          .PAUSE=0,
                          .WEIGHT=0}; //SENSORS STATUS

SETTIME_STRUCT STIME = {.MIN=0, 
                        .SEC=0, 
                        .MFLAG=0, 
                        .SFLAG=0,
                        .CONFIRMED=0}; //Global Variable stores the required heating time

KEYPAD_BUFFER_STRUCT KEYPAD_BUFFER = {.BUFFER=0, 
                                      .PRESS_FLAG=0, 
                                      .ENTER_FLAG=0, 
                                      .START_FLAG=0, 
                                      .CANCELL_FLAG=0};


//Declaring the required tasks
Task SCAN_START   ={.TaskStatus  = START_ISTATUS,  
                    .periodicity = START_PERIOD*PD_SCALE,  
                    .ptr         = SCAN_START_API,  
                    .tempDelay   = START_IDELAY*PD_SCALE};

Task SCAN_CANCEL  ={.TaskStatus  = CANCEL_ISTATUS, 
                    .periodicity = CANCEL_PERIOD*PD_SCALE, 
                    .ptr         = SCAN_CANCEL_API, 
                    .tempDelay   = CANCEL_IDELAY*PD_SCALE};


Task SCAN_KEYPAD  ={.TaskStatus  = KEYPAD_ISTATUS, 
                    .periodicity = KEYPAD_PERIOD*PD_SCALE, 
                    .ptr         = SCAN_KEYPAD_API, 
                    .tempDelay   = KEYPAD_IDELAY*PD_SCALE};

Task SCAN_WEIGHT  ={.TaskStatus  = WEIGHT_ISTATUS, 
                    .periodicity = WEIGHT_PERIOD*PD_SCALE, 
                    .ptr         = SCAN_WEIGHT_API, 
                    .tempDelay   = WEIGHT_IDELAY*PD_SCALE};

Task SCAN_DOOR    ={.TaskStatus  = DOOR_ISTATUS, 
                    .periodicity = DOOR_PERIOD*PD_SCALE, 
                    .ptr         = SCAN_DOOR_API, 
                    .tempDelay   = DOOR_IDELAY*PD_SCALE};

Task SCAN_TEMP    ={.TaskStatus  = TEMP_ISTATUS, 
                    .periodicity = TEMP_PERIOD*PD_SCALE, 
                    .ptr         = SCAN_TEMP_API, 
                    .tempDelay   = TEMP_IDELAY*PD_SCALE};

Task UPDATE_TIME  ={.TaskStatus  = UPDTIME_ISTATUS, 
                    .periodicity = UPDTIME_PERIOD*PD_SCALE, 
                    .ptr         = UPDATE_TIME_API, 
                    .tempDelay   = UPDTIME_IDELAY*PD_SCALE};

Task RUN_CONFIG   ={.TaskStatus  = RCONFG_ISTATUS, 
                    .periodicity = RCONFG_PERIOD, 
                    .ptr         = RUN_CONFIG_API, 
                    .tempDelay   = RCONFG_IDELAY*PD_SCALE};


void CREATE_TASKS_QUEUE(void)
{
    //Assigning Tasks and their priorities
    SCH_CreateTask( &RUN_CONFIG    , RCONFG_PRIORITY  );
    SCH_CreateTask( &SCAN_START    , START_PRIORITY   );
    SCH_CreateTask( &SCAN_CANCEL   , CANCEL_PRIORITY  );
    SCH_CreateTask( &SCAN_KEYPAD   , KEYPAD_PRIORITY  );
    SCH_CreateTask( &SCAN_WEIGHT   , WEIGHT_PRIORITY  );
    SCH_CreateTask( &SCAN_DOOR     , DOOR_PRIORITY    );
    SCH_CreateTask( &UPDATE_TIME   , UPDTIME_PRIORITY );
    SCH_CreateTask( &SCAN_TEMP     , TEMP_PRIORITY    );
}

void SCAN_START_API(void)
{
    u8 flag = 1;
    
    DIO_u8GetPinValue( START_PORT, START_PIN , &flag);
    
    if(!flag)
    {
        KEYPAD_BUFFER.START_FLAG = 1;
    }
}

void SCAN_CANCEL_API(void)
{
    u8 flag = 1;
    
    DIO_u8GetPinValue( CANCEL_PORT, CANCEL_PIN , &flag);
    
    if(!flag)
    {
        KEYPAD_BUFFER.CANCELL_FLAG = 1;
    } 
}

void RUN_CONFIG_API(void)
{
    static u8 flag=0;
    static u8 flag2=0;
    static u8 LoopIndex=0;
    
    if(GLOBAL_RESET)
    {
        flag=1;
        flag2=0;
        GLOBAL_RESET=0;
    }
    
    
    if (flag==0)
    {
        //---################### LOADING Pattern ###################---
        
        if(flag2==0) //Using flag to write this chars one time only not in every tick
        {
            LCD_WriteCMD(ClearDisplay);
            LCD_GOTO_XY(5,3);
            LCD_WriteLINE("LOADING"); //Loading Text
            LCD_WriteDATA(SmileChar); 
            flag2=1;
        }
        
        LoopIndex++;
            
        LCD_GOTO_XY(LoopIndex,1);
        LCD_WriteDATA(BlackChar);
        LCD_GOTO_XY(LoopIndex,2);
        LCD_WriteDATA(BlackChar);
        
        if(LoopIndex<5 || LoopIndex>12)
        {
            LCD_GOTO_XY(LoopIndex,3);
            LCD_WriteDATA(BlackChar);
        }
        
        LCD_GOTO_XY(LoopIndex,4);
        LCD_WriteDATA(BlackChar);
        
        
        if(LoopIndex>=16)
        {
            flag=1; //Finished Loading screen
        }
        
    }
    else if(flag==1)
    {
        //---################### REQUEST TIME SETTING ###################---
        //Clear Time Settings
        STIME.MIN=0;
        STIME.SEC=0;
        STIME.CONFIRMED=0;
        STIME.MFLAG=0;
        STIME.SFLAG=0;

        
        //Update the LCD and write a new message
        LCD_WriteCMD(ClearDisplay);
        LCD_GOTO_XY(2,1);
        LCD_WriteLINE("SET HEAT. TIME");
        LCD_GOTO_XY(1,2);
        LCD_WriteLINE("----------------"); 
        LCD_GOTO_XY(1,3);
        LCD_WriteLINE("= __:__ <M:S>");
        
        LCD_GOTO_XY(3,4);
        LCD_WriteLINE("^^"); 

        flag = 2; 
    }
    else if(flag==2)
    {
        //---################### READING INPUT TIME ###################---
        //Read Minutes
        if( KEYPAD_BUFFER.ENTER_FLAG )
        {
            //MEANS THE USER PRESSED ENTER THEN SAVE THE TIME
            STIME.MIN = KEYPAD_BUFFER.BUFFER;
            STIME.MFLAG = 1; //SET THE FLAG TO INDICATE SAVING MINUTES SETTING

            //RESETTING BUFFER FOR THE NEXT STEP
            KEYPAD_BUFFER.BUFFER=0;
            KEYPAD_BUFFER.ENTER_FLAG =0;
            KEYPAD_BUFFER.START_FLAG=0;
            KEYPAD_BUFFER.CANCELL_FLAG=0; 
            
            LCD_GOTO_XY(3,4);
            LCD_WriteLINE("  "); 
            LCD_GOTO_XY(6,4);
            LCD_WriteLINE("^^"); 
            
            flag=3;
        }
    }
    else if(flag==3)
    {
        //---################### READING INPUT TIME ###################---
        //Read Seconds
        if( (KEYPAD_BUFFER.ENTER_FLAG)&&(KEYPAD_BUFFER.BUFFER||STIME.MIN) )
        {
            //API Can't take 0 seconds while the user entered 0 minutes
            //MEANS THE USER PRESSED ENTER THEN SAVE THE TIME
            STIME.SEC = KEYPAD_BUFFER.BUFFER;
            STIME.SFLAG = 1; //SET THE FLAG TO INDICATE SAVING SECONDS SETTING

            //RESETTING BUFFER FOR THE NEXT STEP
            KEYPAD_BUFFER.BUFFER=0;
            KEYPAD_BUFFER.ENTER_FLAG =0;
            KEYPAD_BUFFER.START_FLAG=0;
            KEYPAD_BUFFER.CANCELL_FLAG=0; 
            
            flag=4;
        }      
    }
    else if(flag==4)
    {
        //---################### ASSURING THE SETTING ###################---
        LCD_WriteCMD(ClearDisplay);
        LCD_WriteLINE("TIME= __:__");
        //-----------------------------------------------
        //Print first digit in minutes
        LCD_GOTO_XY(7,1);
        //LCD_WriteLINE("00");
        LCD_WriteNUMBER( STIME.MIN/10 ); 

        //Print second digit in minutes
        LCD_GOTO_XY(8,1);
        LCD_WriteNUMBER(STIME.MIN - (STIME.MIN/10)*10 );
        //-----------------------------------------------
        //Print first digit in seconds
        LCD_GOTO_XY(10,1);
        //LCD_WriteLINE("00");
        LCD_WriteNUMBER( STIME.SEC/10 ); 

        //Print second digit in seconds
        LCD_GOTO_XY(11,1);
        LCD_WriteNUMBER(STIME.SEC - (STIME.SEC/10)*10 );
        //-----------------------------------------------
        LCD_GOTO_XY(1,3);
        LCD_WriteLINE("START OR CANCEL");
        
        LCD_GOTO_XY(15,4);
        LCD_WriteLINE("??");
        
        //Make The TASKS READY (START_SCAN)
        //SCH_TaskRESUME( START_PRIORITY );
        //SCH_TaskRESUME( CANCEL_PRIORITY );
        
        flag=5;
        
    }
    else if(flag==5)
    {
        //---################### SETTING IS APPLIED/CANCELLED ###################---
        if( KEYPAD_BUFFER.START_FLAG)
        {
            //KEEP THE ENTERED TIME (CONFIRMED)
            LCD_WriteCMD(ClearDisplay);
            LCD_GOTO_XY(1,3);
            LCD_WriteLINE("Setting Applied");
            //SET THE FLAG OF FINAL CONFIRMATION
            STIME.CONFIRMED=1;
 
            //No need to runs this task again till finishing or canceling the process
            
            //SCH_TaskPAUSE( START_PRIORITY );
            //SCH_TaskPAUSE( RCONFG_PRIORITY );
            //SCH_TaskPAUSE( KEYPAD_PRIORITY );

            flag=6; //Any flag >5 
        }
        else if(KEYPAD_BUFFER.CANCELL_FLAG)
        {
            //SCH_TaskPAUSE( START_PRIORITY );
            //SCH_TaskPAUSE( CANCEL_PRIORITY );
        
            //Reset the settings process
            flag=1;
        }
        
    }
    
}


void SCAN_TEMP_API(void)
{
    u16 DIGITAL_READ=0; //Temp in DIGITAL value returned from ADC (0:1023)
   
    ADC_ReadPin(TEMP_PIN,&DIGITAL_READ); //READ THE DIGIAL VALUE
    
    //CALCULATE THE CORRESPONDING TEMP.
    SENSORS.TEMPERATURE =  ( (u32)DIGITAL_READ *( (u16)VDD_VOLT * (u16)100 ) )/(u32)(ADC_RESOLUTION-1) ;

}


void SCAN_KEYPAD_API(void)
{
    u8 DIGIT=0;
    u8 flag=0;
    
    flag = Keypad_ReadKey(  &DIGIT   );
    
    
    //PRINT TO LCD THE DIGIT
    if(flag)
    {
        //---------------------- Pressed Enter -----------------
        if(DIGIT==ENTER)
        {
            //USER FINISHED THE SETTING SUCCESSFULLY
            KEYPAD_BUFFER.ENTER_FLAG =1;
        }    
        else
        {
            //---------------------- Pressed Digit 0:9  -----------------
            if(DIGIT!=DELETE && DIGIT!=ENTER)
            {
                //DIGIT 0 : 9
                if(KEYPAD_BUFFER.BUFFER < 60)
                {
                    KEYPAD_BUFFER.BUFFER = KEYPAD_BUFFER.BUFFER*10 + DIGIT;
                    KEYPAD_BUFFER.PRESS_FLAG =1;
                }
                if(KEYPAD_BUFFER.BUFFER > 60)
                {
                    KEYPAD_BUFFER.BUFFER=60;
                }

            }
            //---------------------- Pressed Delete  -----------------
            else if(DIGIT==DELETE)
            {
                //DELETE
                KEYPAD_BUFFER.BUFFER = KEYPAD_BUFFER.BUFFER/10;
                KEYPAD_BUFFER.PRESS_FLAG =1;
            }
            
            //---------------------- Displaying the BUFFER  -----------------
            if(!STIME.MFLAG)
            {
                //Print first digit in minutes
                LCD_GOTO_XY(3,3);
                //LCD_WriteLINE("00");
                LCD_WriteNUMBER( KEYPAD_BUFFER.BUFFER/10 ); 

                //Print second digit in minutes
                LCD_GOTO_XY(4,3);
                LCD_WriteNUMBER(KEYPAD_BUFFER.BUFFER - (KEYPAD_BUFFER.BUFFER/10)*10 );
            }

            if(STIME.MFLAG && !STIME.SFLAG)
            {
                //Print first digit in seconds
                LCD_GOTO_XY(6,3);
                //LCD_WriteLINE("00");
                LCD_WriteNUMBER( KEYPAD_BUFFER.BUFFER/10 ); 

                //Print second digit in seconds
                LCD_GOTO_XY(7,3);
                LCD_WriteNUMBER(KEYPAD_BUFFER.BUFFER - (KEYPAD_BUFFER.BUFFER/10)*10 );    
            }
        }

        flag=0;
    }



}

void SCAN_WEIGHT_API(void)
{
    DIO_u8GetPinValue( WEIGHT_PORT, WEIGHT_PIN , &SENSORS.WEIGHT);
}

void SCAN_DOOR_API(void)
{
    DIO_u8GetPinValue( DOOR_PORT, DOOR_PIN , &SENSORS.DOOR); 
}

void UPDATE_TIME_API(void)
{
    u8 i;
    static u8 flag =0;
    
    if(STIME.CONFIRMED)
    {
        if(flag==0)
        {
            //Checking that door & weight sensors 
            
            LCD_WriteCMD(ClearDisplay);
            
            //Make The TASKS READY (START_SCAN)
            //SCH_TaskRESUME( WEIGHT_PRIORITY );
            //SCH_TaskRESUME( DOOR_PRIORITY );
            
            LCD_GOTO_XY(1,1);
            LCD_WriteLINE("DOOR: ");
            if(SENSORS.DOOR)
            {
               LCD_WriteLINE("CLOSED"); 
            }
            else
            {
                LCD_WriteLINE("OPENED <<<");
            }
            
            LCD_GOTO_XY(1,2);
            LCD_WriteLINE("WEIGHT:");
            if(SENSORS.WEIGHT)
            {
               LCD_WriteLINE("OK"); 
            }
            else
            {
                LCD_WriteLINE("EMPTY <<<");
            }
            
            if( SENSORS.DOOR && SENSORS.WEIGHT )
            {
                LCD_GOTO_XY(1,4);
                LCD_WriteLINE(">>ALL IS WELL<<");
                flag=2; //ALL IS OK (Let's Get Some Heat) (Starts after 2 cycles)
            }
            else
            {
                LCD_GOTO_XY(1,4);
                LCD_WriteLINE(">>CAUTIOUN!! <<");
            }
            
        }
        if(flag==2)
        {
            
            LCD_WriteCMD(ClearDisplay);
            for(i=1 ; i<5 ; i++)
            {
                LCD_GOTO_XY(8,i);
                LCD_WriteDATA(BlackChar);
                LCD_WriteDATA(BlackChar);
            }
            
            
            
            LCD_GOTO_XY(2,2);
            LCD_WriteLINE("TIMER");
            LCD_GOTO_XY(2,3);
            LCD_WriteLINE("__:__");
            
            LCD_GOTO_XY(11,2);
            LCD_WriteLINE("TEMP.");
            LCD_GOTO_XY(12,3);
            LCD_WriteLINE("__C");
            
            flag=3;
        }
        else if(flag==3)
        {
            if( (STIME.MIN>0 ||STIME.SEC>0)&&(STIME.CONFIRMED) )
            {   
                if(SENSORS.WEIGHT && SENSORS.DOOR) //Checking Door & weight during heating
                {
                    //Displaying Time
                    PICGEN_HEATER(ON);
                    PICGEN_MOTOR(ON);
                    //-----------------------------------------------
                    //Print first digit in minutes
                    LCD_GOTO_XY(2,3);
                    LCD_WriteNUMBER( STIME.MIN/10 ); 
                    //Print second digit in minutes
                    LCD_WriteNUMBER(STIME.MIN - (STIME.MIN/10)*10 );
                    //-----------------------------------------------
                    //Print first digit in seconds
                    LCD_GOTO_XY(5,3);
                    LCD_WriteNUMBER( STIME.SEC/10 ); 
                    //Print second digit in seconds
                    LCD_WriteNUMBER(STIME.SEC - (STIME.SEC/10)*10 );
                    //-----------------------------------------------

                    if( (STIME.SEC ==0) && (STIME.MIN >0) )
                    {
                        STIME.SEC = 60;
                        STIME.MIN--;
                    }
                    STIME.SEC--;
                    
                    LCD_GOTO_XY(12,3);
                    LCD_WriteLINE("__");
                    LCD_GOTO_XY(12,3);
                    LCD_WriteNUMBER(SENSORS.TEMPERATURE);
                }
                else
                {
                    //Something Happened during heating (Door opened or weight problem)
                    
                    LCD_WriteCMD(ClearDisplay);
                    PICGEN_HEATER(OFF);
                    PICGEN_MOTOR(OFF);

                    if(!SENSORS.DOOR)
                    {
                        LCD_GOTO_XY(1,1);
                        LCD_WriteLINE("DOOR: "); 
                        LCD_WriteLINE("OPENED <<<");
                    }

                    if(!SENSORS.WEIGHT)
                    {
                        LCD_GOTO_XY(1,2);
                        LCD_WriteLINE("WEIGHT:");
                        LCD_WriteLINE("EMPTY <<<");
                    }
                    flag = 2; //Got to step 2
                } 
            }
            
            else if( (STIME.MIN==0)&&(STIME.SEC==0)&&(STIME.CONFIRMED) )
            {
                // Finished the heating process
                PICGEN_HEATER(OFF);
                PICGEN_MOTOR(OFF);
                PICGEN_LED(ON);
                PICGEN_BUZZER(ON);
                
                LCD_WriteCMD(ClearDisplay);
                LCD_GOTO_XY(3,1);
                LCD_WriteLINE("TIME UP !!");
                LCD_GOTO_XY(1,2);
                LCD_WriteLINE("To Reset Process");
                LCD_GOTO_XY(1,3);
                LCD_WriteLINE("Press  <START>");
                
                
                //SCH_TaskPAUSE( START_PRIORITY );
                //SCH_TaskPAUSE( WEIGHT_PRIORITY );
                //SCH_TaskPAUSE( DOOR_PRIORITY );
                
                //SCH_TaskRESUME(LED_PRIORITY);
                KEYPAD_BUFFER.START_FLAG=0;
                flag=4;
            }
        }
        else if(flag==4)
        {
            // If a RESET process is pressed after finishing heating
            if( KEYPAD_BUFFER.START_FLAG )
            {
                flag = 0;
                
                PICGEN_LED(OFF);
                PICGEN_BUZZER(OFF);
                
                KEYPAD_BUFFER.BUFFER=0;
                KEYPAD_BUFFER.ENTER_FLAG =0;
                KEYPAD_BUFFER.CANCELL_FLAG=0; 

                //SCH_TaskPAUSE( RCONFG_PRIORITY );
                
                GLOBAL_RESET=1;
            }
        }
    }
}
