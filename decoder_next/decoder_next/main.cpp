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

int pattern[8][16] ={
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,1,1,0,0,1,1,1,1,1},
{1,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1},
{1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

ISR(INT1_vect){
	state = 1 - state;
}


int main(void)
{
	/* Replace with your application code */
	
	DDRA = 0xFF;
	DDRB = 0xFF;
	
	int c = 0;
	
	while (1)
	{
		
		
			// right shift
			int temp;
			
			for (int i = 0; i < 8; i++) {
				temp = pattern[i][7];
				for (int j = 14; j >= 0; j-- ) {
					pattern[i][j + 1] = pattern[i][j];
				}
				pattern[i][0] = temp;
			}
			for(int k=0;k<1000;k++)
			for(int i=0;i<8;i++){
				
				PORTA = 1<<i;
				for(int j=0;j<16;j++){
					if(pattern[i][j]==1){
					PORTB = j;
					}
				}
			}
			//_delay_ms(1000);
		
		/*for(int k=0;k<1000;k++)
			for(int i=0;i<8;i++){
				for(int j=0;j<16;j++){
					if(pattern[i][j] == 1){
						char a = (1 << i);
						char b = j;
						PORTA = a;
						PORTB = b;	
						}
					}
				
			}*/
		}
	}



