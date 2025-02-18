// Yousef Tantawy | Project 2 - interfacing part 1 || Diploma 91

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define time 50 // Ensure digit is shown for short period before the next

char sec = 0, min = 0, hour = 0;

void timer1_init(void); // Timer interrupt

void int0_init(void); // External Interrupt 1

void int1_init(void); // External Interrupt 2

void int2_init(void); // External Interrupt 3

void sevenSegmentDisplay(void); // For displaying numbers on the 7segment


ISR(TIMER1_COMPA_vect){ // Timer interrupt code

	if(PORTD & 1 << PD5){ // Count down

		PORTD = (0x30 & (1 << PB5)) | (0xCF & PORTD); // Activate Yellow led

		if(sec == 0 && min == 0 && hour == 0){
			PORTD |= 0x01; //Activate buzzer
		}

		else {
			if (sec == 0) {
				if (min == 0) {
					if (hour > 0) {
						hour--;    // Decrement hour if available
						min = 59;  // Reset minutes to 59
						sec = 59;  // Reset seconds to 59
					}
				}
				else {
					min--;    // Decrement minute
					sec = 59; // Reset seconds to 59
				}
			}
			else {
				sec--; // Decrement seconds
			}
		}
	}

	else if(PORTD & 1 << PD4){ // Count up

		PORTD = (0x31 & (1 << PB4)) | (0xCE & PORTD); // Activate Red led

		sec++; // increment seconds

		if(sec == 60){
			sec = 0; // reset to 0
			min++; // increment minutes
			if(min == 60){
				min = 0; // reset minutes
				hour++; // increment hours
				if(hour == 90){
					hour = 0; // reset hours
				}
			}
		}
	}
}

ISR(INT0_vect){ // Reset interrupt code
	hour = 0;
	min = 0;
	sec = 0;
}

ISR(INT1_vect){ // Pause interrupt code | stop timer
	TCCR1B &= ~(1<<CS12) & ~(1<<CS10) & ~(1<<WGM12);
}

ISR(INT2_vect){ // Resume interrupt code
	TCCR1B = (1<<CS12) | (1<<CS10) | (1<<WGM12);
}

int main(void){
	SREG |= 1<<7; // Global Interrupt register

	DDRC |= 0x0F;
	PORTC |= 0x00;

	DDRA |= 0x3F;
	PORTA |= 0x3F;

	DDRD &= ~(0x0C);
	DDRD |= 0x31;
	PORTD |= 0x1C;

	DDRB &= ~(0xFF);
	PORTB |= 0xFF;

	timer1_init(); // Activate timer
	int0_init(); // Activate External interrupt 0
	int1_init(); // Activate External interrupt 1
	int2_init(); // Activate External interrupt 2

	for(;;){

		if(!(PINB & 1 << 7)){
			PORTD ^= 0x30;
			while(!(PINB & 1 <<7)){
				sevenSegmentDisplay();
			}
		}
		// This is to indicate whether the timer is counting up or down

		if(!(PINB & 1 << PB1)){
			_delay_ms(30); // Avoid button error
			if(!(PINB & 1 << PB1)){
				if(hour != 90){ // Don't exceed hour limit
					hour++;
				}
			}
			while(!(PINB & 1 << PB1)){
				sevenSegmentDisplay(); // Display until button unpressed
			}
		}

		else if(!(PINB & 1 << PB0)){
			_delay_ms(30); // Avoid button error
			if(!(PINB & 1 << PB0)){
				if(hour != 0){ // Don't exceed hour limit
					hour--;
				}
			}
			while(!(PINB & 1 << PB0)){
				sevenSegmentDisplay(); // Display until button unpressed
			}
		}

		else if(!(PINB & 1 << PB4)){
			_delay_ms(30); // Avoid button error
			if(!(PINB & 1 << PB4)){
				if(min != 59){ // Don't exceed min limit
					min++;
				}
			}
			while(!(PINB & 1 << PB4)){
				sevenSegmentDisplay(); // Display until button unpressed
			}
		}

		else if(!(PINB & 1 << PB3)){
			_delay_ms(30); // Avoid button error
			if(!(PINB & 1 << PB3)){
				if(min != 0){ // Don't exceed min limit
					min--;
				}
			}
			while(!(PINB & 1 << PB3)){
				sevenSegmentDisplay(); // Display until button unpressed
			}
		}

		else if(!(PINB & 1 << PB6)){
			_delay_ms(30); // Avoid button error
			if(!(PINB & 1 << PB6)){
				if(sec != 59){ // Don't exceed sec limit
					sec++;
				}
			}
			while(!(PINB & 1 << PB6)){
				sevenSegmentDisplay(); // Display until button unpressed
			}
		}

		else if(!(PINB & 1 << PB5)){
			_delay_ms(30); // Avoid button error
			if(!(PINB & 1 << PB5)){
				if(sec != 0){ // Don't exceed sec limit
					sec--;
				}
			}
			while(!(PINB & 1 << PB5)){
				sevenSegmentDisplay(); // Display until button unpressed
			}
		}

		else{
		sevenSegmentDisplay(); // Display if no buttons are pressed
		}
	}
}

void timer1_init(void){ // Timer1 Config for 7 Segment
	TCNT1 = 0; // Intial point

	OCR1A = 15625; // Stopping point

	TCCR1B = (1<<CS12) | (1<<CS10) | (1<<WGM12);
	// CS12 and CS10 to activate 1024 prescaler
	// WGM12 to activate Timer1 CTC mode to OCR1A

	TIMSK |= 1<<OCIE1A; // Enable  OCIE1A flag
}

void int0_init(void){
	MCUCR |= 1 << ISC01; // Activate falling edge
	GICR |= 1 << INT0; // Enable interrupt 0
}

void int1_init(void){
	MCUCR |= 1 << ISC11 | 1 << ISC10; // Activate rising edge
	GICR |= 1 << INT1; // Enable interrupt 1
}

void int2_init(void){
	MCUCSR &= ~(1 << ISC2); // Activate falling edge
	GICR |= 1 << INT2; // Enable interrupt 2
}

void sevenSegmentDisplay(void){
	PORTA = 1 << PA5 ; // enable 1st 7 segment
	PORTC = sec%10;	// Display 1st digit of seconds
	_delay_us(time);

	PORTA = 1 << PA4; // enable 2nd 7 segment
	PORTC = sec/10; // Display 2nd digit of seconds
	_delay_us(time);

	PORTA = 1 << PA3; // enable 3rd 7 segment
	PORTC = min%10; // Display 1st digit of minutes
	_delay_us(time);

	PORTA = 1 << PA2; // enable 4th 7 segment
	PORTC = min/10; // Display 2nd digit of minutes
	_delay_us(time);

	PORTA = 1 << PA1; // enable 5th 7 segment
	PORTC = hour%10; // Display 1st digit of hours
	_delay_us(time);

	PORTA = 1 << PA0; // enable 6th 7 segment
	PORTC = hour/10; // Display 2nd digit of hours
	_delay_us(time);
}

