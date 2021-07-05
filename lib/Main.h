#ifndef __MAIN_H__
#define __MAIN_H__

#include "C8051F020.h"

/* GPIO definitions */
/* GPIO Pins */
#define GPIO_PIN_0              (0)
#define GPIO_PIN_1              (1)
#define GPIO_PIN_2              (2)
#define GPIO_PIN_3              (3)
#define GPIO_PIN_4              (4)
#define GPIO_PIN_5              (5)
#define GPIO_PIN_6              (6)
#define GPIO_PIN_7              (7)

/* GPIO Port Registers redefinition */
#define GPIO_PORT0_DATA         (P0)
#define GPIO_PORT0_DIRECTION    (P0MDOUT)

#define GPIO_PORT1_DATA         (P1)
#define GPIO_PORT1_DIRECTION    (P1MDOUT)

#define GPIO_PORT2_DATA         (P2)
#define GPIO_PORT2_DIRECTION    (P2MDOUT)

#define GPIO_PORT3_DATA         (P3)
#define GPIO_PORT3_DIRECTION    (P3MDOUT)

#define GPIO_PORT4_DATA         (P4)
#define GPIO_PORT4_DIRECTION    (P74OUT)

#define GPIO_PORT5_DATA         (P5)
#define GPIO_PORT5_DIRECTION    (P74OUT)

/* GPIO direction setting */
#define GPIO_OUT                (0)
#define GPIO_IN                 (1)

/* GPIO port operations */
#define GPIO_InitPort(CONTROL, DIRECTION)   ((CONTROL) = ((DIRECTION)? (~GPIO_OUT):(GPIO_OUT)))
#define GPIO_WritePort(PORT, DATA)          ((PORT) = (DATA))
#define GPIO_ReadPort(PORT)                 (PORT)

/* GPIO port pin operations */
#define GPIO_InitPortPin(CONTROL, PIN, DIRECTION)   ((CONTROL) = (CONTROL & (~(1 << PIN)))|(DIRECTION << PIN))
#define GPIO_WritePortPin(PORT, PIN, DATA)          ((PORT) = (PORT & (~(1 << PIN)))|(DATA << PIN))
#define GPIO_ReadPortPin(PORT, PIN)                 (((PORT) & (1 << PIN)) >> (PIN))
/* End of code filling */


/* Interrupts */
#define UC_SET_ALL_Int_STATE(x) (EA = x)

/* External Interrupt 0*/
// #define EX0_SET_INT_STATE(x)
// #define EX0_SET_STATE(x)

/* Timer 0*/
#define TIMER0_SET_INT_STATE(x) (ET0 = x)
#define TIMER0_SET_STATE(x) (TR0 = x)
#define TIMER0_SET_MODE(x) 	GPIO_WritePortPin(TMOD, 0, (x&0x1));\
                            GPIO_WritePortPin(TMOD, 1, (x&0x2)>>1);
#define TIMER0_SELECT_CLOCK_SOURCE(y)	GPIO_WritePortPin(CKCON, 3, y);
#define TIMER0_CHECK_FLAG() (TF0)
#define TIMER0_CLEAR_FLAG() (TF0=0)
#define TIMER0_SELECT_Event_Type(x) (IT0=x)
// #define TIMER0_START()  ()
typedef enum 
{
    EVENT_LOW_LEVEL,
    EVENT_FALLING_EDGE
}tTimerEventType;
/* End of Inturrept */

/* Standard data types */
typedef unsigned int tWord;

#endif // __MAIN_H__
