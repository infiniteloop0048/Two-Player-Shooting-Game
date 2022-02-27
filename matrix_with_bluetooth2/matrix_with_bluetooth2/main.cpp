/*
 * LedShape.c
 *
 * Created: 7/9/2019 11:32:21 AM
 * Author : Ramiz
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 1000000

volatile int state = 0;

int pattern[8][8] = {{0,0,0,0,0,0,0,0},
{0,0,1,1,1,1,0,0},
{0,0,1,0,0,0,0,0},
{0,0,1,0,0,0,0,0},
{0,0,1,1,1,1,0,0},
{0,0,0,0,0,1,0,0},
{0,0,0,0,0,1,0,0},
{0,0,1,1,1,1,0,0}
};

ISR(INT1_vect){
	state = 1 - state;
}


int main(void)
{
	/* Replace with your application code */
	
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0xFF;
	
	/*GICR = (1 << INT1);
	MCUCR = MCUCR & 0b11110011;
	MCUCR = MCUCR | 0b00001000;
	sei();
	*/
	int on = 1;
	while (1)
	{
		
		if(PORTC&0b10000001){
			int temp;
			
			
			for (int i = 0; i < 8; i++) {
				temp = pattern[i][7];
				for (int j = 6; j >= 0; j-- ) {
					pattern[i][j + 1] = pattern[i][j];
				}
				pattern[i][0] = temp;
			}
			PORTC=PORTC&0b01111111;
			
		}
		
		on = 1 - on;
		if (state == 1) {
			// right shift
			int temp;
			
			for (int i = 0; i < 8; i++) {
				temp = pattern[i][7];
				for (int j = 6; j >= 0; j-- ) {
					pattern[i][j + 1] = pattern[i][j];
				}
				pattern[i][0] = temp;
			}
		}
		for (int k = 0; k < 1000; k++){
			for(int i=0;i<8;i++){
				for(int j=0;j<8;j++){
					if(pattern[i][j] == 1 && (on == 1 || state == 1)){
						char a = (1 << i);
						char b = (1 << j);
						PORTA = a;
						PORTB = ~b;
						}else{
						PORTA = 0;
						PORTB = 0xFF;
					}
				}
			}
		}
	}
}


