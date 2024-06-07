/*
 * test02-7seg.c
 *
 * Created: 2024-03-21 오후 3:34:28
 * Author : SYSTEM-00
 */ 
#define F_CPU 16000000L

#include <avr/io.h>
#include <avr/delay.h>

#define __delay_t 500

uint8_t digit[] = {0x3F, 0X06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67, 0x77, 0x7c, 0x58, 0x5e, 0x79, 0x71 };
char arr[5]; // 세그먼트 이미지 정보를 담을 안전 영역

void TogglePinA(int n, double dl)  // n : n번째 비트,  dl : delay in mili-second
{
	char b = 1 << n;
	PORTD |= b;  // PortA의 n번째 비트를 HIGH로 출력
	_delay_ms( __delay_t);
	PORTD &= ~b; // PortA의 n번째 비트를 LOW로 출력
	_delay_ms( __delay_t);
}

void LED(char *p,  int n)  // p : PORTx의 포인터, n : n 번째 비트
{
	char b = 1 << n;
	*p |= b;  // PortA의 n번째 비트를 HIGH로 출력
	_delay_ms( __delay_t);
	*p &= ~b; // PortA의 n번째 비트를 LOW로 출력
	_delay_ms( __delay_t);
}

void seg(int sel, uint8_t c)
{	
	PORTB |= 0X0F;
//	PORTB &= ~(1 << (3-sel));
	PORTB |= 1 << (3-sel);
	PORTA = c;		// 숫자 데이터 출력
	_delay_us(1);	// 0.01 초 간격으로 전환
}

void FND_4(char *inf) // segment Image 배열
{
	for(int i = 0;i < 4;i++)
	{		
		seg(i, *(inf+i));
	}
}

char* Trans(unsigned long num)  // 10진 정수 ==> 16진수 문자열 : 56506 ==> 0xDCBA
						//		   ==> 16진수 segment Image 배열		  		  
{	
	int n1 = num % 16;			// A (10) : 문자가 아닌 숫자
	int n2 = (num / 16) % 16;	// B (11)
	int n3 = (num / 256 ) % 16;	// C (12)
	int n4 = (num / 4096);		// D (13)
	arr[0] = digit[n1];
	arr[1] = digit[n2];
	arr[2] = digit[n3];
	arr[3] = digit[n4];
	
	//FND_4(arr);
	return arr;
}
int main(void)
{
	unsigned long j = 0;
	//int i, j = 0;
	//DDRD = 0x07;
	DDRA = 0xFF; // 세그먼트 제어 핀 8개를 출력으로 설정
	DDRB = 0x0F; // 자릿수 선택 핀 4개를 출력으로 설정
	while(1)
	{
		//TogglePinA(2,__delay_t); // PortA의 0번째 비트를 점멸
		//LED(&PORTD, 1); // PortD의 0번째 비트를 점멸
		FND_4(Trans(j++));
		_delay_us(10);
		//for(i = 0; i < 4; i++)
		//{
			//// 해당 자리에만 O(GND)을 출력하고 나머지에는 1을 출력하여 자리 선택
			//PORTB |= 0X0F;
			//PORTB &= ~(1 << (3-i));
			//for(j = 0; j < 16; j++)
			//{
				//PORTA = digit[j];			// 숫자 데이터 출력
				//_delay_ms(100);             // 0.5 초 간격으로 전환
			//}
		//}
	}
	return 0;
}
