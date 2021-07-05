#include "lib/Main.h"
#include "lib/Port.h"
#include "lib/Led.h"


void LED_Init(tLED led, tLED_State state)
{
    /* Add your code here! */
    /* Configure led pins as output */
    switch (led)
    {
        case IS_MOVING:
            GPIO_InitPortPin(MOVING_LED_PORT_CR, MOVING_LED_PIN, GPIO_OUT);
            break;
        case IS_DOOR_OPENED:
           GPIO_InitPortPin(DOOR_OPEN_LED_PORT_CR, DOOR_OPEN_LED_PIN, GPIO_OUT);
            break;
        case TOO_MANY_PEOPLE:
            GPIO_InitPortPin(ALARM_LED_PORT_CR, ALARM_LED_PIN, GPIO_OUT);
            break;
        default:
            /* Should not come here */
            break;
    }
    /* Set led state */
    LED_SetState(led, state);
    /* End of your code */

}

void LED_Toggle(tLED led)
{
    /* Add your code here! */
    /* Toggle led */
    if (LED_GetState(led) == LED_ON)
    {
        LED_SetState(led, LED_OFF);
    } else
    {
        LED_SetState(led, LED_ON);
    }
}


void LED_SetState(tLED led, tLED_State state)
{
    /* Add your code here! */
    /* Set led state */
    switch (led)
    {
        case IS_MOVING:
            GPIO_WritePortPin(MOVING_LED_PORT_DR, MOVING_LED_PIN, state);
            break;
        case IS_DOOR_OPENED:
            GPIO_WritePortPin(DOOR_OPEN_LED_PORT_DR, DOOR_OPEN_LED_PIN, state);
            break;
        case TOO_MANY_PEOPLE:
            GPIO_WritePortPin(ALARM_LED_PORT_DR, ALARM_LED_PIN, state);
            break;
        default:
            /* Should not come here */
            break;
    }
    /* End of your code */
}

tLED_State LED_GetState(tLED led)
{
    tLED_State ret = LED_OFF;

    /* Add your code here! */
    /* Set led state */
    switch (led)
    {
        case IS_MOVING:
            ret = GPIO_ReadPortPin(MOVING_LED_PORT_DR, MOVING_LED_PIN);
            break;
        case IS_DOOR_OPENED:
            ret = GPIO_ReadPortPin(DOOR_OPEN_LED_PORT_DR, DOOR_OPEN_LED_PIN);
            break;
        case TOO_MANY_PEOPLE:
            ret = GPIO_ReadPortPin(ALARM_LED_PORT_DR, ALARM_LED_PIN);
            break;
        default:
            /* Should not come here */
            break;
    }
    /* End of your code */
    return ret;
}
