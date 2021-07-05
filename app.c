#include "lib/Main.h"
#include "lib/Port.h"
#include "lib/Timer0.h"
#include "lib/Led.h"
#include "lib/SevenSegment.h"
#include "lib/PushButton.h"
#include "lib/Enums.h"
#include "lib/Common.h"

#define MAX_PERSONS     (4)

unsigned char currentFloor = GROUND;
unsigned char isMoving = false;
unsigned char numOfPersons = 0;
unsigned char floorRequests[5] = {false};
unsigned char floorBtn;
unsigned char isCalledUp = false;
unsigned char isCalledDown = false;
direction currentDirection = GOING_UP;


void floorRequest();
void startMoving();


void startMoving()
{
    if (currentDirection == GOING_UP)
    {
        isCalledUp = false;
        for(floorBtn = currentFloor; floorBtn < FOURTH_FLOOR; floorBtn++)
        {
            isCalledUp = isCalledUp || floorRequests[floorBtn];
        }
        isCalledDown = false;
        for(floorBtn = GROUND; floorBtn < currentFloor; floorBtn++)
        {
            isCalledDown = isCalledDown || floorRequests[floorBtn];
        }
        if(isCalledUp)
        {
            int i;
            Delay_MS(100);
            for(i = 0; i < 10; i++)
            {
                Delay_MS(300);
                LED_Toggle(IS_DOOR_OPENED);
            }
            LED_SetState(IS_DOOR_OPENED, LED_OFF);
            while(!floorRequests[currentFloor])
            {
                for(i = 0; i < 50; i++)
                {
                    Delay_MS(300);
                    LED_Toggle(IS_MOVING);
                }
                currentFloor++;
                SevenSegment_Write(currentFloor);
            }
            floorRequests[currentFloor] = false;
            LED_SetState(IS_MOVING, LED_OFF);
            for(i = 0; i < 10; i++)
            {
                Delay_MS(300);
                LED_Toggle(IS_DOOR_OPENED);
            }
            LED_SetState(IS_DOOR_OPENED, LED_ON);
            if(currentFloor == FOURTH_FLOOR)
            {
                currentDirection = GOING_DOWN;
            }
        }
        else if(isCalledDown)
        {
            currentDirection = GOING_DOWN;
        }
        
        // if(floorRequests[currentFloor])
        // {
        //     // Stop Elevator (Blinking Led and Motor)
        //     LED_SetState(IS_MOVING, LED_OFF);
        //     // floorRequest[currentFloor] = false
        //     floorRequests[currentFloor] = false;
        //     // Open Door (Delay 2 seconds)
        //     LED_SetState(IS_DOOR_OPENED, LED_ON);
        //     Delay_MS(100);
        //     // Delay 5 seconds
        //     Delay_MS(500);
        //     // Close Door (Delay 2 seconds)
        //     Delay_MS(100);
        //     LED_SetState(IS_DOOR_OPENED, LED_OFF);
        //     // if currentFloor == 4 (currentDirection = Going Down) and start goind down
        //     if (currentFloor == FOURTH_FLOOR)
        //     {
        //         currentDirection = GOING_DOWN;
        //     }
        //     else
        //     {
        //         // unsigned char floorBtn;
        //         isCalledUp = false;
        //         for(floorBtn = currentFloor; floorBtn < FOURTH_FLOOR; floorBtn++)
        //         {
        //             isCalledUp = isCalledUp || floorRequests[floorBtn];
        //         }
                
        //         isCalledDown = false;
        //         for(floorBtn = GROUND; floorBtn < currentFloor; floorBtn++)
        //         {
        //             isCalledDown = isCalledDown || floorRequests[floorBtn];
        //         }
        //         // Start Moving UP
        //         if(isCalledUp && numOfPersons <= MAX_PERSONS)
        //         {
        //             Delay_MS(500);
        //             currentFloor++;
        //             SevenSegment_Write(currentFloor);
        //         }
        //         else if(isCalledDown && numOfPersons <= MAX_PERSONS)
        //         {
        //             currentDirection = GOING_DOWN;
        //             Delay_MS(500);
        //             currentFloor--;
        //             SevenSegment_Write(currentFloor);
        //         }
        //     }
        //     // else
        // }
        // else
        // {
        //     // Start Elevator Movement
        //     // Delay for 5 Seconds
        //     // Update Seven Segments
        // }
    }
    else if(currentDirection == GOING_DOWN)
    {
        isCalledUp = false;
        for(floorBtn = currentFloor; floorBtn < FOURTH_FLOOR; floorBtn++)
        {
            isCalledUp = isCalledUp || floorRequests[floorBtn];
        }
        isCalledDown = false;
        for(floorBtn = GROUND; floorBtn < currentFloor; floorBtn++)
        {
            isCalledDown = isCalledDown || floorRequests[floorBtn];
        }
        if(isCalledDown)
        {
            int i, j;
            Delay_MS(100);
            for(i = 0; i < 50; i++)
            {
                for(j = 0; j < 120; j++)
                {
                    LED_Toggle(IS_DOOR_OPENED);
                }
            }
            LED_SetState(IS_DOOR_OPENED, LED_OFF);
            while(!floorRequests[currentFloor])
            {
                for(i = 0; i < 200; i++)
                {
                    for(j = 0; j < 120; j++)
                    {
                        Delay_MS(100);
                        LED_Toggle(IS_MOVING);
                    }
                }
                currentFloor--;
                SevenSegment_Write(currentFloor);
            }
            LED_SetState(IS_MOVING, LED_OFF);
            for(i = 0; i < 50; i++)
            {
                for(j = 0; j < 120; j++)
                {
                    Delay_MS(100);
                    LED_Toggle(IS_DOOR_OPENED);
                }
            }
            LED_SetState(IS_DOOR_OPENED, LED_ON);
            if(currentFloor == GROUND)
            {
                currentDirection = GOING_UP;
            }
        }
        else if(isCalledUp)
        {
            currentDirection = GOING_UP;
        }

        // if(floorRequests[currentFloor])
        // {
        //     // Stop Elevator (Blinking Led and Motor)
        //     // Open Door (Delay 2 seconds)
        //     // Delay 5 seconds
        //     // Close Door (Delay 2 seconds)
        //     // if currentFloor == 4 (currentDirection = Going Down)
        // }
    }
}

void floorRequest()
{
    PB_Update();

    // unsigned char floorBtn = GROUND;
    for(floorBtn = GROUND; floorBtn <= FOURTH_FLOOR; floorBtn++)
    {
        if(PB_GetState(floorBtn) == PB_PRESSED)
            floorRequests[floorBtn] = true;
    }
    if(!isMoving)
    {
        if(DOOR_OPENED)
        {
            if(PB_GetState(INCREASE) == PB_PRESSED)
                numOfPersons++;
            if(PB_GetState(DECREASE) == PB_PRESSED)
            {
                numOfPersons != 0? numOfPersons-- : 0;
            }

            if(numOfPersons > MAX_PERSONS)
                LED_SetState(TOO_MANY_PEOPLE, LED_ON);
            else
                LED_SetState(TOO_MANY_PEOPLE, LED_OFF);
        }
    }
}

void TIMER0_Update() interrupt 1
{
    static unsigned char count = 0;

    TIMER0_CLEAR_FLAG();
    
    count++;
    if (count % 20 == 0)
    {
        // LED_Toggle(ALARM_LED_PIN);
        floorRequest();
        count = 0;
    }
}

void main()
{
    // diable the watch dog
    WDTCN = 0x0DE;
    WDTCN = 0x0AD;

    OSCICN = 0x014; // 2MH clock

    // config cross bar
    XBR0 = 0x00;
    XBR1 = 0x00;
    XBR2 = 0x040; // Cross bar enabled , weak Pull-up enabled

    PB_Init(F0_BTN, PB_RELEASED);
    PB_Init(F1_BTN, PB_RELEASED);
    PB_Init(F2_BTN, PB_RELEASED);
    PB_Init(F3_BTN, PB_RELEASED);
    PB_Init(F4_BTN, PB_RELEASED);
    PB_Init(UP, PB_RELEASED);
    PB_Init(DOWN, PB_RELEASED);
    PB_Init(FORCE, PB_RELEASED);
    PB_Init(INCREASE, PB_RELEASED);
    PB_Init(DECREASE, PB_RELEASED);

    LED_Init(IS_MOVING, LED_OFF);
    LED_Init(IS_DOOR_OPENED, LED_ON);
    LED_Init(TOO_MANY_PEOPLE, LED_OFF);

    SevenSegment_Init();

    TIMER0_Init();
    TIMER0_Start();

    while (1)
    {
        startMoving();
    }
}