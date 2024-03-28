/*
 * CFile1.c
 *
 * Created: 2024-03-28 오전 10:45:29
 *  Author: SYSTEM-00
 */ 
#include "myHeader.h"
//#define F_CPU 16000000L

#include <avr/io.h>
#include <avr/delay.h>

uint8_t digit[] = {0x3F, 0X06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67, 0x77, 0x7c, 0x58, 0x5e, 0x79, 0x71 };
char arr[5]; // 세그먼트 이미지 정보를 담을 안전 영역
char *PA = &PORTB, *PB = &PORTC;

void SegPort(char *p1, char *p2)
{	
	PA = p1; PB = p2;
}
void seg(int sel, uint8_t c)
{
	*PB |= 0X0F;
	*PB &= ~(1 << (3-sel));
	*PA = c;		// 숫자 데이터 출력
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

char* SegDisp(unsigned long num)  // 10진 정수 ==> 16진수 문자열 : 56506 ==> 0xDCBA
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
