/*
 * test03-intr.c
 *
 * Created: 2024-03-27 오후 12:25:35
 * Author : SYSTEM-00
 */ 
#define F_CPU 16000000L

#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

#define __delay_t 500
#define OPMODEMAX	3
#define STATE_MAX	3

uint8_t digit[] = {0x3F, 0X06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67, 0x77, 0x7c, 0x58, 0x5e, 0x79, 0x71 };
char arr[5]; // 세그먼트 이미지 정보를 담을 안전 영역
volatile int opmode = 0, state = 0;	// 최적화 금지

void seg(int sel, uint8_t c)
{
	PORTB |= 0X0F;
	PORTB &= ~(1 << (3-sel));
	PORTA = c;		// 숫자 데이터 출력
	//_delay_us(1);	// 0.01 초 간격으로 전환
}

int sm = 4;
void FND_4(char *inf) // segment Image 배열
{
	int i;
	for(i = 0;i < sm;i++)
	{
		seg(i, *(inf+i));
		_delay_ms(5);
	}
}

char* Disp(unsigned long num)  // 10진 정수 ==> 16진수 문자열 : 56506 ==> 0xDCBA
								//		   ==> 4 digit 16진수 segment 출력
{
	num %= 65536;
	int n1 = num % 16;			// A (10) : 문자가 아닌 숫자
	int n2 = (num / 16) % 16;	// B (11)
	int n3 = (num / 256 ) % 16;	// C (12)
	int n4 = (num / 4096);		// D (13)
	arr[0] = digit[n1];
	arr[1] = digit[n2];
	arr[2] = digit[n3];
	arr[3] = digit[n4];
	sm = (num > 4095) ? 4 : (num > 256) ? 3 : (num > 16) ? 2 : 1;
	FND_4(arr);
	return arr;
}

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

