/*
 * main.c
 *
 * Created: 5/31/2024 4:33:38 PM
 *  Author: user
 */ 

#include <xc.h>
#include "myHeader.h"
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

#define __delay_t 500

int cnt = 0, tcnt = 0;

void initADC(int ch)
{	
	ADMUX |= 1 << REFS0;	// �������� Vcc 0100 0000

	ADCSRA |= 0x07;			// Pre-scaler ���ֺ� ����
	ADCSRA |= 1 << ADEN;	// ADC Ȱ��ȭ
	ADCSRA |= 1 << ADFR;	// free-running mode ����
	ADMUX  |= (ADMUX & 0xE0) | ch;
	ADCSRA |= 1 << ADSC;	// ADC ����
}
int main(void)
{
	DDRA = 0xFF; // ���׸�Ʈ ���� �� 8���� ������� ����
	DDRB = 0x0F; // �ڸ��� ���� �� 4���� ������� ����
	SegPort(&PORTA, &PORTB);
	SegType(1);
	
	initADC(1); // 1: ch number
    while(1)
    {
		while(!(ADCSRA & (1 << ADIF))) ;
		int cnt = ADC;
		SegDisp(cnt);
    }
}