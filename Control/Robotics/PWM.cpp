/*
* PWM.cpp
*
* Created: 9/20/2015 11:58:15 PM
* Author: Eduardo
*/


#include "PWM.h"
#include <avr/io.h>

PWM::PWM() {

}
// default constructor
PWM::PWM(Timer timer, Channel channel, int frequency, int dutyCycle, int prescaler) :Frequency(frequency), DutyCycle(dutyCycle), Prescaler(prescaler)
{
	//	Get the address for the registers of the selected Timer and Channel
	//	We need to get the address for the registers:
	//	TCCR:	Timer/Counter Control Register
	//	DDR:	Data Direction Register ( We need to set the pin as OUTPUT )
	//	WGM:	Waveform Generation Mode
	//	ICR:	Input Control Register
	//	COM:	Compare Output Mode

	switch (timer) {
		case TIMER_1:
			ControlRegA = &TCCR1A;
			ControlRegB = &TCCR1B;
			DDR = &DDRB;
			WGM0 = WGM10;
			WGM1 = WGM11;
			WGM2 = WGM12;
			WGM3 = WGM13;
			ICR = &ICR1;

			// Set the channel to be used
			switch (channel)
			{
			case CHANNEL_A:
				OCR = &OCR1A;
				COM0 = COM1A0;
				COM1 = COM1A1;
				OutBit = PB5;
				break;
			case CHANNEL_B:
				OCR = &OCR1B;
				COM0 = COM1B0;
				COM1 = COM1B1;
				OutBit = PB6;
				break;
			case CHANNEL_C:
				OCR = &OCR1C;
				COM0 = COM1C0;
				COM1 = COM1C1;
				OutBit = PB7;
				break;
			}

			break;
	case TIMER_3:
		ControlRegA = &TCCR3A;
		ControlRegB = &TCCR3B;
		DDR = &DDRE;
		WGM0 = WGM30;
		WGM1 = WGM31;
		WGM2 = WGM32;
		WGM3 = WGM33;
		ICR = &ICR3;
		// Set the channel to be used
		switch (channel)
		{
			case CHANNEL_A:
				OCR = &OCR3A;
				COM0 = COM3A0;
				COM1 = COM3A1;
				OutBit = PE3;
				break;
			case CHANNEL_B:
				OCR = &OCR3B;
				COM0 = COM3B0;
				COM1 = COM3B1;
				OutBit = PE4;
				break;
			case CHANNEL_C:
				OCR = &OCR3C;
				COM0 = COM3C0;
				COM1 = COM3C1;
				OutBit = PE5;
				break;
		}
		break;
	case TIMER_4:
		ControlRegA = &TCCR4A;
		ControlRegB = &TCCR4B;
		DDR = &PORTH;
		WGM0 = WGM40;
		WGM1 = WGM41;
		WGM2 = WGM42;
		WGM3 = WGM43;
		ICR = &ICR4;
		// Set the channel to be used
		switch (channel)
		{
			case CHANNEL_A:
				OCR = &OCR4A;
				COM0 = COM4A0;
				COM1 = COM4A1;
				OutBit = PH3;
				break;
			case CHANNEL_B:
				OCR = &OCR4B;
				COM0 = COM4B0;
				COM1 = COM4B1;
				OutBit = PH4;
				break;
			case CHANNEL_C:
				OCR = &OCR4C;
				COM0 = COM4C0;
				COM1 = COM4C1;
				OutBit = PH5;
				break;
		}
		break;
	case TIMER_5:
		ControlRegA = &TCCR5A;
		ControlRegB = &TCCR5B;
		DDR = &PORTL;
		WGM0 = WGM50;
		WGM1 = WGM51;
		WGM2 = WGM52;
		WGM3 = WGM53;
		ICR = &ICR5;
		// Set the channel to be used
		switch (channel)
		{
		case CHANNEL_A:
			OCR = &OCR5A;
			COM0 = COM5A0;
			COM1 = COM5A1;
			OutBit = PL3;
			break;
		case CHANNEL_B:
			OCR = &OCR5B;
			COM0 = COM5B0;
			COM1 = COM5B1;
			OutBit = PL4;
			break;
		case CHANNEL_C:
			OCR = &OCR5C;
			COM0 = COM5C0;
			COM1 = COM5C1;
			OutBit = PL5;
			break;
		}
		break;
	}
	TimerSetup();
	SetFrequency(frequency);
	SetDutyCycle(dutyCycle);
} //PWM

// Sets the values of the control register for the Timer
void PWM::TimerSetup()
{
	uint8_t prescaleMode = 0;
	switch (Prescaler) {
	case 0:
		prescaleMode = 0;
		break;
	case 1:
		prescaleMode = 1;
		break;
	case 8:
		prescaleMode = 2;
		break;
	case 64:
		prescaleMode = 3;
		break;
	case 256:
		prescaleMode = 4;
		break;
	case 1024:
		prescaleMode = 5;
		break;
	default:
		prescaleMode = 1;
	}

	//	Set WGM = 14 (Fast PWM)
	//	Set Output to Inverting Mode COM = 2
	//	Set the Timer pin to OUTPUT
	noInterrupts();
	*ControlRegA |= _BV(WGM1) | _BV(COM1);
	*ControlRegA &= 0xFE;
	*ControlRegB |= _BV(WGM3) | _BV(WGM2) | prescaleMode;
	*DDR |= _BV(OutBit);
	Serial.println("test");
	Serial.println(*ControlRegA, HEX);
	interrupts();
}

void PWM::SetFrequency(int frequency) {
	int f = F_CPU / (Prescaler * frequency) - 1;
	*ICR = (uint16_t)f;
}

void PWM::SetDutyCycle(float dutyCycle) {
	if (dutyCycle < 0)
	{
		DutyCycle = 0;
		*OCR = 0;
		return;
	}
	else if (dutyCycle > 100)
		DutyCycle = 100;
	else
		DutyCycle = dutyCycle;
	//Serial.print("DutyCycle: ");
	//Serial.print(dutyCycle);
	//Serial.print(" ICR: ");
	//uint16_t t = *ICR;
	//Serial.println(DutyCycle);
	//Serial.println(*ICR);
	//Serial.print(" OCR: ");
	//Serial.print(*OCR, DEC);
	//Serial.print(" new OCR:");
	//Serial.println(*OCR, DEC);
	//Serial.println(*ICR, DEC);
	//Serial.println(TCCR1A);
	//Serial.println(*ControlRegB, DEC);
	uint16_t result = (uint16_t)((DutyCycle / 100.0) * (*ICR));
	//Serial.println(result);
	*OCR = result;
	//Serial.println(*OCR, DEC);
}
