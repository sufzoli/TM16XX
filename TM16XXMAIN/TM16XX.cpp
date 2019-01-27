
#include "TM16XX.h"
#include "Segment7.h"
#include "Segment14.h"

const uint8_t HexChars[16] =
{
	SEG7_CHAR_0,
	SEG7_CHAR_1,
	SEG7_CHAR_2,
	SEG7_CHAR_3,
	SEG7_CHAR_4,
	SEG7_CHAR_5,
	SEG7_CHAR_6,
	SEG7_CHAR_7,
	SEG7_CHAR_8,
	SEG7_CHAR_9,
	SEG7_CHAR_A,
	SEG7_CHAR_B,
	SEG7_CHAR_C,
	SEG7_CHAR_D,
	SEG7_CHAR_E,
	SEG7_CHAR_F
};

const uint16_t HexChars_S14[16] =
{
	SEG14_CHAR_0,
	SEG14_CHAR_1,
	SEG14_CHAR_2,
	SEG14_CHAR_3,
	SEG14_CHAR_4,
	SEG14_CHAR_5,
	SEG14_CHAR_6,
	SEG14_CHAR_7,
	SEG14_CHAR_8,
	SEG14_CHAR_9,
	SEG14_CHAR_A,
	SEG14_CHAR_B,
	SEG14_CHAR_C,
	SEG14_CHAR_D,
	SEG14_CHAR_E,
	SEG14_CHAR_F
};

const uint16_t ASCII_S14[96] =
{
	0,	// 32 Space
	0,	// 33 !
	0,	// 34 "
	0,	// 35 #
	0,	// 36 $
	0,  // 37 %
	0,	// 38 &
	0,	// 39 '
	0,  // 40 (
	0,  // 41 )
	0,  // 42 *
	0,  // 43 +
	0,  // 44 ,
	0,  // 45 -
	0,  // 46 .
	0,	// 47 /
	SEG14_CHAR_0,	// 48 0
	SEG14_CHAR_1,	// 49 1
	SEG14_CHAR_2,	// 50 2
	SEG14_CHAR_3,	// 51 3
	SEG14_CHAR_4,	// 52 4
	SEG14_CHAR_5,	// 53 5
	SEG14_CHAR_6,	// 54 6
	SEG14_CHAR_7,	// 55 7
	SEG14_CHAR_8,	// 56 8
	SEG14_CHAR_9,	// 57 9
	0,	// 58 :
	0,	// 59 ;
	0,	// 60 <
	0,	// 61 =
	0,	// 62 >
	0,	// 63 ?
	0,	// 64 @
	SEG14_CHAR_A,	// 65 A
	SEG14_CHAR_B,	// 66 B
	SEG14_CHAR_C,	// 67 C
	SEG14_CHAR_D,	// 68 D
	SEG14_CHAR_E,	// 69 E
	SEG14_CHAR_F,	// 70 F
	SEG14_CHAR_G,	// 71 G
	SEG14_CHAR_H,	// 72 H
	SEG14_CHAR_I,	// 73 I
	SEG14_CHAR_J,	// 74 J
	SEG14_CHAR_K,	// 75 K
	SEG14_CHAR_L,	// 76 L
	SEG14_CHAR_M,	// 77 M
	SEG14_CHAR_N,	// 78 N
	SEG14_CHAR_O,	// 79 O
	SEG14_CHAR_P,	// 80 P
	SEG14_CHAR_Q,	// 81 Q
	SEG14_CHAR_R,	// 82 R
	SEG14_CHAR_S,	// 83 S
	SEG14_CHAR_T,	// 84 T
	SEG14_CHAR_U,	// 85 U
	SEG14_CHAR_V,	// 86 V
	SEG14_CHAR_W,	// 87 W
	SEG14_CHAR_X,	// 88 X
	SEG14_CHAR_Y,	// 89 Y
	SEG14_CHAR_Z,	// 90 Z
	0,	// 91 [
	0,	// 92 backslash \
	0,	// 93 ]
	0,	// 94 ^
	0,	// 95 _
	0,	// 96 `
	SEG14_CHAR_A,	// 97 a
	SEG14_CHAR_B,	// 98 b
	SEG14_CHAR_C,	// 99 c
	SEG14_CHAR_D,	// 100 d
	SEG14_CHAR_E,	// 101 e
	SEG14_CHAR_F,	// 102 f
	SEG14_CHAR_G,	// 103 g
	SEG14_CHAR_H,	// 104 h
	SEG14_CHAR_I,	// 105 i
	SEG14_CHAR_J,	// 106 j
	SEG14_CHAR_K,	// 107 k
	SEG14_CHAR_L,	// 108 l
	SEG14_CHAR_M,	// 109 m
	SEG14_CHAR_N,	// 110 n
	SEG14_CHAR_O,	// 111 o
	SEG14_CHAR_P,	// 112 p
	SEG14_CHAR_Q,	// 113 q
	SEG14_CHAR_R,	// 114 r
	SEG14_CHAR_S,	// 115 s
	SEG14_CHAR_T,	// 116 t
	SEG14_CHAR_U,	// 117 u
	SEG14_CHAR_V,	// 118 v
	SEG14_CHAR_W,	// 119 w
	SEG14_CHAR_X,	// 120 x
	SEG14_CHAR_Y,	// 121 y
	SEG14_CHAR_Z,	// 122 z
	0,	// 123 {
	0,	// 124 |
	0,	// 125 }
	0,	// 126 ~
	0	// 127 DEL
};


TM16XX::TM16XX() {}

TM16XX::TM16XX(chip_type ic, uint8_t pin_CLK, uint8_t pin_DIO)
{
	init(ic, pin_CLK, pin_DIO);
}
TM16XX::TM16XX(chip_type ic, uint8_t pin_CLK, uint8_t pin_DIO, uint8_t pin_STB)
{
	init( ic, pin_CLK, pin_DIO, pin_STB);
}
TM16XX::TM16XX(chip_type ic, uint8_t pin_CLK, uint8_t pin_DOUT, uint8_t pin_DIN, uint8_t pin_STB)
{
	init(ic, pin_CLK, pin_DOUT, pin_DIN, pin_STB);
}

// 2 pin constructor
void TM16XX::init(chip_type ic, uint8_t pin_CLK, uint8_t pin_DIO)
{
	_CLK = pin_CLK;
	_DIO = pin_DIO;
	_IC = ic;
	pinMode(_CLK, OUTPUT);
	pinMode(_DIO, OUTPUT);
	digitalWrite(_CLK, 1);
	digitalWrite(_DIO, 1);
}

// 3 pin constructor
void TM16XX::init(chip_type ic, uint8_t pin_CLK, uint8_t pin_DIO, uint8_t pin_STB)
{
	_CLK = pin_CLK;
	_DIO = pin_DIO;
	_STB = pin_STB;
	_IC = ic;
	pinMode(_CLK, OUTPUT);
	pinMode(_DIO, OUTPUT);
	pinMode(_STB, OUTPUT);
	digitalWrite(_STB, 1);
	digitalWrite(_CLK, 1);
 	digitalWrite(_DIO, 1);
}

// 4 pin constructor
void TM16XX::init(chip_type ic, uint8_t pin_CLK, uint8_t pin_DOUT, uint8_t pin_DIN, uint8_t pin_STB)
{
	_CLK = pin_CLK;
	_DIO = pin_DOUT;
	_DIN = pin_DIN;
	_STB = pin_STB;
	_IC = ic;
	pinMode(_CLK, OUTPUT);
	pinMode(_DIO, OUTPUT);
	pinMode(_DIN, INPUT_PULLUP);
	pinMode(_STB, OUTPUT);
	digitalWrite(_STB, 1);
	digitalWrite(_CLK, 1);
	digitalWrite(_DIO, 1);
}

void TM16XX::p2_start(void)
{
	digitalWrite(_DIO, 1);
	digitalWrite(_CLK, 1);
	delayMicroseconds(_IC.clk_delay);
	digitalWrite(_DIO, 0);
}

void TM16XX::p34_start(void)
{
	digitalWrite(_DIO, 0);
	digitalWrite(_CLK, 1);
	delayMicroseconds(_IC.clk_delay);
	digitalWrite(_STB, 0);
	delayMicroseconds(_IC.clk_delay);
}

void TM16XX::p2_stop(void)
{
	digitalWrite(_CLK, 0);
	delayMicroseconds(_IC.clk_delay);
	digitalWrite(_DIO, 0);
	delayMicroseconds(_IC.clk_delay);
	digitalWrite(_CLK, 1);
	delayMicroseconds(_IC.clk_delay);
	digitalWrite(_DIO, 1);
}

void TM16XX::p34_stop(void)
{
	delayMicroseconds(_IC.clk_delay);
	digitalWrite(_STB, 1);
}

void TM16XX::p234_write(uint8_t data)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		digitalWrite(_CLK, 0);
		digitalWrite(_DIO, (data & B1) ? 1 : 0);
		delayMicroseconds(_IC.clk_delay);
		data >>= 1;
		digitalWrite(_CLK, 1);
		delayMicroseconds(_IC.clk_delay);
	}
}

bool TM16XX::p2_ack(void)
{
	bool retval = false;
	digitalWrite(_CLK, 0);
	pinMode(_DIO, INPUT_PULLUP);
	delayMicroseconds(_IC.clk_delay);
	retval = digitalRead(_DIO) == 0;
	digitalWrite(_CLK, 1);
	delayMicroseconds(_IC.clk_delay);
	digitalWrite(_CLK, 0);
	pinMode(_DIO, OUTPUT);
	return retval;
}

uint8_t TM16XX::p2_read(void)
{
	uint8_t revalue = 0;
	p2_start();
	p234_write(TM16XX_COMMAND_DATA_SET | TM16XX_DATA_READ);
	p2_ack();

	pinMode(_DIO, INPUT);
	digitalWrite(_DIO, 1);
	delayMicroseconds(_IC.clk_delay);
	for (uint8_t i = 0; i < 8; i++)
	{
		revalue <<= 1;
		digitalWrite(_CLK, 0);
		delayMicroseconds(_IC.clk_delay);
		digitalWrite(_CLK, 1);
		revalue = revalue | digitalRead(_DIO);
		delayMicroseconds(_IC.clk_delay);
	}
	pinMode(_DIO, OUTPUT);
	p2_ack();
	p2_stop();
	return revalue;
}

void TM16XX::p3_read(uint8_t* buff)
{
	p34_start();
	p234_write(TM16XX_COMMAND_DATA_SET | TM16XX_DATA_READ);
	pinMode(_DIO, INPUT_PULLUP); // Change data direction to input
	delayMicroseconds(_IC.clk_delay); // TWAIT
	for (uint8_t j = 0; j < _IC.ks_read_bytes; j++)
	{
		for (uint8_t i = 0; i < 8; i++)
		{
			buff[j] <<= 1;
			digitalWrite(_CLK, 0);
			delayMicroseconds(_IC.clk_delay);
			digitalWrite(_CLK, 1);
			buff[j] = buff[j] | digitalRead(_DIO);
			delayMicroseconds(_IC.clk_delay);
		}
	}
	pinMode(_DIO, OUTPUT);
	p34_stop();
}

void TM16XX::p4_read(uint8_t* buff)
{
	p34_start();
	p234_write(TM16XX_COMMAND_DATA_SET | TM16XX_DATA_READ);
	delayMicroseconds(_IC.clk_delay); // TWAIT
	for (uint8_t j = 0; j < _IC.ks_read_bytes; j++)
	{
		for (uint8_t i = 0; i < 8; i++)
		{
			buff[j] <<= 1;
			digitalWrite(_CLK, 0);
			delayMicroseconds(_IC.clk_delay);
			digitalWrite(_CLK, 1);
			buff[j] = buff[j] | digitalRead(_DIN);
			delayMicroseconds(_IC.clk_delay);
		}
	}
	p34_stop();
}



void TM16XX::p2_command(uint8_t command)
{
	p2_start();
	p234_write(command);
	p2_ack();
	p2_stop();
}

void TM16XX::p34_command(uint8_t command)
{
	p34_start();
	p234_write(command);
	p34_stop();
}

void TM16XX::p2_data(uint8_t command, uint8_t data)
{
	p2_start();
	p234_write(command);
	p2_ack();
	p234_write(data);
	p2_ack();
	p2_stop();
}

void TM16XX::p34_data(uint8_t command, uint8_t data)
{
	p34_start();
	p234_write(command);
	p234_write(data);
	p34_stop();
}

void TM16XX::Clear(void)
{
	switch (_IC.if_type)
	{
		case TM16XX_IF_TYPE_P2:
			p2_command(TM16XX_COMMAND_DATA_SET | TM16XX_DATA_AUTOINC | TM16XX_DATA_WRITE);

			p2_start();
			p234_write(TM16XX_COMMAND_ADDRESS);
			p2_ack();

			for (uint8_t i = 0; i < _IC.display_buff_len; i++)
			{
				p234_write(0);
				p2_ack();
			}
			p2_stop();

			p2_command(TM16XX_COMMAND_CONTROL | (_DisplayOn ? TM16XX_CONTROL_ON : TM16XX_CONTROL_OFF) | _Brightness);
			break;
		case TM16XX_IF_TYPE_P3:
		case TM16XX_IF_TYPE_P4:
			p34_command(TM16XX_COMMAND_DATA_SET | TM16XX_DATA_AUTOINC | TM16XX_DATA_WRITE);

			p34_start();
			p234_write(TM16XX_COMMAND_ADDRESS);
			for (uint8_t i = 0; i < _IC.display_buff_len; i++)
			{
				p234_write(0);
			}
			p34_stop();

			p34_command(TM16XX_COMMAND_CONTROL | (_DisplayOn ? TM16XX_CONTROL_ON : TM16XX_CONTROL_OFF) | _Brightness);

			break;
	}
}

void TM16XX::SetDisplayState(bool DisplayOn, uint8_t Brightness)
{
	_DisplayOn = DisplayOn;
	_Brightness = Brightness;
}

void TM16XX::DisplayBin(uint8_t addr, uint8_t data)
{
	switch (_IC.if_type)
	{
		case TM16XX_IF_TYPE_P2:
			p2_command(TM16XX_COMMAND_DATA_SET);
			p2_data(TM16XX_COMMAND_ADDRESS | addr, data);
			p2_command(TM16XX_COMMAND_CONTROL | (_DisplayOn ? TM16XX_CONTROL_ON : TM16XX_CONTROL_OFF) | _Brightness);
			break;
		case TM16XX_IF_TYPE_P3:
		case TM16XX_IF_TYPE_P4:
			p34_command(TM16XX_COMMAND_DATA_SET);
			p34_data(TM16XX_COMMAND_ADDRESS | addr, data);
			p34_command(TM16XX_COMMAND_CONTROL | (_DisplayOn ? TM16XX_CONTROL_ON : TM16XX_CONTROL_OFF) | _Brightness);
			break;
	}
}

void TM16XX::DisplayBin(uint8_t addr, const uint8_t* data, uint8_t len)
{
	switch (_IC.if_type)
	{
	case TM16XX_IF_TYPE_P2:
		p2_command(TM16XX_COMMAND_DATA_SET | TM16XX_DATA_AUTOINC | TM16XX_DATA_WRITE);

		p2_start();
		p234_write(TM16XX_COMMAND_ADDRESS | addr);
		p2_ack();
		for (uint8_t i = 0; i < len; i++)
		{
			p234_write(data[i]);
			p2_ack();
		}
		p2_stop();

		p2_command(TM16XX_COMMAND_CONTROL | (_DisplayOn ? TM16XX_CONTROL_ON : TM16XX_CONTROL_OFF) | _Brightness);
		break;
	case TM16XX_IF_TYPE_P3:
	case TM16XX_IF_TYPE_P4:
		p34_command(TM16XX_COMMAND_DATA_SET | TM16XX_DATA_AUTOINC | TM16XX_DATA_WRITE);

		p34_start();
		p234_write(TM16XX_COMMAND_ADDRESS | addr);
		for (uint8_t i = 0; i < len; i++)
		{
			p234_write(data[i]);
		}
		p34_stop();

		p34_command(TM16XX_COMMAND_CONTROL | (_DisplayOn ? TM16XX_CONTROL_ON : TM16XX_CONTROL_OFF) | _Brightness);

		break;
	}
}

void TM16XX::DisplayNum(uint8_t addr, bool leadingzero, uint8_t displaylen, uint32_t data)
{
	for (int i = displaylen - 1; i >= 0; i--)
	{
		DisplayBin((addr + i) << _IC.buff_word_width, (leadingzero || data != 0) ? HexChars[data % 10] : 0);
		data /= 10;
	}
}

void TM16XX::DisplayNumS14(uint8_t addr, bool leadingzero, uint8_t displaylen, uint32_t data)
{
	for (int i = displaylen - 1; i >= 0; i--)
	{
		DisplayBin((addr + i) << _IC.buff_word_width, (leadingzero || data != 0) ? HexChars_S14[data % 10] & 0xFF : 0);
		DisplayBin(((addr + i) << _IC.buff_word_width) + 1, (leadingzero || data != 0) ? HexChars_S14[data % 10] >> 8 : 0);
		data /= 10;
	}
}

void TM16XX::DisplayStrS14(uint8_t addr, uint8_t displaylen, String data)
{
	for (int i = addr; i < displaylen; i++)
	{
		DisplayBin((i) << _IC.buff_word_width, ASCII_S14[data[i - addr]-32] & 0xFF);
		DisplayBin(((i) << _IC.buff_word_width) + 1, ASCII_S14[data[i - addr]-32] >> 8);
	}
}


void TM16XX::DisplayHex(uint8_t addr, uint8_t displaylen, uint32_t data)
{
	for (int i = displaylen - 1; i >= 0; i--)
	{
		DisplayBin((addr + i) << _IC.buff_word_width, HexChars[data & 0x0000000F]);
		data >>= 4;
	}
}



Display_TM1638_8D_16K::Display_TM1638_8D_16K(uint8_t pin_CLK, uint8_t pin_DIO, uint8_t pin_STB)
{
	init(TM1638, pin_CLK, pin_DIO, pin_STB);
}

uint32_t Display_TM1638_8D_16K::KeyRead(void)
{
	uint32_t keys = 0;
	p34_start();
	p234_write(TM16XX_COMMAND_DATA_SET | TM16XX_DATA_READ);
	pinMode(_DIO, INPUT_PULLUP); // Change data direction to input
	delayMicroseconds(_IC.clk_delay); // TWAIT
	for (uint8_t i = 0; i < 32; i++)
	{
		keys <<= 1;
		digitalWrite(_CLK, 0);
		delayMicroseconds(_IC.clk_delay);
		digitalWrite(_CLK, 1);
		keys = keys | digitalRead(_DIO);
		delayMicroseconds(_IC.clk_delay);
	}
	pinMode(_DIO, OUTPUT);
	p34_stop();
	return keys;
}

void Display_TM1638_8D_16K::Clear(void)
{
	// Clear buffer
	for (uint8_t i = 0; i < 8; i++)
	{
		_BUFF[i] = 0;
	}
	TM16XX::Clear();
}

void Display_TM1638_8D_16K::DisplayNum(uint8_t addr, bool leadingzero, uint8_t displaylen, uint32_t data)
{
	for (int i = displaylen - 1; i >= 0; i--)
	{
		_BUFF[addr + i] = (leadingzero || data != 0) ? HexChars[data % 10] : 0;
		data /= 10;
	}
	displayBuff();
}

void Display_TM1638_8D_16K::DisplayHex(uint8_t addr, uint8_t displaylen, uint32_t data)
{
	for (int i = displaylen - 1; i >= 0; i--)
	{
		_BUFF[addr + i] = HexChars[data & 0x0000000F];
		data <<= 4;
	}
	displayBuff();
}

void Display_TM1638_8D_16K::displayBuff(void)
{
	uint8_t tempdata = 0;
	for (uint8_t i = 0; i < 8; i++)
	{
		for (uint8_t j = 0; j < 8; j++)
		{
			tempdata = (tempdata << 1) | ((_BUFF[j] & (1 << i)) >> i);
		}
		DisplayBin(i << 1, tempdata);
	}
}

/*
Display_TM1637_Clock
*/


Display_TM1637_Clock::Display_TM1637_Clock(uint8_t pin_CLK, uint8_t pin_DIO)
{
	init(TM1637, pin_CLK, pin_DIO);
}

void Display_TM1637_Clock::Clear(void)
{
	_BUFF = 0;
	TM16XX::Clear();
}

void Display_TM1637_Clock::DisplayNum(uint8_t addr, bool leadingzero, uint8_t displaylen, uint16_t data)
{
	uint8_t bindata;
	for (int i = displaylen - 1; i >= 0; i--)
	{
		// generate the binary data of the digit
		bindata = (leadingzero || data != 0) ? HexChars[data % 10] : 0;
		// if it is the second digit (contains the hour/munite separator column)
		if ((addr + i) == 1)
		{
			bindata = bindata | (_BUFF & 0x80); // use the colon state from the buffer
			_BUFF = bindata; // save the current data to the buffer
		}
		// display it
		DisplayBin((addr + i), bindata);
		data /= 10;
	}
}

void Display_TM1637_Clock::Hour(uint8_t hour)
{
	DisplayNum(0, true, 2, hour);
}

void Display_TM1637_Clock::Min(uint8_t min)
{
	DisplayNum(2, true, 2, min);
}

void Display_TM1637_Clock::Clock(uint8_t hour, uint8_t min)
{
	DisplayNum(0, true, 2, hour);
	DisplayNum(2, true, 2, min);
}

void Display_TM1637_Clock::Colon(bool colon)
{
	_BUFF = colon ? _BUFF | 0x80 : _BUFF & 0x7F;
	DisplayBin(1, _BUFF);
}

/*
Display_TM1638_8D_8K_8L
*/

Display_TM1638_8D_8K_8L::Display_TM1638_8D_8K_8L(uint8_t pin_CLK, uint8_t pin_DIO, uint8_t pin_STB)
{
	init(TM1638, pin_CLK, pin_DIO, pin_STB);
}

uint8_t Display_TM1638_8D_8K_8L::KeyRead(void)
{
	uint8_t keys = 0;
	p34_start();
	p234_write(TM16XX_COMMAND_DATA_SET | TM16XX_DATA_READ);
	pinMode(_DIO, INPUT_PULLUP); // Change data direction to input
	delayMicroseconds(_IC.clk_delay); // TWAIT
	for (uint8_t i = 0; i < 32; i++)
	{
		if(i % 4 == 0)
			keys <<= 1;
		digitalWrite(_CLK, 0);
		delayMicroseconds(_IC.clk_delay);
		digitalWrite(_CLK, 1);
		if (i % 4 == 0)
			keys = keys | digitalRead(_DIO);
		delayMicroseconds(_IC.clk_delay);
	}
	pinMode(_DIO, OUTPUT);
	p34_stop();
	return keys;
}

void Display_TM1638_8D_8K_8L::LED(uint8_t num, bool enable)
{
	DisplayBin(((num - 1) << 1) | 1, enable ? 1 : 0);
}

/*
Display_Seeed_Tick_Tock
*/


Display_Seeed_Tick_Tock::Display_Seeed_Tick_Tock()
{
	init(TM1636, SEEED_TICK_TOCK_CLK, SEEED_TICK_TOCK_DIO);
}

void Display_Seeed_Tick_Tock::Clear(void)
{
	_BUFF[0] = 0;
	_BUFF[1] = 0;
	TM16XX::Clear();
}

void Display_Seeed_Tick_Tock::DisplayNum(uint8_t addr, bool leadingzero, uint8_t displaylen, uint16_t data)
{
	uint8_t bindata;
	for (int i = displaylen - 1; i >= 0; i--)
	{
		// generate the binary data of the digit
		bindata = (leadingzero || data != 0) ? HexChars[data % 10] : 0;
		// if it is the 3rd or 4th digit (contains the hour/munite separator column)
		if ((addr + i) == 2 || (addr + i) == 3)
		{
			bindata = bindata | (_BUFF[(addr + i) - 2] & 0x80); // use the colon state from the buffer
			_BUFF[(addr + i) - 2] = bindata; // save the current data to the buffer
		}
		// display it
		DisplayBin((addr + i), bindata);
		data /= 10;
	}
}

void Display_Seeed_Tick_Tock::Hour(uint8_t hour)
{
	DisplayNum(0, true, 2, hour);
}

void Display_Seeed_Tick_Tock::Min(uint8_t min)
{
	DisplayNum(2, true, 2, min);
}

void Display_Seeed_Tick_Tock::Clock(uint8_t hour, uint8_t min)
{
	DisplayNum(0, true, 2, hour);
	DisplayNum(2, true, 2, min);
}

void Display_Seeed_Tick_Tock::Colon(bool colon)
{
	_BUFF[0] = colon ? _BUFF[0] | 0x80 : _BUFF[0] & 0x7F;
	_BUFF[1] = colon ? _BUFF[1] | 0x80 : _BUFF[1] & 0x7F;
	DisplayBin(2, _BUFF,2);
}

void Display_Seeed_Tick_Tock::Colon_Lower(bool lower_dot)
{
	_BUFF[1] = lower_dot ? _BUFF[1] | 0x80 : _BUFF[1] & 0x7F;
	DisplayBin(3, _BUFF[1]);
}

void Display_Seeed_Tick_Tock::Colon_Upper(bool upper_dot)
{
	_BUFF[0] = upper_dot ? _BUFF[0] | 0x80 : _BUFF[0] & 0x7F;
	DisplayBin(2, _BUFF[0]);
}
