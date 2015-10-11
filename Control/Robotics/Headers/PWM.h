/* 
* PWM.h
*
* Created: 9/20/2015 11:58:15 PM
* Author: Eduardo
*/


#ifndef __PWM_H__
#define __PWM_H__

#include <avr/io.h>
// Enums
typedef enum Timer{
	TIMER_1,
	TIMER_3,
	TIMER_4,
	TIMER_5
}timer;
typedef enum Channel{
	CHANNEL_A,
	CHANNEL_B,
	CHANNEL_C
}chanel;


class PWM
{
//variables
public:


	// Operation variables
	int Frequency;
	int DutyCycle;
	int Prescaler;
	
	// Control variables
	volatile uint8_t *ControlRegA;
	volatile uint8_t *ControlRegB;
	volatile uint8_t *DDR;
	volatile uint16_t *ICR;
	volatile uint16_t *OCR;
	uint8_t OutBit;
	uint8_t COM0;
	uint8_t COM1;
	uint8_t WGM0;
	uint8_t WGM1;
	uint8_t WGM2;
	uint8_t WGM3;

private:
	void TimerSetup();

//functions
public:
	PWM();
	PWM(Timer timer, Channel channel, int frequency, int dutyCycle, int Prescaler);
	void SetDutyCycle(int dutyCycle);
	void SetFrequency(int frequency);
	void Start();
	void Stop();
protected:

}; //PWM

#endif //__PWM_H__
