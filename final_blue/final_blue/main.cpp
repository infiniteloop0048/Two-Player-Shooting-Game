#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>

void USART_init(void)
{
	UCSRA = 0b00000010;  // double speed
	UCSRB = 0b00011000;  // Enable Tx and Rx, polling
	UCSRC = 0b10000110;  // Async mode, no parity, 1 stop bit, 				8 data bits
	//in double-speed mode, UBRR = clock/(8xbaud rate) - 1
	UBRRH = 0;
	UBRRL = 12; // Baud rate 9600bps, assuming 1MHz clock
}

void UART_send(unsigned char data){
	// wait until UDRE flag is set to logic 1
	while ((UCSRA & (1<<UDRE)) == 0x00);
	UDR = data; // Write character to UDR for transmission
}

unsigned char UART_receive(void){
	// Wait until RXC flag is set to logic 1
	while ((UCSRA & (1<<RXC)) == 0x00);
	return UDR; // Read the received character from UDR
}

void send_string(char * str){
	int i = 0;
	while(str[i] != '\0'){
		UART_send(str[i]);
		i++;
	}
}


int main(void)
{
	DDRA = 0xFF;
	DDRB = 0xFF;
	USART_init(); // initialise USART
	//DDRA = 0b11111110;
	PORTA = 0b00000000;
	while (1) {
		
		unsigned char data = UART_receive();
		
		if(data=='1'){
			
			send_string("you are sending 1\n");
			PORTA=0b00000001;
			_delay_ms(320);
			PORTA=0b00000000;
		}
		else if(data=='2'){
			
			send_string("you are sending 2\n");
			PORTA=0b00000010;
			_delay_ms(320);
			PORTA=0b00000000;
		}
		else if(data=='3'){
			
			send_string("you are sending 3\n");
			PORTA=0b00000011;
			_delay_ms(320);
			PORTA=0b00000000;
		}
		else if(data=='4'){
			
			send_string("you are sending 4\n");
			PORTA=0b00000100;
			_delay_ms(320);
			PORTA=0b00000000;
		}
		else if(data=='5'){
			
			send_string("you are sending 5\n");
			PORTA=0b00000101;
			_delay_ms(420);
			PORTA=0b00000000;
		}
		else if(data=='6'){
			
			//send_string("you are sending 6\n");
			PORTA=0b00000110;
			_delay_ms(30);
			PORTA=0b00000000;
		}
		
	}
}