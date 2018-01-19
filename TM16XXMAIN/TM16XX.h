#pragma once

#include <Arduino.h>

#define TM16XX_COMMAND_ADDRESS 0xC0
#define TM16XX_COMMAND_CONTROL 0x80
#define TM16XX_COMMAND_DATA_SET 0x40

#define TM16XX_DATA_READ 0x02
#define TM16XX_DATA_WRITE 0x00

#define TM16XX_DATA_AUTOINC 0x00
#define TM16XX_DATA_FIXADDR 0x04

#define TM16XX_CONTROL_PWM_1 0x00
#define TM16XX_CONTROL_PWM_2 0x01
#define TM16XX_CONTROL_PWM_4 0x02
#define TM16XX_CONTROL_PWM_10 0x03
#define TM16XX_CONTROL_PWM_11 0x04
#define TM16XX_CONTROL_PWM_12 0x05
#define TM16XX_CONTROL_PWM_13 0x06
#define TM16XX_CONTROL_PWM_14 0x07

#define TM16XX_CONTROL_OFF 0x00
#define TM16XX_CONTROL_ON 0x08

#define TM16XX_BUFF_WORD_8 0x00
#define TM16XX_BUFF_WORD_16 0x01


#define TM16XX_IF_TYPE_P2 0
#define TM16XX_IF_TYPE_P3 1

struct chip_type
{
	uint16_t clk_delay;
	uint8_t if_type;
	uint8_t ks_read_bytes;
	uint8_t display_buff_len;
	uint8_t buff_word_width;
};

#define TM1637 chip_type {5, TM16XX_IF_TYPE_P2, 1, 6, TM16XX_BUFF_WORD_8}
#define TM1638 chip_type {5, TM16XX_IF_TYPE_P3, 4, 16, TM16XX_BUFF_WORD_16}

class TM16XX
{
	public:
		// Constructor
		TM16XX(chip_type ic, uint8_t pin_CLK, uint8_t pin_DIO);
		TM16XX(chip_type ic, uint8_t pin_CLK, uint8_t pin_DIO, uint8_t pin_STB);
		// Low level functions
		void p2_start(void);
		void p3_start(void);
		void p2_stop(void);
		void p3_stop(void);
		void p2_write(uint8_t data);
		bool p2_ack(void);
		uint8_t p2_read(void);
		void p2_command(uint8_t command);
		void p3_command(uint8_t command);
		void p2_data(uint8_t command, uint8_t data);
		void p3_data(uint8_t command, uint8_t data);

		void Clear(void);
		void SetDisplayState(bool DisplayOn, uint8_t Brightness);
		void DisplayBin(uint8_t addr, uint8_t data);
		void DisplayBin(uint8_t addr, const uint8_t* data, uint8_t len);
		void DisplayNum(uint8_t addr, bool leadingzero, uint8_t displaylen, uint32_t data);
// 		void DisplayNum(uint8_t addr, bool leadingzero, uint8_t displaylen, uint16_t data);
		void DisplayHex(uint8_t addr, uint8_t data);
private:
		// Variables
		uint8_t _CLK;
		uint8_t _DIO;
		uint8_t _STB;
		chip_type _IC;
		uint8_t _Brightness;
		bool _DisplayOn;
};