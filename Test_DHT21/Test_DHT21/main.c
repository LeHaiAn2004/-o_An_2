/*
 * Example test bench for DHT22 on an Atmega 1284 
 *
 * Author      : David Feng
 * Updated     : June 26th, 2018
 * Usage       : Compiled on AVR-GCC using Atmel Studio 7 
 */

#ifndef F_CPU
#define F_CPU 8000000UL //define microcontroller clock speed
#endif

#include <util/delay.h>
#include "lcd_io.h" //library that controls LCD display
#include "DHT.h" //library that works with DHT sensor
#define DEGREE_SYMBOL 0xDF
uint16_t temperature_int = 0;
uint16_t humidity_int = 0;

//function to convert number values into characters
/*void LCD_print(uint16_t temp, unsigned char cur_count) {
	
	unsigned char ten_count = 0;
	unsigned char hun_count = 0;

	LCD_Cursor(cur_count);
	while( temp >= 100 ) {
		hun_count++;
		temp -= 100;
	}	
	
	LCD_WriteData(hun_count + '0');
	cur_count++;

	LCD_Cursor(cur_count);
	while( temp >= 10 ) {
		ten_count++;
		temp -= 10;
	}
	
	LCD_WriteData(ten_count + '0');
	cur_count++;
	
	LCD_Cursor(cur_count);
	LCD_WriteData('.');
	cur_count++;	
	
	LCD_Cursor(cur_count);
	LCD_WriteData((unsigned char) temp + '0');
	
	LCD_Cursor(0);
}*/
// Hàm m?i ?? hi?n th? s? nguyên 2 ch? s? (thay th? cho hàm LCD_print c?)
void LCD_print_integer(uint16_t number, unsigned char column) {
	char buffer[3]; // Buffer cho 2 ch? s? và ký t? k?t thúc chu?i
	sprintf(buffer, "%02d", number); // ??nh d?ng s? thành chu?i 2 ch? s? (ví d?: 9 -> "09", 31 -> "31")

	LCD_Cursor(column); // Di chuy?n con tr? ??n c?t b?t ??u
	LCD_WriteData(buffer[0]); // In ra ch? s? hàng ch?c

	LCD_Cursor(column + 1); // Di chuy?n ??n c?t ti?p theo
	LCD_WriteData(buffer[1]); // In ra ch? s? hàng ??n v?
}

int main(void) {
	
	//Initializing LCD Display to output data from DHT sensor
	
	DDRC = 0xFF; PORTC = 0x00;   // set PORTC to output
	DDRD = 0xFF; PORTD = 0x00;   // set PORTD to output

	const char* template = "Temp:   oC      Led: ";
	const char* error = "Error";
	
	LCD_init();
	LCD_ClearScreen ();
	LCD_DisplayString (1, template);

	_delay_ms(1000);
		
    while (1) {
		//call DHT sensor function defined in DHT.c
		// Bên trong vòng l?p while(1) c?a hàm main

		if (dht_GetTempUtil(&temperature_int, &humidity_int) != -1) {
			// G?i hàm m?i ?? hi?n th? nhi?t ??
			LCD_print_integer(temperature_int, 6); // In nhi?t ?? ? c?t th? 6
			if (temperature_int > 25 || temperature_int < 20) {
				LCD_print_integer(1, 22); // In nhi?t ?? ? c?t th? 6
			}
			else {
				LCD_print_integer(0, 22); // In nhi?t ?? ? c?t th? 6
			}
			// G?i hàm m?i ?? hi?n th? ?? ?m
			//LCD_print_integer(humidity_int, 20); // In ?? ?m ? c?t th? 20
		}
		
		else {LCD_DisplayString (1, error);}
		
		_delay_ms(1000);
    }
}