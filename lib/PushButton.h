#ifndef __PB_H__
#define __PB_H__

typedef enum
{
    F0_BTN,
    F1_BTN,
    F2_BTN,
    F3_BTN,
    F4_BTN,
    UP,
    DOWN,
    FORCE,
    INCREASE,
    DECREASE
}tPB;

typedef enum
{
    PB_RELEASED,
    PB_PRE_PRESSED,
    PB_PRESSED,
    PB_PRE_RELEASED
}tPB_State;


void PB_Init(tPB pb, tPB_State initial_state);
void PB_Update(void);
tPB_State PB_GetState(tPB pb);
#endif // __PB_H__
