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
{0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0},
{0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0},
{0,1,1,1,2,0,0,0,0,0,0,0,0,1,1,1},
{0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0},
{0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0},
{0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

ISR(INT1_vect){
	state = 1 - state;
}


int main(void)
{
	/* Replace with your application code */
	
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRD = 0b00000000;
	
	int c = 0;
	
	while (1)
	{
		
		
			// right shift
			int temp;
			c++;
			c=c%400;
			int f=0;
			
			//for(int k=0;k<1000;k++)
			for(int i=0;i<8;i++){
				
				for(int j=0;j<16;j++){
					if(pattern[i][j]==1){
					PORTA = 1<<i;
					PORTB = j;
					}
					if(!f)
					if(PIND&0b00000001)
					if(pattern[i][j]==2){
						PORTA = 1<<i;
						PORTB = j;
						if(c>=300){
							pattern[i][j]=0;
							if(pattern[i][j+1]==1)f=1;
							else
							pattern[i][j+1]=2;
							c=0;
						}
					}
				}
			}
			
		}
	}



