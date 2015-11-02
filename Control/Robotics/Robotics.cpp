/*
 * Robotics.cpp
 *
 * Created: 9/20/2015 11:09:14 PM
 *  Author: Eduardo
 */ 
#include "Arduino.h"
#include "Wire.h"
#include "Headers/usart.h"
#include <HardwareSerial.cpp>
#include <avr/io.h>
#include <util/delay.h>
//#include "Headers/Wheel.h"
#include "Headers/_cplusplus.h"
//#include "Headers/Robot.h"


  int x = 9999;
  byte xH, xL;
int main(void)
{
	
	USART_Send_string("1\n");
	Serial.begin(9600);
	USART_Init(MYUBRR);
	  //Serial.println(x);
	Serial.println("Inicianco configuracion");
	Wire.beginTransmission(0x3C);
	USART_Send_string("2\n");
	Wire.write(0x02);
	
	USART_Send_string("3\n");
	Wire.write(0x00);
	Wire.endTransmission();
	USART_Send_string("4\n");
	USART_Send_string("5\n");
	Wire.beginTransmission(0x3C);
	Wire.write(0x03);
	Wire.endTransmission();
	//Robot *r = new Robot();
	//Wheel a(TIMER_1,CHANNEL_A,30,31);
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
	//int speed = 30;
	//bool up = true;
	//Serial.println("Iniciando loop");
	USART_Send_string("Iniciando Loop");
    while(1)
    {
		  x=0;
		  Wire.requestFrom(0x3D, 2);
		  xH = Wire.read();
		  //Serial.println(xH);
		  xL = Wire.read();
		  //Serial.println(xL);
		  x = (xH<<8)|xL;
		  USART_Send_int(x);
		  //Serial.println(x);
		_delay_ms(100);/*
		r->Move(FORWARD,100);
		_delay_ms(2000);
		r->Stop();
		_delay_ms(500);
		r->Move(BACKWARD,100);
		_delay_ms(2000);
		r->Stop();
		_delay_ms(500);
		r->Move(LEFT,100);
		_delay_ms(2000);
		r->Stop();
		_delay_ms(500);
		r->Move(RIGHT,100);
		_delay_ms(2000);
		r->Stop();
		_delay_ms(500);
		//r->StateMachine->Update();
		
		//_delay_ms(10000);
		//a.Backward(50);
		//_delay_ms(10000);
		//a.Stop();
		//_delay_ms(2000);
		//dutyCyle++;
		//if(dutyCyle > 100){
			//_delay_ms(1000);
			//dutyCyle = 0;
		//}
		//a.SetDutyCycle(dutyCyle);
		//_delay_ms(100);
        //TODO:: Please write your application code */
    }
}