/*
 * test03-intr.c
 *
 * Created: 2024-03-27 오후 12:25:35
 * Author : SYSTEM-00
 */ 

#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

#define __delay_t 500
#define OPMODEMAX	3
#define STATE_MAX	3

extern char* Disp(unsigned long num);

volatile int opmode = 0, state = 0;	// 최적화 금지

int main(void)
{
    /* Replace with your application code */
	// 7-Segment 사용 : 4 Module - C type
	//    Pin assign :  PAx - Segment img,  PBx - module sel
	// Interrupt 사용 : INT4 ~ INT6 (Ext Int)
	//    Pin assign :   PE4 ~ PE6
	DDRA = 0xFF; // 세그먼트 제어 핀 8개를 출력으로 설정
	DDRB = 0x0F; // 자릿수 선택 핀 4개를 출력으로 설정

	//  인터럽트 설정
	EIMSK = 0x70;	// 0111 0000b
	EICRB = 0x2a;	// 0010 1010b
	SREG |= 0x80;	// status Register - 인터럽트 허용
	sei();			// set interrupt - 인터럽트 시작
	
	long t = 0;
    while (1) 
    {
		switch(opmode)
		{
			case 0:	// reset & wait
				t = 0; break;
			case 1: // counter start
				t++; break;
			case 2: // count stop
				break;
			default: break;			
		}
		Disp(t);
		_delay_ms(15);
		Disp(t);
		_delay_ms(15);
		Disp(t);
		_delay_ms(15);
		Disp(t);
		_delay_ms(13);
    }
}
ISR(INT4_vect) // INT4 인터럽트 처리 루틴 : sw1
{	
	opmode++;
	if(opmode >= OPMODEMAX) opmode = 0;
}
ISR(INT5_vect) // INT5 인터럽트 처리 루틴 : sw2
{	
	state++;
	if(state >= STATE_MAX) state = 0;
}
ISR(INT6_vect) // INT6 인터럽트 처리 루틴 : sw3
{	
	
}

