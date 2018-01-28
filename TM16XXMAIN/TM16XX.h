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

#define TA6932 chip_type {5, TM16XX_IF_TYPE_P3, 0, 16, TM16XX_BUFF_WORD_8}
#define TM1616 chip_type {5, TM16XX_IF_TYPE_P3, 0, 8, TM16XX_BUFF_WORD_16}

#define TM1636 chip_type {5, TM16XX_IF_TYPE_P2, 1, 4, TM16XX_BUFF_WORD_8}
#define TM1637 chip_type {5, TM16XX_IF_TYPE_P2, 1, 6, TM16XX_BUFF_WORD_8}
#define TM1638 chip_type {5, TM16XX_IF_TYPE_P3, 4, 16, TM16XX_BUFF_WORD_16}
#define TM1640 chip_type {5, TM16XX_IF_TYPE_P2, 0, 16, TM16XX_BUFF_WORD_8}

class TM16XX
{
	public:
		// Constructor
		TM16XX();
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
		void p3_read(uint8_t* buff);
		void p2_command(uint8_t command);
		void p3_command(uint8_t command);
		void p2_data(uint8_t command, uint8_t data);
		void p3_data(uint8_t command, uint8_t data);

		virtual void Clear(void);
		void SetDisplayState(bool DisplayOn, uint8_t Brightness);
		void DisplayBin(uint8_t addr, uint8_t data);
		void DisplayBin(uint8_t addr, const uint8_t* data, uint8_t len);
		virtual void DisplayNum(uint8_t addr, bool leadingzero, uint8_t displaylen, uint32_t data);
// 		void DisplayNum(uint8_t addr, bool leadingzero, uint8_t displaylen, uint16_t data);
		void DisplayHex(uint8_t addr, uint8_t data);
	protected:
		// Variables
		uint8_t _CLK;
		uint8_t _DIO;
		uint8_t _STB;
		chip_type _IC;

		void init(chip_type ic, uint8_t pin_CLK, uint8_t pin_DIO);
		void init(chip_type ic, uint8_t pin_CLK, uint8_t pin_DIO, uint8_t pin_STB);
	private:
		// Variables
		uint8_t _Brightness;
		bool _DisplayOn;
};


// class Display_TM1638_8D_16K
// Chinese display module with:
// - Titan Microelectronics TM1638 driver IC
// - 8 digit 7 Segment Common Anode display
// - 16 (4x4) buttons
// The Display is in reverse (the driver primary designed for Common Chatode displays)

// Keyscan codes
#define TM1638_8D_16K_KEY_R1C1 0x20000000
#define TM1638_8D_16K_KEY_R1C2 0x02000000
#define TM1638_8D_16K_KEY_R1C3 0x00200000
#define TM1638_8D_16K_KEY_R1C4 0x00020000
#define TM1638_8D_16K_KEY_R2C1 0x00002000
#define TM1638_8D_16K_KEY_R2C2 0x00000200
#define TM1638_8D_16K_KEY_R2C3 0x00000020
#define TM1638_8D_16K_KEY_R2C4 0x00000002
#define TM1638_8D_16K_KEY_R3C1 0x40000000
#define TM1638_8D_16K_KEY_R3C2 0x04000000
#define TM1638_8D_16K_KEY_R3C3 0x00400000
#define TM1638_8D_16K_KEY_R3C4 0x00040000
#define TM1638_8D_16K_KEY_R4C1 0x00004000
#define TM1638_8D_16K_KEY_R4C2 0x00000400
#define TM1638_8D_16K_KEY_R4C3 0x00000040
#define TM1638_8D_16K_KEY_R4C4 0x00000004

class Display_TM1638_8D_16K : public TM16XX
{
	public:
		// Constructor
		Display_TM1638_8D_16K(uint8_t pin_CLK, uint8_t pin_DIO, uint8_t pin_STB);
		// Functions
		uint32_t KeyRead(void);
		void Clear(void); // The clear function must be overridden because the internal buffer must be cleared also
		void DisplayNum(uint8_t addr, bool leadingzero, uint8_t displaylen, uint32_t data);
	private:
		// Variables
		uint8_t _BUFF[8] = { 0,0,0,0,0,0,0,0 };
		// Functions
		void displayBuff(void);
};

// Chinese display module with:
// - Titan Microelectronics TM1638 driver IC
// - 8 digit 7 Segment Common Chatode display
// - 8 (1x8) buttons
// - 8 individual LEDs

// Keyscan codes
#define TM1638_8D_8K_8L_KEY_S1 0x80
#define TM1638_8D_8K_8L_KEY_S2 0x20
#define TM1638_8D_8K_8L_KEY_S3 0x08
#define TM1638_8D_8K_8L_KEY_S4 0x02
#define TM1638_8D_8K_8L_KEY_S5 0x40
#define TM1638_8D_8K_8L_KEY_S6 0x10
#define TM1638_8D_8K_8L_KEY_S7 0x04
#define TM1638_8D_8K_8L_KEY_S8 0x01

class Display_TM1638_8D_8K_8L : public TM16XX
{
	public:
		// Constructor
		Display_TM1638_8D_8K_8L(uint8_t pin_CLK, uint8_t pin_DIO, uint8_t pin_STB);
		// Functions
		uint8_t KeyRead(void);
		void LED(uint8_t num, bool enable);
};


class Display_TM1637_Clock : public TM16XX
{
	public:
		// Constructor
		Display_TM1637_Clock(uint8_t pin_CLK, uint8_t pin_DIO);
		// Functions
		void Clear(void); // The clear function must be overridden because the internal buffer must be cleared also
		void DisplayNum(uint8_t addr, bool leadingzero, uint8_t displaylen, uint16_t data);
		void Hour(uint8_t hour);
		void Min(uint8_t min);
		void Clock(uint8_t hour, uint8_t min);
		void Colon(bool colon);
	private:
		// Variables
		uint8_t _BUFF = 0; // single character buffer for the second digit used to store data to be able to set the separator colon individually
};

#define SEEED_TICK_TOCK_CLK 7
#define SEEED_TICK_TOCK_DIO 8

class Display_Seeed_Tick_Tock : public TM16XX
{
public:
	// Constructor
	Display_Seeed_Tick_Tock();
	// Functions
	void Clear(void); // The clear function must be overridden because the internal buffer must be cleared also
	void DisplayNum(uint8_t addr, bool leadingzero, uint8_t displaylen, uint16_t data);
	void Hour(uint8_t hour);
	void Min(uint8_t min);
	void Clock(uint8_t hour, uint8_t min);
	void Colon(bool colon);
	void Colon_Lower(bool lower_dot);
	void Colon_Upper(bool upper_dot);
private:
	// Variables
	uint8_t _BUFF[2] = { 0, 0 }; // double character buffer for the 3rd and 4th digit used to store data to be able to set the separator colon individually the upper dot for the 3rd and the lower for the 4th
};