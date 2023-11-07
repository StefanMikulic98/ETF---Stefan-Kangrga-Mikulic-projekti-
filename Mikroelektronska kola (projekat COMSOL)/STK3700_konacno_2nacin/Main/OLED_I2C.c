/*
 OLED_I2C.cpp - Arduino/chipKit library support for 128x64 pixel SSD1306 OLEDs
 Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved

 This library has been made to make it easy to use 128x64 pixel OLED displays
 based on the SSD1306 controller chip with an Arduino or a chipKit.

 You can always find the latest version of the library at
 http://www.RinkyDinkElectronics.com/

 This library is free software; you can redistribute it and/or
 modify it under the terms of the CC BY-NC-SA 3.0 license.
 Please see the included documents for further information.

 Commercial use of this library requires you to buy a license that
 will allow commercial use. This includes using the library,
 modified or not, as a tool to sell products.

 The license applies to all part of the library including the
 examples and tools supplied with the library.
 */
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "em_device.h"
#include "em_chip.h"
#include "em_i2c.h"
#include "em_rtc.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "udelay.h"

typedef _Bool boolean;
typedef __uint8_t byte;
typedef __uint8_t uint8_t;
typedef __uint16_t uint16_t;

/*
  WString.h - String library for Wiring & Arduino
  ...mostly rewritten by Paul Stoffregen...
  Copyright (c) 2009-10 Hernando Barragan.  All right reserved.
  Copyright 2011, Paul Stoffregen, paul@pjrc.com

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef String_class_h
#define String_class_h
#ifdef __cplusplus

// When compiling programs with this class, the following gcc parameters
// dramatically increase performance and memory (RAM) efficiency, typically
// with little or no increase in code size.
//     -felide-constructors
//     -std=c++0x

class __FlashStringHelper;
#define F(string_literal) (reinterpret_cast<const __FlashStringHelper *>(PSTR(string_literal)))

// An inherited class for holding the result of a concatenation.  These
// result objects are assumed to be writable by subsequent concatenations.
class StringSumHelper;

// The string class
class String
{
	// use a function pointer to allow for "if (s)" without the
	// complications of an operator bool(). for more information, see:
	// http://www.artima.com/cppsource/safebool.html
	typedef void (String::*StringIfHelperType)() const;
	void StringIfHelper() const {}

public:
	// constructors
	// creates a copy of the initial value.
	// if the initial value is null or invalid, or if memory allocation
	// fails, the string will be marked as invalid (i.e. "if (s)" will
	// be false).
	String(const char *cstr = "");
	String(const String &str);
	String(const __FlashStringHelper *str);
       #if __cplusplus >= 201103L || defined(__GXX_EXPERIMENTAL_CXX0X__)
	String(String &&rval);
	String(StringSumHelper &&rval);
	#endif
	explicit String(char c);
	explicit String(unsigned char, unsigned char base=10);
	explicit String(int, unsigned char base=10);
	explicit String(unsigned int, unsigned char base=10);
	explicit String(long, unsigned char base=10);
	explicit String(unsigned long, unsigned char base=10);
	explicit String(float, unsigned char decimalPlaces=2);
	explicit String(double, unsigned char decimalPlaces=2);
	~String(void);

	// memory management
	// return true on success, false on failure (in which case, the string
	// is left unchanged).  reserve(0), if successful, will validate an
	// invalid string (i.e., "if (s)" will be true afterwards)
	unsigned char reserve(unsigned int size);
	inline unsigned int length(void) const {return len;}

	// creates a copy of the assigned value.  if the value is null or
	// invalid, or if the memory allocation fails, the string will be
	// marked as invalid ("if (s)" will be false).
	String & operator = (const String &rhs);
	String & operator = (const char *cstr);
	String & operator = (const __FlashStringHelper *str);
       #if __cplusplus >= 201103L || defined(__GXX_EXPERIMENTAL_CXX0X__)
	String & operator = (String &&rval);
	String & operator = (StringSumHelper &&rval);
	#endif

	// concatenate (works w/ built-in types)

	// returns true on success, false on failure (in which case, the string
	// is left unchanged).  if the argument is null or invalid, the
	// concatenation is considered unsucessful.
	unsigned char concat(const String &str);
	unsigned char concat(const char *cstr);
	unsigned char concat(char c);
	unsigned char concat(unsigned char c);
	unsigned char concat(int num);
	unsigned char concat(unsigned int num);
	unsigned char concat(long num);
	unsigned char concat(unsigned long num);
	unsigned char concat(float num);
	unsigned char concat(double num);
	unsigned char concat(const __FlashStringHelper * str);

	// if there's not enough memory for the concatenated value, the string
	// will be left unchanged (but this isn't signalled in any way)
	String & operator += (const String &rhs)	{concat(rhs); return (*this);}
	String & operator += (const char *cstr)		{concat(cstr); return (*this);}
	String & operator += (char c)			{concat(c); return (*this);}
	String & operator += (unsigned char num)		{concat(num); return (*this);}
	String & operator += (int num)			{concat(num); return (*this);}
	String & operator += (unsigned int num)		{concat(num); return (*this);}
	String & operator += (long num)			{concat(num); return (*this);}
	String & operator += (unsigned long num)	{concat(num); return (*this);}
	String & operator += (float num)		{concat(num); return (*this);}
	String & operator += (double num)		{concat(num); return (*this);}
	String & operator += (const __FlashStringHelper *str){concat(str); return (*this);}

	friend StringSumHelper & operator + (const StringSumHelper &lhs, const String &rhs);
	friend StringSumHelper & operator + (const StringSumHelper &lhs, const char *cstr);
	friend StringSumHelper & operator + (const StringSumHelper &lhs, char c);
	friend StringSumHelper & operator + (const StringSumHelper &lhs, unsigned char num);
	friend StringSumHelper & operator + (const StringSumHelper &lhs, int num);
	friend StringSumHelper & operator + (const StringSumHelper &lhs, unsigned int num);
	friend StringSumHelper & operator + (const StringSumHelper &lhs, long num);
	friend StringSumHelper & operator + (const StringSumHelper &lhs, unsigned long num);
	friend StringSumHelper & operator + (const StringSumHelper &lhs, float num);
	friend StringSumHelper & operator + (const StringSumHelper &lhs, double num);
	friend StringSumHelper & operator + (const StringSumHelper &lhs, const __FlashStringHelper *rhs);

	// comparison (only works w/ Strings and "strings")
	operator StringIfHelperType() const { return buffer ? &String::StringIfHelper : 0; }
	int compareTo(const String &s) const;
	unsigned char equals(const String &s) const;
	unsigned char equals(const char *cstr) const;
	unsigned char operator == (const String &rhs) const {return equals(rhs);}
	unsigned char operator == (const char *cstr) const {return equals(cstr);}
	unsigned char operator != (const String &rhs) const {return !equals(rhs);}
	unsigned char operator != (const char *cstr) const {return !equals(cstr);}
	unsigned char operator <  (const String &rhs) const;
	unsigned char operator >  (const String &rhs) const;
	unsigned char operator <= (const String &rhs) const;
	unsigned char operator >= (const String &rhs) const;
	unsigned char equalsIgnoreCase(const String &s) const;
	unsigned char startsWith( const String &prefix) const;
	unsigned char startsWith(const String &prefix, unsigned int offset) const;
	unsigned char endsWith(const String &suffix) const;

	// character acccess
	char charAt(unsigned int index) const;
	void setCharAt(unsigned int index, char c);
	char operator [] (unsigned int index) const;
	char& operator [] (unsigned int index);
	void getBytes(unsigned char *buf, unsigned int bufsize, unsigned int index=0) const;
	void toCharArray(char *buf, unsigned int bufsize, unsigned int index=0) const
		{ getBytes((unsigned char *)buf, bufsize, index); }
	const char* c_str() const { return buffer; }
	char* begin() { return buffer; }
	char* end() { return buffer + length(); }
	const char* begin() const { return c_str(); }
	const char* end() const { return c_str() + length(); }

	// search
	int indexOf( char ch ) const;
	int indexOf( char ch, unsigned int fromIndex ) const;
	int indexOf( const String &str ) const;
	int indexOf( const String &str, unsigned int fromIndex ) const;
	int lastIndexOf( char ch ) const;
	int lastIndexOf( char ch, unsigned int fromIndex ) const;
	int lastIndexOf( const String &str ) const;
	int lastIndexOf( const String &str, unsigned int fromIndex ) const;
	String substring( unsigned int beginIndex ) const { return substring(beginIndex, len); };
	String substring( unsigned int beginIndex, unsigned int endIndex ) const;

	// modification
	void replace(char find, char replace);
	void replace(const String& find, const String& replace);
	void remove(unsigned int index);
	void remove(unsigned int index, unsigned int count);
	void toLowerCase(void);
	void toUpperCase(void);
	void trim(void);

	// parsing/conversion
	long toInt(void) const;
	float toFloat(void) const;
	double toDouble(void) const;

protected:
	char *buffer;	        // the actual char array
	unsigned int capacity;  // the array length minus one (for the '\0')
	unsigned int len;       // the String length (not counting the '\0')
protected:
	void init(void);
	void invalidate(void);
	unsigned char changeBuffer(unsigned int maxStrLen);
	unsigned char concat(const char *cstr, unsigned int length);

	// copy and move
	String & copy(const char *cstr, unsigned int length);
	String & copy(const __FlashStringHelper *pstr, unsigned int length);
       #if __cplusplus >= 201103L || defined(__GXX_EXPERIMENTAL_CXX0X__)
	void move(String &rhs);
	#endif
};

class StringSumHelper : public String
{
public:
	StringSumHelper(const String &s) : String(s) {}
	StringSumHelper(const char *p) : String(p) {}
	StringSumHelper(char c) : String(c) {}
	StringSumHelper(unsigned char num) : String(num) {}
	StringSumHelper(int num) : String(num) {}
	StringSumHelper(unsigned int num) : String(num) {}
	StringSumHelper(long num) : String(num) {}
	StringSumHelper(unsigned long num) : String(num) {}
	StringSumHelper(float num) : String(num) {}
	StringSumHelper(double num) : String(num) {}
};

#endif  // __cplusplus
#endif  // String_class_h

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2
#define LOW 0
#define HIGH 1
#define LSBFIRST 0
#define MSBFIRST 1

#define CHANGE 1
#define FALLING 2
#define RISING 3

void pinMode(uint8_t pin, uint8_t type);
void digitalWrite(uint8_t pin, uint8_t type);
int  digitalRead(uint8_t pin);
void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val);
void delay(int n);

#define A0_PORT gpioPortD
#define A0_PIN  0
#define A1_PORT gpioPortD
#define A1_PIN  1
#define A2_PORT gpioPortD
#define A2_PIN  2
#define A3_PORT gpioPortD
#define A3_PIN  3
#define A4_PORT gpioPortD
#define A4_PIN  4
#define A5_PORT gpioPortD
#define A5_PIN  5
#define A6_PORT gpioPortD
#define A6_PIN  6
#define A7_PORT gpioPortD
#define A7_PIN  7
#define A8_PORT gpioPortD
#define A8_PIN  8

#define D20_PORT gpioPortC
#define D20_PIN  4
#define D21_PORT gpioPortC
#define D21_PIN  5

int pin_remap[][2]=
{
		{gpioPortD,0}, //A0
		{gpioPortD,1}, //A1
		{gpioPortD,2}, //A2
		{gpioPortD,3}, //A3
		{gpioPortD,4}, //A4
		{gpioPortD,5}, //A5
		{gpioPortD,6}, //A6
		{gpioPortD,7}, //A7
		{gpioPortD,0}, //A8
		{gpioPortD,0}, //A9
		{gpioPortD,0}, //A10
		{gpioPortD,0}, //A11

		{gpioPortC,0}, //D12
		{gpioPortC,0}, //D13
		{gpioPortC,0}, //D14
		{gpioPortC,0}, //D15
		{gpioPortC,0}, //D16
		{gpioPortC,0}, //D17
		{gpioPortC,0}, //D18
		{gpioPortC,0}, //D19
		{gpioPortC,4}, //D20
		{gpioPortC,5}, //D21

};

void pinMode(uint8_t pin, uint8_t type)
 {
	switch(type)
	{
	 case OUTPUT:
     //GPIO_PinModeSet(pin_remap[pin][0], pin_remap[pin][1], gpioModePushPull, 1);
     GPIO_PinModeSet((GPIO_Port_TypeDef)pin_remap[pin][0], pin_remap[pin][1], gpioModePushPull, 1);
     break;
	 case INPUT:
     //GPIO_PinModeSet(pin_remap[pin][0], pin_remap[pin][1], gpioModePushPull, 1);
     GPIO_PinModeSet((GPIO_Port_TypeDef)pin_remap[pin][0], pin_remap[pin][1], gpioModeInput, 1);
     break;
	 case INPUT_PULLUP:
     //GPIO_PinModeSet(pin_remap[pin][0], pin_remap[pin][1], gpioModePushPull, 1);
     GPIO_PinModeSet((GPIO_Port_TypeDef)pin_remap[pin][0], pin_remap[pin][1], gpioModeInputPull, 1);
     break;
	}
 }

 void digitalWrite(uint8_t pin, uint8_t value)
  {
   if (value)
	   GPIO_PinOutSet((GPIO_Port_TypeDef)pin_remap[pin][0], pin_remap[pin][1]);
   else
	   GPIO_PinOutClear((GPIO_Port_TypeDef)pin_remap[pin][0], pin_remap[pin][1]);
  }

 int digitalRead(uint8_t pin)
  {
	return(GPIO_PinInGet((GPIO_Port_TypeDef)pin_remap[pin][0], pin_remap[pin][1]));
  }

 void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val)
 {
     uint8_t i;

     for (i = 0; i < 8; i++)  {
           if (bitOrder == LSBFIRST)
                 digitalWrite(dataPin, !!(val & (1 << i)));
           else
                 digitalWrite(dataPin, !!(val & (1 << (7 - i))));

           digitalWrite(clockPin, HIGH);
           digitalWrite(clockPin, LOW);
     }
 }

 void delay(int n)
 {
	 UDELAY_Calibrate();
	 UDELAY_Delay(n*1000);
 }



#include "OLED_I2C.h"
#include <stdio.h>

 // *** Hardwarespecific defines ***
 #define cbi(reg, bitmask) *reg &= ~bitmask
 #define sbi(reg, bitmask) *reg |= bitmask
 #define pulseClock cbi(P_SCK, B_SCK); asm ("nop"); sbi(P_SCK, B_SCK)

 #define fontbyte(x) cfont.font[x]
 #define bitmapbyte(x) bitmap[x]

 #define bitmapdatatype unsigned char*

 #define SDA		20
 #define SCL		21
 #define SDA1	70
 #define SCL1	71

 #define TWI_SPEED		TWI_SPEED_400k	// Set default TWI Speed
 #define TWI_SPEED_100k	208
 #define TWI_SPEED_400k	101

 #define TWI_DIV			TWI_DIV_400k	// Set divider for TWI Speed (must match TWI_SPEED setting)
 #define TWI_DIV_100k	1
 #define TWI_DIV_400k	0

		uint8_t			_scl_pin, _sda_pin, _rst_pin;
		boolean			_use_hw;
		struct _current_font	cfont;
		uint8_t			scrbuf[1024];
#define PROGMEM
#define fontdatatype const unsigned char

fontdatatype SmallFont[] PROGMEM =
{
0x06, 0x08, 0x20, 0x5f,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   // sp
0x00, 0x00, 0x00, 0x2f, 0x00, 0x00,   // !
0x00, 0x00, 0x07, 0x00, 0x07, 0x00,   // "
0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14,   // #
0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12,   // $
0x00, 0x23, 0x13, 0x08, 0x64, 0x62,   // %
0x00, 0x36, 0x49, 0x55, 0x22, 0x50,   // &
0x00, 0x00, 0x05, 0x03, 0x00, 0x00,   // '
0x00, 0x00, 0x1c, 0x22, 0x41, 0x00,   // (
0x00, 0x00, 0x41, 0x22, 0x1c, 0x00,   // )
0x00, 0x14, 0x08, 0x3E, 0x08, 0x14,   // *
0x00, 0x08, 0x08, 0x3E, 0x08, 0x08,   // +
0x00, 0x00, 0x00, 0xA0, 0x60, 0x00,   // ,
0x00, 0x08, 0x08, 0x08, 0x08, 0x08,   // -
0x00, 0x00, 0x60, 0x60, 0x00, 0x00,   // .
0x00, 0x20, 0x10, 0x08, 0x04, 0x02,   // /

0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E,   // 0
0x00, 0x00, 0x42, 0x7F, 0x40, 0x00,   // 1
0x00, 0x42, 0x61, 0x51, 0x49, 0x46,   // 2
0x00, 0x21, 0x41, 0x45, 0x4B, 0x31,   // 3
0x00, 0x18, 0x14, 0x12, 0x7F, 0x10,   // 4
0x00, 0x27, 0x45, 0x45, 0x45, 0x39,   // 5
0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30,   // 6
0x00, 0x01, 0x71, 0x09, 0x05, 0x03,   // 7
0x00, 0x36, 0x49, 0x49, 0x49, 0x36,   // 8
0x00, 0x06, 0x49, 0x49, 0x29, 0x1E,   // 9
0x00, 0x00, 0x36, 0x36, 0x00, 0x00,   // :
0x00, 0x00, 0x56, 0x36, 0x00, 0x00,   // ;
0x00, 0x08, 0x14, 0x22, 0x41, 0x00,   // <
0x00, 0x14, 0x14, 0x14, 0x14, 0x14,   // =
0x00, 0x00, 0x41, 0x22, 0x14, 0x08,   // >
0x00, 0x02, 0x01, 0x51, 0x09, 0x06,   // ?

0x00, 0x32, 0x49, 0x59, 0x51, 0x3E,   // @
0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C,   // A
0x00, 0x7F, 0x49, 0x49, 0x49, 0x36,   // B
0x00, 0x3E, 0x41, 0x41, 0x41, 0x22,   // C
0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C,   // D
0x00, 0x7F, 0x49, 0x49, 0x49, 0x41,   // E
0x00, 0x7F, 0x09, 0x09, 0x09, 0x01,   // F
0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A,   // G
0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F,   // H
0x00, 0x00, 0x41, 0x7F, 0x41, 0x00,   // I
0x00, 0x20, 0x40, 0x41, 0x3F, 0x01,   // J
0x00, 0x7F, 0x08, 0x14, 0x22, 0x41,   // K
0x00, 0x7F, 0x40, 0x40, 0x40, 0x40,   // L
0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F,   // M
0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F,   // N
0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E,   // O

0x00, 0x7F, 0x09, 0x09, 0x09, 0x06,   // P
0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E,   // Q
0x00, 0x7F, 0x09, 0x19, 0x29, 0x46,   // R
0x00, 0x46, 0x49, 0x49, 0x49, 0x31,   // S
0x00, 0x01, 0x01, 0x7F, 0x01, 0x01,   // T
0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F,   // U
0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F,   // V
0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F,   // W
0x00, 0x63, 0x14, 0x08, 0x14, 0x63,   // X
0x00, 0x07, 0x08, 0x70, 0x08, 0x07,   // Y
0x00, 0x61, 0x51, 0x49, 0x45, 0x43,   // Z
0x00, 0x00, 0x7F, 0x41, 0x41, 0x00,   // [
0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,   // Backslash (Checker pattern)
0x00, 0x00, 0x41, 0x41, 0x7F, 0x00,   // ]
0x00, 0x04, 0x02, 0x01, 0x02, 0x04,   // ^
0x00, 0x40, 0x40, 0x40, 0x40, 0x40,   // _

0x00, 0x00, 0x03, 0x05, 0x00, 0x00,   // `
0x00, 0x20, 0x54, 0x54, 0x54, 0x78,   // a
0x00, 0x7F, 0x48, 0x44, 0x44, 0x38,   // b
0x00, 0x38, 0x44, 0x44, 0x44, 0x20,   // c
0x00, 0x38, 0x44, 0x44, 0x48, 0x7F,   // d
0x00, 0x38, 0x54, 0x54, 0x54, 0x18,   // e
0x00, 0x08, 0x7E, 0x09, 0x01, 0x02,   // f
0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C,   // g
0x00, 0x7F, 0x08, 0x04, 0x04, 0x78,   // h
0x00, 0x00, 0x44, 0x7D, 0x40, 0x00,   // i
0x00, 0x40, 0x80, 0x84, 0x7D, 0x00,   // j
0x00, 0x7F, 0x10, 0x28, 0x44, 0x00,   // k
0x00, 0x00, 0x41, 0x7F, 0x40, 0x00,   // l
0x00, 0x7C, 0x04, 0x18, 0x04, 0x78,   // m
0x00, 0x7C, 0x08, 0x04, 0x04, 0x78,   // n
0x00, 0x38, 0x44, 0x44, 0x44, 0x38,   // o

0x00, 0xFC, 0x24, 0x24, 0x24, 0x18,   // p
0x00, 0x18, 0x24, 0x24, 0x18, 0xFC,   // q
0x00, 0x7C, 0x08, 0x04, 0x04, 0x08,   // r
0x00, 0x48, 0x54, 0x54, 0x54, 0x20,   // s
0x00, 0x04, 0x3F, 0x44, 0x40, 0x20,   // t
0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C,   // u
0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C,   // v
0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C,   // w
0x00, 0x44, 0x28, 0x10, 0x28, 0x44,   // x
0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C,   // y
0x00, 0x44, 0x64, 0x54, 0x4C, 0x44,   // z
0x00, 0x00, 0x10, 0x7C, 0x82, 0x00,   // {
0x00, 0x00, 0x00, 0xFF, 0x00, 0x00,   // |
0x00, 0x00, 0x82, 0x7C, 0x10, 0x00,   // }
0x00, 0x00, 0x06, 0x09, 0x09, 0x06    // ~ (Degrees)
};

fontdatatype MediumNumbers[] PROGMEM =
{
0x0c, 0x10, 0x2d, 0x0d,
0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00, 0x00,   // -
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,   // .
0x00, 0x00, 0x02, 0x86, 0x86, 0x86, 0x86, 0x86, 0x86, 0x02, 0x00, 0x00, 0x00, 0x00, 0x81, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x81, 0x00, 0x00,   // /
0x00, 0xfc, 0x7a, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x7a, 0xfc, 0x00, 0x00, 0x7e, 0xbc, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xbc, 0x7e, 0x00,   // 0
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x7e, 0x00,   // 1
0x00, 0x00, 0x02, 0x86, 0x86, 0x86, 0x86, 0x86, 0x86, 0x7a, 0xfc, 0x00, 0x00, 0x7e, 0xbd, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x81, 0x00, 0x00,   // 2
0x00, 0x00, 0x02, 0x86, 0x86, 0x86, 0x86, 0x86, 0x86, 0x7a, 0xfc, 0x00, 0x00, 0x00, 0x81, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xbd, 0x7e, 0x00,   // 3
0x00, 0xfc, 0x78, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x78, 0xfc, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x3d, 0x7e, 0x00,   // 4
0x00, 0xfc, 0x7a, 0x86, 0x86, 0x86, 0x86, 0x86, 0x86, 0x02, 0x00, 0x00, 0x00, 0x00, 0x81, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xbd, 0x7e, 0x00,   // 5
0x00, 0xfc, 0x7a, 0x86, 0x86, 0x86, 0x86, 0x86, 0x86, 0x02, 0x00, 0x00, 0x00, 0x7e, 0xbd, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xbd, 0x7e, 0x00,   // 6
0x00, 0x00, 0x02, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x7a, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x7e, 0x00,   // 7
0x00, 0xfc, 0x7a, 0x86, 0x86, 0x86, 0x86, 0x86, 0x86, 0x7a, 0xfc, 0x00, 0x00, 0x7e, 0xbd, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xbd, 0x7e, 0x00,   // 8
0x00, 0xfc, 0x7a, 0x86, 0x86, 0x86, 0x86, 0x86, 0x86, 0x7a, 0xfc, 0x00, 0x00, 0x00, 0x81, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xbd, 0x7e, 0x00,   // 9
};

fontdatatype BigNumbers[] PROGMEM =
{
0x0e, 0x18, 0x2d, 0x0d,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   // -
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xe0, 0xe0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,   // .
0x00, 0x00, 0x02, 0x06, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x06, 0x02, 0x00, 0x00, 0x00, 0x00, 0x10, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x10, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0x80, 0x00, 0x00,   // /
0x00, 0xfc, 0xfa, 0xf6, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0xf6, 0xfa, 0xfc, 0x00, 0x00, 0xef, 0xc7, 0x83, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x83, 0xc7, 0xef, 0x00, 0x00, 0x7f, 0xbf, 0xdf, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xdf, 0xbf, 0x7f, 0x00,   // 0
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf8, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x83, 0xc7, 0xef, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x3f, 0x7f, 0x00,   // 1
0x00, 0x00, 0x02, 0x06, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0xf6, 0xfa, 0xfc, 0x00, 0x00, 0xe0, 0xd0, 0xb8, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x3b, 0x17, 0x0f, 0x00, 0x00, 0x7f, 0xbf, 0xdf, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0x80, 0x00, 0x00,   // 2
0x00, 0x00, 0x02, 0x06, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0xf6, 0xfa, 0xfc, 0x00, 0x00, 0x00, 0x10, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0xbb, 0xd7, 0xef, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xdf, 0xbf, 0x7f, 0x00,   // 3
0x00, 0xfc, 0xf8, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf8, 0xfc, 0x00, 0x00, 0x0f, 0x17, 0x3b, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0xbb, 0xd7, 0xef, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x3f, 0x7f, 0x00,   // 4
0x00, 0xfc, 0xfa, 0xf6, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x06, 0x02, 0x00, 0x00, 0x00, 0x0f, 0x17, 0x3b, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0xb8, 0xd0, 0xe0, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xdf, 0xbf, 0x7f, 0x00,   // 5
0x00, 0xfc, 0xfa, 0xf6, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x06, 0x02, 0x00, 0x00, 0x00, 0xef, 0xd7, 0xbb, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0xb8, 0xd0, 0xe0, 0x00, 0x00, 0x7f, 0xbf, 0xdf, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xdf, 0xbf, 0x7f, 0x00,   // 6
0x00, 0x00, 0x02, 0x06, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0xf6, 0xfa, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x83, 0xc7, 0xef, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x3f, 0x7f, 0x00,   // 7
0x00, 0xfc, 0xfa, 0xf6, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0xf6, 0xfa, 0xfc, 0x00, 0x00, 0xef, 0xd7, 0xbb, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0xbb, 0xd7, 0xef, 0x00, 0x00, 0x7f, 0xbf, 0xdf, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xdf, 0xbf, 0x7f, 0x00,   // 8
0x00, 0xfc, 0xfa, 0xf6, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0xf6, 0xfa, 0xfc, 0x00, 0x00, 0x0f, 0x17, 0x3b, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0xbb, 0xd7, 0xef, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xdf, 0xbf, 0x7f, 0x00,   // 9
};

fontdatatype TinyFont[] PROGMEM =
{
0x04, 0x06, 0x20, 0x5f,
0x00, 0x00, 0x00, 0x03, 0xa0, 0x00, 0xc0, 0x0c, 0x00, 0xf9, 0x4f, 0x80, 0x6b, 0xeb, 0x00, 0x98, 0x8c, 0x80, 0x52, 0xa5, 0x80, 0x03, 0x00, 0x00,  // Space, !"#$%&'
0x01, 0xc8, 0x80, 0x89, 0xc0, 0x00, 0x50, 0x85, 0x00, 0x21, 0xc2, 0x00, 0x08, 0x40, 0x00, 0x20, 0x82, 0x00, 0x00, 0x20, 0x00, 0x18, 0x8c, 0x00,  // ()*+,-./
0xfa, 0x2f, 0x80, 0x4b, 0xe0, 0x80, 0x5a, 0x66, 0x80, 0x8a, 0xa5, 0x00, 0xe0, 0x8f, 0x80, 0xea, 0xab, 0x00, 0x72, 0xa9, 0x00, 0x9a, 0x8c, 0x00,  // 01234567
0xfa, 0xaf, 0x80, 0x4a, 0xa7, 0x00, 0x01, 0x40, 0x00, 0x09, 0x40, 0x00, 0x21, 0x48, 0x80, 0x51, 0x45, 0x00, 0x89, 0x42, 0x00, 0x42, 0x66, 0x00,  // 89:;<=>?
0x72, 0xa6, 0x80, 0x7a, 0x87, 0x80, 0xfa, 0xa5, 0x00, 0x72, 0x25, 0x00, 0xfa, 0x27, 0x00, 0xfa, 0xa8, 0x80, 0xfa, 0x88, 0x00, 0x72, 0x2b, 0x00,  // @ABCDEFG
0xf8, 0x8f, 0x80, 0x8b, 0xe8, 0x80, 0x8b, 0xe8, 0x00, 0xf8, 0x8d, 0x80, 0xf8, 0x20, 0x80, 0xf9, 0x0f, 0x80, 0xf9, 0xcf, 0x80, 0x72, 0x27, 0x00,  // HIJKLMNO
0xfa, 0x84, 0x00, 0x72, 0x27, 0x40, 0xfa, 0x85, 0x80, 0x4a, 0xa9, 0x00, 0x83, 0xe8, 0x00, 0xf0, 0x2f, 0x00, 0xe0, 0x6e, 0x00, 0xf0, 0xef, 0x00,  // PQRSTUVW
0xd8, 0x8d, 0x80, 0xc0, 0xec, 0x00, 0x9a, 0xac, 0x80, 0x03, 0xe8, 0x80, 0xc0, 0x81, 0x80, 0x8b, 0xe0, 0x00, 0x42, 0x04, 0x00, 0x08, 0x20, 0x80,  // XYZ[\]^_
0x02, 0x04, 0x00, 0x31, 0x23, 0x80, 0xf9, 0x23, 0x00, 0x31, 0x24, 0x80, 0x31, 0x2f, 0x80, 0x31, 0x62, 0x80, 0x23, 0xea, 0x00, 0x25, 0x53, 0x80,  // `abcdefg
0xf9, 0x03, 0x80, 0x02, 0xe0, 0x00, 0x06, 0xe0, 0x00, 0xf8, 0x42, 0x80, 0x03, 0xe0, 0x00, 0x79, 0x87, 0x80, 0x39, 0x03, 0x80, 0x31, 0x23, 0x00,  // hijklmno
0x7d, 0x23, 0x00, 0x31, 0x27, 0xc0, 0x78, 0x84, 0x00, 0x29, 0x40, 0x00, 0x43, 0xe4, 0x00, 0x70, 0x27, 0x00, 0x60, 0x66, 0x00, 0x70, 0x67, 0x00,  // pqrstuvw
0x48, 0xc4, 0x80, 0x74, 0x57, 0x80, 0x59, 0xe6, 0x80, 0x23, 0xe8, 0x80, 0x03, 0x60, 0x00, 0x8b, 0xe2, 0x00, 0x61, 0x0c, 0x00                     // zyx{|}~
};

void OLEDI2C_convert_float(char *buf, double num, int width, byte prec)
{
	char format[10];

	sprintf(format, "%%%i.%if", width, prec);
	sprintf(buf, format, num);
}

void OLEDI2C_begin()
{
	_scl_pin=21;
	_sda_pin=20;
	_rst_pin=RST_NOT_IN_USE;
	_use_hw=false;

	if (_rst_pin != RST_NOT_IN_USE)
	{
		pinMode(_rst_pin, OUTPUT);
		digitalWrite(_rst_pin, HIGH);
		//delay(1);
		digitalWrite(_rst_pin, LOW);
		//delay(10);
		digitalWrite(_rst_pin, HIGH);
	}

	if ((_sda_pin == SDA) && (_scl_pin == SCL))
	{
		//_use_hw = true;
		_use_hw = false;
		OLEDI2C_initTWI();
	}
	else
	{
		_use_hw = false;
		pinMode(_scl_pin, OUTPUT);
	}

	OLEDI2C_sendTWIcommand(SSD1306_DISPLAY_OFF);
	OLEDI2C_sendTWIcommand(SSD1306_SET_DISPLAY_CLOCK_DIV_RATIO);
	OLEDI2C_sendTWIcommand(0x80);
	OLEDI2C_sendTWIcommand(SSD1306_SET_MULTIPLEX_RATIO);
	OLEDI2C_sendTWIcommand(0x3F);
	OLEDI2C_sendTWIcommand(SSD1306_SET_DISPLAY_OFFSET);
	OLEDI2C_sendTWIcommand(0x0);
	OLEDI2C_sendTWIcommand(SSD1306_SET_START_LINE | 0x0);
	OLEDI2C_sendTWIcommand(SSD1306_CHARGE_PUMP);
	OLEDI2C_sendTWIcommand(0x14);
	OLEDI2C_sendTWIcommand(SSD1306_MEMORY_ADDR_MODE);
	OLEDI2C_sendTWIcommand(0x00);
	OLEDI2C_sendTWIcommand(SSD1306_SET_SEGMENT_REMAP | 0x1);
	OLEDI2C_sendTWIcommand(SSD1306_COM_SCAN_DIR_DEC);
	OLEDI2C_sendTWIcommand(SSD1306_SET_COM_PINS);
	OLEDI2C_sendTWIcommand(0x12);
	OLEDI2C_sendTWIcommand(SSD1306_SET_CONTRAST_CONTROL);
	OLEDI2C_sendTWIcommand(0xCF);
	OLEDI2C_sendTWIcommand(SSD1306_SET_PRECHARGE_PERIOD);
	OLEDI2C_sendTWIcommand(0xF1);
	OLEDI2C_sendTWIcommand(SSD1306_SET_VCOM_DESELECT);
	OLEDI2C_sendTWIcommand(0x40);
	OLEDI2C_sendTWIcommand(SSD1306_DISPLAY_ALL_ON_RESUME);
	OLEDI2C_sendTWIcommand(SSD1306_NORMAL_DISPLAY);
	OLEDI2C_sendTWIcommand(SSD1306_DISPLAY_ON);

	OLEDI2C_clrScr();
	OLEDI2C_update();
	cfont.font = 0;
}

void OLEDI2C_clrScr() {
	memset(scrbuf, 0, 1024);
}

void OLEDI2C_fillScr() {
	memset(scrbuf, 255, 1024);
}

void OLEDI2C_setBrightness(uint8_t value) {
	OLEDI2C_sendTWIcommand(SSD1306_SET_CONTRAST_CONTROL);
	OLEDI2C_sendTWIcommand(value);
}

void OLEDI2C_invert(bool mode) {
	if (mode == true)
		OLEDI2C_sendTWIcommand(SSD1306_INVERT_DISPLAY);
	else
		OLEDI2C_sendTWIcommand(SSD1306_NORMAL_DISPLAY);
}

void OLEDI2C_setPixel(uint16_t x, uint16_t y) {
	int by, bi;

	if ((x >= 0) && (x < 128) && (y >= 0) && (y < 64)) {
		by = ((y / 8) * 128) + x;
		bi = y % 8;

		scrbuf[by] = scrbuf[by] | (1 << bi);
	}
}

void OLEDI2C_clrPixel(uint16_t x, uint16_t y) {
	int by, bi;

	if ((x >= 0) && (x < 128) && (y >= 0) && (y < 64)) {
		by = ((y / 8) * 128) + x;
		bi = y % 8;

		scrbuf[by] = scrbuf[by] & ~(1 << bi);
	}
}

void OLEDI2C_invPixel(uint16_t x, uint16_t y) {
	int by, bi;

	if ((x >= 0) && (x < 128) && (y >= 0) && (y < 64)) {
		by = ((y / 8) * 128) + x;
		bi = y % 8;

		if ((scrbuf[by] & (1 << bi)) == 0)
			scrbuf[by] = scrbuf[by] | (1 << bi);
		else
			scrbuf[by] = scrbuf[by] & ~(1 << bi);
	}
}

void OLEDI2C_invertText(bool mode) {
	if (mode == true)
		cfont.inverted = 1;
	else
		cfont.inverted = 0;
}

void OLEDI2C__print_char(unsigned char c, int x, int y) {
	if ((cfont.y_size % 8) == 0) {
		int font_idx =
				((c - cfont.offset) * (cfont.x_size * (cfont.y_size / 8))) + 4;
		for (int rowcnt = 0; rowcnt < (cfont.y_size / 8); rowcnt++) {
			for (int cnt = 0; cnt < cfont.x_size; cnt++) {
				for (int b = 0; b < 8; b++)
					if ((fontbyte(font_idx+cnt+(rowcnt*cfont.x_size))& (1<<b))!=0)
					if (cfont.inverted==0)
					OLEDI2C_setPixel(x+cnt, y+(rowcnt*8)+b);
					else
						OLEDI2C_clrPixel(x+cnt, y+(rowcnt*8)+b);
					else
					if (cfont.inverted==0)
						OLEDI2C_clrPixel(x+cnt, y+(rowcnt*8)+b);
					else
						OLEDI2C_setPixel(x+cnt, y+(rowcnt*8)+b);
				}
			}
		}
		else
		{
			int font_idx = ((c - cfont.offset)*((cfont.x_size*cfont.y_size/8)))+4;
			int cbyte=fontbyte(font_idx);
			int cbit=7;
			for (int cx=0; cx<cfont.x_size; cx++)
			{
				for (int cy=0; cy<cfont.y_size; cy++)
				{
					if ((cbyte & (1<<cbit)) != 0)
					if (cfont.inverted==0)
						OLEDI2C_setPixel(x+cx, y+cy);
					else
						OLEDI2C_clrPixel(x+cx, y+cy);
					else
					if (cfont.inverted==0)
						OLEDI2C_clrPixel(x+cx, y+cy);
					else
						OLEDI2C_setPixel(x+cx, y+cy);
					cbit--;
					if (cbit<0)
					{
						cbit=7;
						font_idx++;
						cbyte=fontbyte(font_idx);
					}
				}
			}
		}
	}

void OLEDI2C_print(char *st, int x, int y) {
	int stl;

	stl = strlen(st);
	if (x == RIGHT)
		x = 128 - (stl * cfont.x_size);
	if (x == CENTER)
		x = (128 - (stl * cfont.x_size)) / 2;

	for (int cnt = 0; cnt < stl; cnt++)
		OLEDI2C__print_char(*st++, x + (cnt * (cfont.x_size)), y);
}

void OLEDI2C_printNumI(long num, int x, int y, int length, char filler) {
	char buf[25];
	char st[27];
	boolean neg = false;
	int c = 0, f = 0;

	if (num == 0) {
		if (length != 0) {
			for (c = 0; c < (length - 1); c++)
				st[c] = filler;
			st[c] = 48;
			st[c + 1] = 0;
		} else {
			st[0] = 48;
			st[1] = 0;
		}
	} else {
		if (num < 0) {
			neg = true;
			num = -num;
		}

		while (num > 0) {
			buf[c] = 48 + (num % 10);
			c++;
			num = (num - (num % 10)) / 10;
		}
		buf[c] = 0;

		if (neg) {
			st[0] = 45;
		}

		if (length > (c + neg)) {
			for (int i = 0; i < (length - c - neg); i++) {
				st[i + neg] = filler;
				f++;
			}
		}

		for (int i = 0; i < c; i++) {
			st[i + neg + f] = buf[c - i - 1];
		}
		st[c + neg + f] = 0;

	}

	OLEDI2C_print(st, x, y);
}

void OLEDI2C_printNumF(double num, byte dec, int x, int y, char divider,
		int length, char filler) {
	char st[27];
	boolean neg = false;

	if (num < 0)
		neg = true;

	OLEDI2C_convert_float(st, num, length, dec);

	if (divider != '.') {
		for (unsigned int i = 0; i < sizeof(st); i++)
			if (st[i] == '.')
				st[i] = divider;
	}

	if (filler != ' ') {
		if (neg) {
			st[0] = '-';
			for (unsigned int i = 1; i < sizeof(st); i++)
				if ((st[i] == ' ') || (st[i] == '-'))
					st[i] = filler;
		} else {
			for (unsigned int i = 0; i < sizeof(st); i++)
				if (st[i] == ' ')
					st[i] = filler;
		}
	}

	OLEDI2C_print(st, x, y);
}

void OLEDI2C_setFont(uint8_t* font) {
	cfont.font = font;
	cfont.x_size = fontbyte(0);
	cfont.y_size = fontbyte(1);
	cfont.offset = fontbyte(2);
	cfont.numchars = fontbyte(3);
	cfont.inverted = 0;
}

void OLEDI2C_drawHLine(int x, int y, int l) {
	int by, bi;

	if ((x >= 0) && (x < 128) && (y >= 0) && (y < 64)) {
		for (int cx = 0; cx < l; cx++) {
			by = ((y / 8) * 128) + x;
			bi = y % 8;

			scrbuf[by + cx] |= (1 << bi);
		}
	}
}

void OLEDI2C_clrHLine(int x, int y, int l) {
	int by, bi;

	if ((x >= 0) && (x < 128) && (y >= 0) && (y < 64)) {
		for (int cx = 0; cx < l; cx++) {
			by = ((y / 8) * 128) + x;
			bi = y % 8;

			scrbuf[by + cx] &= ~(1 << bi);
		}
	}
}

void OLEDI2C_drawVLine(int x, int y, int l) {
	if ((x >= 0) && (x < 128) && (y >= 0) && (y < 64)) {
		for (int cy = 0; cy < l; cy++) {
			OLEDI2C_setPixel(x, y + cy);
		}
	}
}

void OLEDI2C_clrVLine(int x, int y, int l) {
	if ((x >= 0) && (x < 128) && (y >= 0) && (y < 64)) {
		for (int cy = 0; cy < l; cy++) {
			OLEDI2C_clrPixel(x, y + cy);
		}
	}
}

void OLEDI2C_drawLine(int x1, int y1, int x2, int y2) {
	int tmp;
	double delta, tx, ty;

	if (((x2 - x1) < 0)) {
		tmp = x1;
		x1 = x2;
		x2 = tmp;
		tmp = y1;
		y1 = y2;
		y2 = tmp;
	}
	if (((y2 - y1) < 0)) {
		tmp = x1;
		x1 = x2;
		x2 = tmp;
		tmp = y1;
		y1 = y2;
		y2 = tmp;
	}

	if (y1 == y2) {
		if (x1 > x2) {
			tmp = x1;
			x1 = x2;
			x2 = tmp;
		}
		OLEDI2C_drawHLine(x1, y1, x2 - x1);
	} else if (x1 == x2) {
		if (y1 > y2) {
			tmp = y1;
			y1 = y2;
			y2 = tmp;
		}
		OLEDI2C_drawVLine(x1, y1, y2 - y1);
	} else if (abs(x2 - x1) > abs(y2 - y1)) {
		delta = ((double)(y2 - y1) / (double)(x2 - x1));
		ty = (double)(y1);
		if (x1 > x2) {
			for (int i = x1; i >= x2; i--) {
				OLEDI2C_setPixel(i, (int)(ty + 0.5));
				ty = ty - delta;
			}
		} else {
			for (int i = x1; i <= x2; i++) {
				OLEDI2C_setPixel(i, (int)(ty + 0.5));
				ty = ty + delta;
			}
		}
	} else {
		delta = ((float)(x2 - x1) / (float)(y2 - y1));
		tx = (float)(x1);
		if (y1 > y2) {
			for (int i = y2 + 1; i > y1; i--) {
				OLEDI2C_setPixel((int)(tx + 0.5), i);
				tx = tx + delta;
			}
		} else {
			for (int i = y1; i < y2 + 1; i++) {
				OLEDI2C_setPixel((int)(tx + 0.5), i);
				tx = tx + delta;
			}
		}
	}

}

void OLEDI2C_clrLine(int x1, int y1, int x2, int y2) {
	int tmp;
	double delta, tx, ty;

	if (((x2 - x1) < 0)) {
		tmp = x1;
		x1 = x2;
		x2 = tmp;
		tmp = y1;
		y1 = y2;
		y2 = tmp;
	}
	if (((y2 - y1) < 0)) {
		tmp = x1;
		x1 = x2;
		x2 = tmp;
		tmp = y1;
		y1 = y2;
		y2 = tmp;
	}

	if (y1 == y2) {
		if (x1 > x2) {
			tmp = x1;
			x1 = x2;
			x2 = tmp;
		}
		OLEDI2C_clrHLine(x1, y1, x2 - x1);
	} else if (x1 == x2) {
		if (y1 > y2) {
			tmp = y1;
			y1 = y2;
			y2 = tmp;
		}
		OLEDI2C_clrVLine(x1, y1, y2 - y1);
	} else if (abs(x2 - x1) > abs(y2 - y1)) {
		delta = ((double)(y2 - y1) / (double)(x2 - x1));
		ty = (double)(y1);
		if (x1 > x2) {
			for (int i = x1; i >= x2; i--) {
				OLEDI2C_clrPixel(i, (int)(ty + 0.5));
				ty = ty - delta;
			}
		} else {
			for (int i = x1; i <= x2; i++) {
				OLEDI2C_clrPixel(i, (int)(ty + 0.5));
				ty = ty + delta;
			}
		}
	} else {
		delta = ((float)(x2 - x1) / (float)(y2 - y1));
		tx = (float)(x1);
		if (y1 > y2) {
			for (int i = y2 + 1; i > y1; i--) {
				OLEDI2C_clrPixel((int)(tx + 0.5), i);
				tx = tx + delta;
			}
		} else {
			for (int i = y1; i < y2 + 1; i++) {
				OLEDI2C_clrPixel((int)(tx + 0.5), i);
				tx = tx + delta;
			}
		}
	}

}

void OLEDI2C_drawRect(int x1, int y1, int x2, int y2) {
	int tmp;

	if (x1 > x2) {
		tmp = x1;
		x1 = x2;
		x2 = tmp;
	}
	if (y1 > y2) {
		tmp = y1;
		y1 = y2;
		y2 = tmp;
	}

	OLEDI2C_drawHLine(x1, y1, x2 - x1);
	OLEDI2C_drawHLine(x1, y2, x2 - x1);
	OLEDI2C_drawVLine(x1, y1, y2 - y1);
	OLEDI2C_drawVLine(x2, y1, y2 - y1 + 1);
}

void OLEDI2C_clrRect(int x1, int y1, int x2, int y2) {
	int tmp;

	if (x1 > x2) {
		tmp = x1;
		x1 = x2;
		x2 = tmp;
	}
	if (y1 > y2) {
		tmp = y1;
		y1 = y2;
		y2 = tmp;
	}

	OLEDI2C_clrHLine(x1, y1, x2 - x1);
	OLEDI2C_clrHLine(x1, y2, x2 - x1);
	OLEDI2C_clrVLine(x1, y1, y2 - y1);
	OLEDI2C_clrVLine(x2, y1, y2 - y1 + 1);
}

void OLEDI2C_drawRoundRect(int x1, int y1, int x2, int y2) {
	int tmp;

	if (x1 > x2) {
		tmp = x1;
		x1 = x2;
		x2 = tmp;
	}
	if (y1 > y2) {
		tmp = y1;
		y1 = y2;
		y2 = tmp;
	}
	if ((x2 - x1) > 4 && (y2 - y1) > 4) {
		OLEDI2C_setPixel(x1 + 1, y1 + 1);
		OLEDI2C_setPixel(x2 - 1, y1 + 1);
		OLEDI2C_setPixel(x1 + 1, y2 - 1);
		OLEDI2C_setPixel(x2 - 1, y2 - 1);
		OLEDI2C_drawHLine(x1 + 2, y1, x2 - x1 - 3);
		OLEDI2C_drawHLine(x1 + 2, y2, x2 - x1 - 3);
		OLEDI2C_drawVLine(x1, y1 + 2, y2 - y1 - 3);
		OLEDI2C_drawVLine(x2, y1 + 2, y2 - y1 - 3);
	}
}

void OLEDI2C_clrRoundRect(int x1, int y1, int x2, int y2) {
	int tmp;

	if (x1 > x2) {
		tmp = x1;
		x1 = x2;
		x2 = tmp;
	}
	if (y1 > y2) {
		tmp = y1;
		y1 = y2;
		y2 = tmp;
	}
	if ((x2 - x1) > 4 && (y2 - y1) > 4) {
		OLEDI2C_clrPixel(x1 + 1, y1 + 1);
		OLEDI2C_clrPixel(x2 - 1, y1 + 1);
		OLEDI2C_clrPixel(x1 + 1, y2 - 1);
		OLEDI2C_clrPixel(x2 - 1, y2 - 1);
		OLEDI2C_clrHLine(x1 + 2, y1, x2 - x1 - 3);
		OLEDI2C_clrHLine(x1 + 2, y2, x2 - x1 - 3);
		OLEDI2C_clrVLine(x1, y1 + 2, y2 - y1 - 3);
		OLEDI2C_clrVLine(x2, y1 + 2, y2 - y1 - 3);
	}
}

void OLEDI2C_drawCircle(int x, int y, int radius) {
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x1 = 0;
	int y1 = radius;

	OLEDI2C_setPixel(x, y + radius);
	OLEDI2C_setPixel(x, y - radius);
	OLEDI2C_setPixel(x + radius, y);
	OLEDI2C_setPixel(x - radius, y);

	while (x1 < y1) {
		if (f >= 0) {
			y1--;
			ddF_y += 2;
			f += ddF_y;
		}
		x1++;
		ddF_x += 2;
		f += ddF_x;
		OLEDI2C_setPixel(x + x1, y + y1);
		OLEDI2C_setPixel(x - x1, y + y1);
		OLEDI2C_setPixel(x + x1, y - y1);
		OLEDI2C_setPixel(x - x1, y - y1);
		OLEDI2C_setPixel(x + y1, y + x1);
		OLEDI2C_setPixel(x - y1, y + x1);
		OLEDI2C_setPixel(x + y1, y - x1);
		OLEDI2C_setPixel(x - y1, y - x1);
	}
}

void OLEDI2C_clrCircle(int x, int y, int radius) {
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x1 = 0;
	int y1 = radius;

	OLEDI2C_clrPixel(x, y + radius);
	OLEDI2C_clrPixel(x, y - radius);
	OLEDI2C_clrPixel(x + radius, y);
	OLEDI2C_clrPixel(x - radius, y);

	while (x1 < y1) {
		if (f >= 0) {
			y1--;
			ddF_y += 2;
			f += ddF_y;
		}
		x1++;
		ddF_x += 2;
		f += ddF_x;
		OLEDI2C_clrPixel(x + x1, y + y1);
		OLEDI2C_clrPixel(x - x1, y + y1);
		OLEDI2C_clrPixel(x + x1, y - y1);
		OLEDI2C_clrPixel(x - x1, y - y1);
		OLEDI2C_clrPixel(x + y1, y + x1);
		OLEDI2C_clrPixel(x - y1, y + x1);
		OLEDI2C_clrPixel(x + y1, y - x1);
		OLEDI2C_clrPixel(x - y1, y - x1);
	}
}

void OLEDI2C_drawBitmap(int x, int y, uint8_t* bitmap, int sx, int sy) {
	int bit;
	byte data;

	for (int cy = 0; cy < sy; cy++) {
		bit = cy % 8;
		for (int cx = 0; cx < sx; cx++) {
			data = bitmapbyte(cx + ((cy / 8) * sx));
			if ((data & (1 << bit)) > 0)
				OLEDI2C_setPixel(x + cx, y + cy);
			else
				OLEDI2C_clrPixel(x + cx, y + cy);
		}
	}
}

// Private

void OLEDI2C_sendStart(byte addr) {
	pinMode(_sda_pin, OUTPUT);
	digitalWrite(_sda_pin, HIGH);
	digitalWrite(_scl_pin, HIGH);
	digitalWrite(_sda_pin, LOW);
	digitalWrite(_scl_pin, LOW);
	shiftOut(_sda_pin, _scl_pin, MSBFIRST, addr);
}

void OLEDI2C_sendStop() {
	pinMode(_sda_pin, OUTPUT);
	digitalWrite(_sda_pin, LOW);
	digitalWrite(_scl_pin, HIGH);
	digitalWrite(_sda_pin, HIGH);
	pinMode(_sda_pin, INPUT);
}

void OLEDI2C_sendNack() {
	pinMode(_sda_pin, OUTPUT);
	digitalWrite(_scl_pin, LOW);
	digitalWrite(_sda_pin, HIGH);
	digitalWrite(_scl_pin, HIGH);
	digitalWrite(_scl_pin, LOW);
	pinMode(_sda_pin, INPUT);
}

void OLEDI2C_sendAck() {
	pinMode(_sda_pin, OUTPUT);
	digitalWrite(_scl_pin, LOW);
	digitalWrite(_sda_pin, LOW);
	digitalWrite(_scl_pin, HIGH);
	digitalWrite(_scl_pin, LOW);
	pinMode(_sda_pin, INPUT);
}

void OLEDI2C_waitForAck() {
	pinMode(_sda_pin, INPUT);
	digitalWrite(_scl_pin, HIGH);
	while (digitalRead(_sda_pin) == HIGH) {
	}
	digitalWrite(_scl_pin, LOW);
}

void OLEDI2C_writeByte(uint8_t value) {
	pinMode(_sda_pin, OUTPUT);
	shiftOut(_sda_pin, _scl_pin, MSBFIRST, value);
}

/**************************************************************************************************************************/
/**************************************************************************************************************************/
/* I2C */
/**************************************************************************************************************************/
/**************************************************************************************************************************/

/* Defines*/
#define CORE_FREQUENCY              14000000
#define I2C_ADDRESS                     0xE2
#define I2C_TXBUFFER_SIZE                 1024
#define I2C_RXBUFFER_SIZE                 1024

// Buffers++
uint8_t i2c_txBuffer[I2C_TXBUFFER_SIZE];
uint8_t i2c_rxBuffer[I2C_RXBUFFER_SIZE];
uint8_t i2c_rxBufferIndex;

// Transmission flags
volatile bool i2c_rxInProgress;
volatile bool i2c_startTx;
//extern I2C_TransferReturn_TypeDef I2C_Status;

/**************************************************************************//**
 * @brief  Starting oscillators and enabling clocks
 *****************************************************************************/
void setupOscillators(void) {
	/* Enabling clock to the I2C, GPIO, LE */
	CMU_ClockEnable(cmuClock_I2C1, true);
	CMU_ClockEnable(cmuClock_GPIO, true);
	CMU_ClockEnable(cmuClock_CORELE, true);

	/* Starting LFXO and waiting until it is stable */
	CMU_OscillatorEnable(cmuOsc_LFXO, true, true);
}

/**************************************************************************//**
 * @brief  Transmitting I2C data. Will busy-wait until the transfer is complete.
 *****************************************************************************/
void OLEDI2C_sendTWIcommand(uint8_t value) {
	I2C_TransferReturn_TypeDef I2C_Status;

	/* Transfer structure */
	I2C_TransferSeq_TypeDef i2cTransfer;

	if (_use_hw)
	{
		/* Setting pin to indicate transfer */
		GPIO_PinOutSet(gpioPortC, 0);

		/* Initializing I2C transfer */
		i2cTransfer.addr = SSD1306_ADDR;
		i2cTransfer.flags = I2C_FLAG_WRITE;
		i2c_txBuffer[0] = SSD1306_COMMAND;
		i2c_txBuffer[1] = value;
		i2cTransfer.buf[0].data = i2c_txBuffer;
		i2cTransfer.buf[0].len = 2;
		i2cTransfer.buf[1].data = i2c_rxBuffer;
		i2cTransfer.buf[1].len = 1; //I2C_RXBUFFER_SIZE;
		I2C_TransferInit(I2C1, &i2cTransfer);

		/* Sending data */
		I2C_Status = i2cTransferInProgress;
		while (I2C_Status == i2cTransferInProgress) {
			I2C_Status = I2C_Transfer(I2C1);
		}

		/* Clearing pin to indicate end of transfer */
		GPIO_PinOutClear(gpioPortC, 0);
	}
	else
	{
		OLEDI2C_sendStart(SSD1306_ADDR << 1);
		OLEDI2C_waitForAck();
		OLEDI2C_writeByte(SSD1306_COMMAND);
		OLEDI2C_waitForAck();
		OLEDI2C_writeByte(value);
		OLEDI2C_waitForAck();
		OLEDI2C_sendStop();
	}
}

void OLEDI2C_update()
{
	OLEDI2C_sendTWIcommand(SSD1306_SET_COLUMN_ADDR);
	OLEDI2C_sendTWIcommand(0);
	OLEDI2C_sendTWIcommand(127);

	OLEDI2C_sendTWIcommand(SSD1306_SET_PAGE_ADDR);
	OLEDI2C_sendTWIcommand(0);
	OLEDI2C_sendTWIcommand(7);

	if (_use_hw)					// Send TWI Start
	{
		//	  /* Transfer structure */
		//	  I2C_TransferSeq_TypeDef i2cTransfer;
		//
		//	  /* Initializing I2C transfer */
		//	  i2cTransfer.addr          = SSD1306_ADDR;
		//	  i2cTransfer.flags         = I2C_FLAG_WRITE;
		//	  i2c_txBuffer[0]=SSD1306_DATA_CONTINUE;
		//	  i2cTransfer.buf[0].data   = scrbuf;
		//	  i2cTransfer.buf[0].len    = 1024;
		//	  i2cTransfer.buf[1].data   = i2c_rxBuffer;
		//	  i2cTransfer.buf[1].len    = I2C_RXBUFFER_SIZE;
		//	  I2C_TransferInit(I2C1, &i2cTransfer);
		//
		//	  /* Sending data */
		//	  while (I2C_Transfer(I2C1) == i2cTransferInProgress){;}
		//
		//	  /* Clearing pin to indicate end of transfer */
		//	  GPIO_PinOutClear(gpioPortC, 0);
	}
	else
	{
		OLEDI2C_sendStart(SSD1306_ADDR << 1);
		OLEDI2C_waitForAck();
		OLEDI2C_writeByte(SSD1306_DATA_CONTINUE);
		OLEDI2C_waitForAck();
	}

	for (int b = 0; b < 1024; b++)		// Send data
		if (_use_hw)
		{
			//	  /* Transfer structure */
			//	  I2C_TransferSeq_TypeDef i2cTransfer;
			//
			//	  /* Initializing I2C transfer */
			//	  i2cTransfer.addr          = SSD1306_ADDR;
			//	  i2cTransfer.flags         = I2C_FLAG_WRITE;
			//	  i2c_txBuffer[0]=SSD1306_DATA_CONTINUE;
			//	  i2cTransfer.buf[0].data   = scrbuf;
			//	  i2cTransfer.buf[0].len    = 1024;
			//	  i2cTransfer.buf[1].data   = i2c_rxBuffer;
			//	  i2cTransfer.buf[1].len    = I2C_RXBUFFER_SIZE;
			//	  I2C_TransferInit(I2C1, &i2cTransfer);
			//
			//	  /* Sending data */
			//	  while (I2C_Transfer(I2C1) == i2cTransferInProgress){;}
			//
			//	  /* Clearing pin to indicate end of transfer */
			//	  GPIO_PinOutClear(gpioPortC, 0);
		}
		else
		{
			OLEDI2C_writeByte(scrbuf[b]);
			OLEDI2C_waitForAck();
		}

	if (_use_hw)					// Send TWI Stop
	{
		// Send STOP condition
//		twi->TWI_CR = TWI_CR_STOP;
//		while ((twi->TWI_SR & TWI_SR_TXCOMP) != TWI_SR_TXCOMP) {
//		};
	}
	else
		OLEDI2C_sendStop();
}

void OLEDI2C_initTWI() {

	// $[Peripheral Clock enables]
	/* Enable clock for I2C1 */
//	CMU_ClockEnable(cmuClock_I2C1, true);
//
//	/* Enable clock for GPIO by default */
//	CMU_ClockEnable(cmuClock_GPIO, true);
//
//	I2C1->ROUTE |= I2C_ROUTE_SCLPEN | I2C_ROUTE_SDAPEN;
//
//	// $[I2C1 initialization]
//	I2C_Init_TypeDef init = I2C_INIT_DEFAULT;
//
//	init.enable = 1;
//	init.master = 1;
//	init.freq = 10000;
//	init.clhr = i2cClockHLRStandard;
//	I2C_Init(I2C1, &init);
	//VARIJANTA 1
//	setupOscillators();
//	CMU_ClockEnable(cmuClock_I2C1, true);
//	I2C_Init_TypeDef init = I2C_INIT_DEFAULT;
//
//	init.enable = 1;
//	init.master = 1;
//	init.freq = I2C_FREQ_STANDARD_MAX;
//	init.clhr = i2cClockHLRStandard;
//	I2C_Init(I2C1, &init);
//	I2C1->ROUTE |= I2C_ROUTE_SCLPEN | I2C_ROUTE_SDAPEN;
//	/* Pin PC4 is configured to Open-drain with pull-up and filter */
//	GPIO->P[2].MODEL = (GPIO->P[2].MODEL & ~_GPIO_P_MODEL_MODE4_MASK)
//			| GPIO_P_MODEL_MODE4_WIREDANDPULLUPFILTER;
//
//	/* Pin PC5 is configured to Open-drain with pull-up and filter */
//	GPIO->P[2].MODEL = (GPIO->P[2].MODEL & ~_GPIO_P_MODEL_MODE5_MASK)
//			| GPIO_P_MODEL_MODE5_WIREDANDPULLUPFILTER;
//VARIJANTA 2
	// Using default settings
	I2C_Init_TypeDef i2cInit = I2C_INIT_DEFAULT;

	/* Using PD6 (SDA) and PD7 (SCL) */
	GPIO_PinModeSet(gpioPortC, 4, gpioModeWiredAndPullUpFilter, 1);
	GPIO_PinModeSet(gpioPortC, 5, gpioModeWiredAndPullUpFilter, 1);

	// Setting up PC0 to indicate transfer direction
	GPIO_PinModeSet(gpioPortC, 0, gpioModePushPull, 0);

	/* Enable pins at location 1 */
	I2C1->ROUTE = I2C_ROUTE_SDAPEN |
	I2C_ROUTE_SCLPEN | (1 << _I2C_ROUTE_LOCATION_SHIFT);
	/* Initializing the I2C */
	I2C_Init(I2C1, &i2cInit);

	/* Setting the status flags and index */
	i2c_rxInProgress = false;
	i2c_startTx = false;
	i2c_rxBufferIndex = 0;

//  /* Setting up to enable slave mode */
//  I2C1->SADDR = I2C_ADDRESS;
//  I2C1->CTRL |= I2C_CTRL_SLAVE | I2C_CTRL_AUTOACK | I2C_CTRL_AUTOSN;
//  enableI2cSlaveInterrupts();
}

