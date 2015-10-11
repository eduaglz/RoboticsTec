/*
 * Robotics.cpp
 *
 * Created: 9/20/2015 11:09:14 PM
 *  Author: Eduardo
 */ 
#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include "Headers/Wheel.h"
#include "Headers/_cplusplus.h"
#include "Headers/Robot.h"



int main(void)
{
	Robot *r = new Robot();
	Wheel a(TIMER_1,CHANNEL_A,30,31);
	//int dutyCyle = 10;
	//PWM a(TIMER_1, CHANNEL_A, 50, 10,8);
	//PWM b(TIMER_1, CHANNEL_B, 50, 20,8);
	//PWM c(TIMER_1, CHANNEL_C, 50, 30,8);
	//PWM d(TIMER_3, CHANNEL_A, 50, 40,8);
	//PWM e(TIMER_3, CHANNEL_B, 50, 50,8);
	//PWM f(TIMER_3, CHANNEL_C, 50, 60,8);
	
	//uint16_t TOP = (clk_io / ( 64 * 50 )) - 1;
	//uint16_t dutyCyle = (50.0 / 100.0) * TOP;
	//TCCR1A |= _BV(COM1A1) | _BV(COM1A0) | _BV(WGM11);
	//TCCR1B |= _BV(WGM13) | _BV(WGM12) | 3;
	//DDRB |= _BV(PB5);
	//ICR1 = TOP;
	//OCR1A = dutyCyle;
	//uint16_t x = OCR3A;
	//uint16_t y = OCR1A;
	//bool t = OCR1A == OCR3A;
	//bool t2 = TCCR1A == TCCR3A;
	//bool t3 = TCCR2B == TCCR3B;
	//a.Forward(90);
    while(1)
    {
		r->StateMachine->Update();
		//a.Forward(50);
		//_delay_ms(2000);
		//a.Backward(50);
		//_delay_ms(2000);
		//a.Stop();
		//_delay_ms(2000);
		//dutyCyle++;
		//if(dutyCyle > 100){
			//_delay_ms(1000);
			//dutyCyle = 0;
		//}
		//a.SetDutyCycle(dutyCyle);
		//_delay_ms(100);
        //TODO:: Please write your application code 
    }
}