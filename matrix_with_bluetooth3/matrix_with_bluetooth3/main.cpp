/*
 * LedShape.c
 *
 * Created: 7/9/2019 11:32:21 AM
 * Author : Ramiz
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define F_CPU 1000000

volatile int state = 0;

int pattern[8][8] = {{0,0,0,0,0,0,0,0},
{0,0,0,1,0,0,0,0},
{0,0,0,1,0,0,0,0},
{0,0,0,1,0,0,0,0},
{0,0,1,1,1,0,0,0},
{0,0,0,1,0,0,0,0},
{0,0,0,1,0,0,0,0},
{0,0,0,1,0,0,0,0}
};
/*
ISR(INT1_vect){
	state = 1 - state;
}
*/

int main(void)
{
	/* Replace with your application code */
	
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0x00;
	
	/*GICR = (1 << INT1);
	MCUCR = MCUCR & 0b11110011;
	MCUCR = MCUCR | 0b00001000;
	sei();
	*/
	int on = 1;
	while (1)
	{
		//_delay_ms(1000);
		
		if(PINC&0b00000001){
			int temp;
			//_delay_ms(1000);
			if(PINC&0b01000000){
			for (int i = 0; i < 8; i++) {
				temp = pattern[i][7];
				for (int j = 6; j >= 0; j-- ) {
					pattern[i][j + 1] = pattern[i][j];
				}
				pattern[i][0] = temp;
			}
			}
			//PORTC=PORTC&0b01111111;
			
		}
		
		else if(PINC&0b00000010){
			int temp;
			if(PINC&0b01000000){
			for (int i = 0; i < 8; i++) {
				temp = pattern[i][0];
				for (int j = 0; j < 7; j++ ) {
					pattern[i][j] = pattern[i][j+1];
				}
				pattern[i][7] = temp;
			}
			}
			//PORTC=PORTC&0b01111111;
			
		}
		
		else if(PINC&0b01000100){
			int temp;
			
			for (int i = 0; i < 8; i++) {
				temp = pattern[i][0];
				for (int j = 0; j < 7; j++ ) {
					pattern[i][j] = pattern[i][j+1];
				}
				pattern[i][7] = temp;
			}
			//PORTC=PORTC&0b01111111;
			
		}
		
		on = 1 - on;
		
		for (int k = 0; k < 1; k++){
			for(int i=0;i<8;i++){
				for(int j=0;j<8;j++){
					if(pattern[i][j] == 1 ){
						char a = (1 << i);
						char b = (1 << j);
						PORTA = a;
						PORTB = ~b;
						}
					}
				}
			}
			//_delay_ms(100);
		}
	}



