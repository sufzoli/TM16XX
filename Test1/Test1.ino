/*
 Name:		TM16XX.ino
 Created:	1/18/2018 11:15:48 PM
 Author:	zoli
*/

#include <Arduino.h>
#include "TM16XX.h"
#include "Segment7.h"


const byte PIN_CLK = 3;   // define CLK pin (any digital pin)
const byte PIN_DIO = 2;   // define DIO pin (any digital pin)

TM16XX display(TM1637, PIN_CLK, PIN_DIO);

/*
void send(byte data)
{
	for (int i = 0; i < 8; i++) {
		digitalWrite(PIN_CLK, LOW);
		digitalWrite(PIN_DIO, data & 1 ? HIGH : LOW);
		data >>= 1;
		digitalWrite(PIN_CLK, HIGH);
	}
}

void sendCommand(byte cmd)
{
	digitalWrite(PIN_STB, LOW);
	send(cmd);
	digitalWrite(PIN_STB, HIGH);
}

*/

// uint8_t keys[4] = { 0,0,0,0 };

uint32_t keys;

// the setup function runs once when you press reset or power the board
void setup()
{
	delay(200);
/*	
	pinMode(PIN_DIO, OUTPUT);
	pinMode(PIN_CLK, OUTPUT);
	pinMode(PIN_STB, OUTPUT);

	digitalWrite(PIN_STB, HIGH);
	digitalWrite(PIN_CLK, HIGH);
	
	sendCommand(0x40);
	sendCommand(0x8F);

	digitalWrite(PIN_STB, LOW);
	send(0xC0);
	for (int i = 0; i < 16; i++) {
		send(0xFF);
	}
	digitalWrite(PIN_STB, HIGH);
*/
	Serial.begin(115200);
	
	// Set display brightness (change to adaptive in the next version)
	display.SetDisplayState(true, TM16XX_CONTROL_PWM_14);

	// Clear screen
	display.Clear();
	// initial number display
	display.DisplayNum(0, false, 6, 123456);
	// display.DisplayBin(2, 0xFF);
}

// the loop function runs over and over again until power down or reset
void loop()
{
  /*
	keys = display.KeyRead();
	Serial.println(keys, HEX);
	delay(500);

	display.p3_read(keys);
	for (uint8_t i = 0; i < 4; i++)
	{
		Serial.print(keys[i], HEX);
		Serial.print(",");
	}
	Serial.println();
	delay(500);
	*/
}
