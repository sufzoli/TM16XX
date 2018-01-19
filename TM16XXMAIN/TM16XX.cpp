
#include "TM16XX.h"
#include "Segment7.h"

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


TM16XX::TM16XX(chip_type ic, uint8_t pin_CLK, uint8_t pin_DIO)
{
	_CLK = pin_CLK;
	_DIO = pin_DIO;
	_IC = ic;
	pinMode(_CLK, OUTPUT);
	pinMode(_DIO, OUTPUT);
	digitalWrite(_CLK, 1);
	digitalWrite(_DIO, 1);
}

TM16XX::TM16XX(chip_type ic, uint8_t pin_CLK, uint8_t pin_DIO, uint8_t pin_STB)
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


void TM16XX::p2_start(void)
{
	digitalWrite(_DIO, 1);
	digitalWrite(_CLK, 1);
	delayMicroseconds(_IC.clk_delay);
	digitalWrite(_DIO, 0);
}

void TM16XX::p3_start(void)
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

void TM16XX::p3_stop(void)
{
	delayMicroseconds(_IC.clk_delay);
	digitalWrite(_STB, 1);
}

void TM16XX::p2_write(uint8_t data)
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
	p2_write(TM16XX_COMMAND_DATA_SET | TM16XX_DATA_READ);
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

void TM16XX::p2_command(uint8_t command)
{
	p2_start();
	p2_write(command);
	p2_ack();
	p2_stop();
}

void TM16XX::p3_command(uint8_t command)
{
	p3_start();
	p2_write(command);
	p3_stop();
}

void TM16XX::p2_data(uint8_t command, uint8_t data)
{
	p2_start();
	p2_write(command);
	p2_ack();
	p2_write(data);
	p2_ack();
	p2_stop();
}

void TM16XX::p3_data(uint8_t command, uint8_t data)
{
	p3_start();
	p2_write(command);
	p2_write(data);
	p3_stop();
}

void TM16XX::Clear(void)
{
	switch (_IC.if_type)
	{
		case TM16XX_IF_TYPE_P2:
			p2_command(TM16XX_COMMAND_DATA_SET | TM16XX_DATA_AUTOINC | TM16XX_DATA_WRITE);

			p2_start();
			p2_write(TM16XX_COMMAND_ADDRESS);
			p2_ack();

			for (uint8_t i = 0; i < _IC.display_buff_len; i++)
			{
				p2_write(0);
				p2_ack();
			}
			p2_stop();

			p2_command(TM16XX_COMMAND_CONTROL | (_DisplayOn ? TM16XX_CONTROL_ON : TM16XX_CONTROL_OFF) | _Brightness);
			break;
		case TM16XX_IF_TYPE_P3:
			p3_command(TM16XX_COMMAND_DATA_SET | TM16XX_DATA_AUTOINC | TM16XX_DATA_WRITE);

			p3_start();
			p2_write(TM16XX_COMMAND_ADDRESS);
			for (uint8_t i = 0; i < _IC.display_buff_len; i++)
			{
				p2_write(0);
			}
			p3_stop();

			p3_command(TM16XX_COMMAND_CONTROL | (_DisplayOn ? TM16XX_CONTROL_ON : TM16XX_CONTROL_OFF) | _Brightness);

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
			p3_command(TM16XX_COMMAND_DATA_SET);
			p3_data(TM16XX_COMMAND_ADDRESS | addr, data);
			p3_command(TM16XX_COMMAND_CONTROL | (_DisplayOn ? TM16XX_CONTROL_ON : TM16XX_CONTROL_OFF) | _Brightness);
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
		p2_write(TM16XX_COMMAND_ADDRESS | addr);
		p2_ack();
		for (uint8_t i = 0; i < len; i++)
		{
			p2_write(data[i]);
			p2_ack();
		}
		p2_stop();

		p2_command(TM16XX_COMMAND_CONTROL | (_DisplayOn ? TM16XX_CONTROL_ON : TM16XX_CONTROL_OFF) | _Brightness);
		break;
	case TM16XX_IF_TYPE_P3:
		p3_command(TM16XX_COMMAND_DATA_SET | TM16XX_DATA_AUTOINC | TM16XX_DATA_WRITE);

		p3_start();
		p2_write(TM16XX_COMMAND_ADDRESS | addr);
		for (uint8_t i = 0; i < len; i++)
		{
			p2_write(data[i]);
		}
		p3_stop();

		p3_command(TM16XX_COMMAND_CONTROL | (_DisplayOn ? TM16XX_CONTROL_ON : TM16XX_CONTROL_OFF) | _Brightness);

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
/*
void TM16XX::DisplayNum(uint8_t addr, bool leadingzero, uint8_t displaylen, uint8_t data)
{
	for (int i = displaylen - 1; i >= 0; i--)
	{
		DisplayBin((addr + i) << _IC.buff_word_width, (leadingzero || data != 0) ? HexChars[data % 10] : 0);
		data /= 10;
	}
}
*/