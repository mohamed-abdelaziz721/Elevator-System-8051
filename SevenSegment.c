#include "lib/Main.h"
#include "lib/Port.h"
#include "lib/Common.h"
#include "lib/SevenSegment.h"

char numbers[] = {0x71, 0x06, 0x5B, 0x4F, 0x66};
// char numbers[] = {0x71, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
// char numbers[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void SevenSegment_Init(void)
{
    GPIO_InitPort(SEVEN_SEGMENT_CR, GPIO_OUT);
    GPIO_WritePort(SEVEN_SEGMENT_DR, numbers[0]);
}

void SevenSegment_Write(unsigned char number_index)
{
    GPIO_WritePort(SEVEN_SEGMENT_DR, numbers[number_index]);
}