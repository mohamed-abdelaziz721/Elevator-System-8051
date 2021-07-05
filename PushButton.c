#include "lib/PushButton.h"
#include "lib/Port.h"


#define NUMBER_OF_SAMPLE    (2)
#define NUMBER_OF_PUSH_BUTTONS  (10)

#define PB_PRESSED_VOLTAGE  (0)
#define PB_RELEASED_VOLTAGE  (1)


typedef struct
{
    unsigned char samples[NUMBER_OF_SAMPLE];
    tPB_State state;
}tPB_Info;

static tPB_Info pb_info[NUMBER_OF_PUSH_BUTTONS];


void PB_Init(tPB pb, tPB_State initial_state)
{
    /* Initialize hw pins */
    switch(pb)
    {
        case F0_BTN:
            GPIO_InitPortPin(F0_BTN_PORT_CR, F0_BTN_PIN, GPIO_IN);
            break;
        case F1_BTN:
            GPIO_InitPortPin(F1_BTN_PORT_CR, F1_BTN_PIN, GPIO_IN);
            break;
        case F2_BTN:
            GPIO_InitPortPin(F2_BTN_PORT_CR, F2_BTN_PIN, GPIO_IN);
            break;
        case F3_BTN:
            GPIO_InitPortPin(F3_BTN_PORT_CR, F3_BTN_PIN, GPIO_IN);
            break;
        case F4_BTN:
            GPIO_InitPortPin(F4_BTN_PORT_CR, F4_BTN_PIN, GPIO_IN);
            break;
        case UP:
            GPIO_InitPortPin(UP_BTN_PORT_CR, UP_BTN_PIN, GPIO_IN);
            break;
        case DOWN:
            GPIO_InitPortPin(DOWN_BTN_PORT_CR, DOWN_BTN_PIN, GPIO_IN);
            break;
        case FORCE:
            GPIO_InitPortPin(FORCE_OPEN_BTN_PORT_CR, FORCE_OPEN_BTN_PIN, GPIO_IN);
        case INCREASE:
            GPIO_InitPortPin(INCREASE_BTN_PORT_CR, INCREASE_BTN_PIN, GPIO_IN);
        case DECREASE:
            GPIO_InitPortPin(DECREASE_BTN_PORT_CR, DECREASE_BTN_PIN, GPIO_IN);
            break;
        default:
            /* Should not be here */
            break;
    }

    /* Initialize state */
    pb_info[pb].state = initial_state;

    /* Initialize samples */
    switch (initial_state)
    {
    case PB_RELEASED:
    case PB_PRE_RELEASED:
        pb_info[pb].samples[0] = PB_RELEASED_VOLTAGE;
        pb_info[pb].samples[1] = PB_RELEASED_VOLTAGE;
        break;
    case PB_PRESSED:
    case PB_PRE_PRESSED:
        pb_info[pb].samples[0] = PB_PRESSED_VOLTAGE;
        pb_info[pb].samples[1] = PB_PRESSED_VOLTAGE;
        break;
    }
}

void PB_Update(void)
{
    tPB current_button = F0_BTN;
    for (current_button = F0_BTN; current_button <= FORCE; current_button++)
    {
        /* Update samples */
        pb_info[current_button].samples[0] = pb_info[current_button].samples[1];

        switch(current_button)
        {
        case F0_BTN:
            pb_info[current_button].samples[1] = GPIO_ReadPortPin(F0_BTN_PORT_DR, F0_BTN_PIN);
            break;
        case F1_BTN:
            pb_info[current_button].samples[1] = GPIO_ReadPortPin(F1_BTN_PORT_DR, F1_BTN_PIN);
            break;
        case F2_BTN:
            pb_info[current_button].samples[1] = GPIO_ReadPortPin(F2_BTN_PORT_DR, F2_BTN_PIN);
            break;
        case F3_BTN:
            pb_info[current_button].samples[1] = GPIO_ReadPortPin(F3_BTN_PORT_DR, F3_BTN_PIN);
            break;
        case F4_BTN:
            pb_info[current_button].samples[1] = GPIO_ReadPortPin(F4_BTN_PORT_DR, F4_BTN_PIN);
            break;
        case UP:
            pb_info[current_button].samples[1] = GPIO_ReadPortPin(UP_BTN_PORT_DR, UP_BTN_PIN);
            break;
        case DOWN:
            pb_info[current_button].samples[1] = GPIO_ReadPortPin(DOWN_BTN_PORT_DR, DOWN_BTN_PIN);
            break;
        case FORCE:
            pb_info[current_button].samples[1] = GPIO_ReadPortPin(FORCE_OPEN_BTN_PORT_DR, FORCE_OPEN_BTN_PIN);
            break;
        case INCREASE:
            pb_info[current_button].samples[1] = GPIO_ReadPortPin(INCREASE_BTN_PORT_DR, INCREASE_BTN_PIN);
            break;
        case DECREASE:
            pb_info[current_button].samples[1] = GPIO_ReadPortPin(DECREASE_BTN_PORT_DR, DECREASE_BTN_PIN);
            break;
        default:
            /* Should not be here */
            break;
        }

        /* Update state */
        switch(pb_info[current_button].state)
        {
        case PB_RELEASED:
            if((pb_info[current_button].samples[0] == PB_PRESSED_VOLTAGE) &&
               (pb_info[current_button].samples[1] == PB_PRESSED_VOLTAGE))
            {
                pb_info[current_button].state = PB_PRE_PRESSED;
            }
            break;
        case PB_PRE_PRESSED:
            if(pb_info[current_button].samples[1] == PB_PRESSED_VOLTAGE)
            {
                pb_info[current_button].state = PB_PRESSED;
            }
            break;
        case PB_PRESSED:
            if((pb_info[current_button].samples[0] == PB_RELEASED_VOLTAGE) &&
               (pb_info[current_button].samples[1] == PB_RELEASED_VOLTAGE))
            {
                pb_info[current_button].state = PB_PRE_RELEASED;
            }
            break;
        case PB_PRE_RELEASED:
            if(pb_info[current_button].samples[1] == PB_RELEASED_VOLTAGE)
            {
                pb_info[current_button].state = PB_RELEASED;
            }
            break;
        default:
            /* Should not be here */
            break;
        }

    }
}

tPB_State PB_GetState(tPB pb)
{
    tPB_State ret = PB_RELEASED;

    ret = pb_info[pb].state;

    return ret;
}