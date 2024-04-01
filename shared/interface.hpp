#ifndef MOCCARDUINO_SHARED_INTERFACE_HPP
#define MOCCARDUINO_SHARED_INTERFACE_HPP

#include "constants.hpp"

#include <algorithm>
#include <cmath>

// https://gcc.gnu.org/wiki/Visibility
#if defined _WIN32 || defined __CYGWIN__
#define LIBRARY_API
#else
  #if __GNUC__ >= 4
	#define LIBRARY_API __attribute__ ((visibility ("default")))
  #else
	#define LIBRARY_API
  #endif
#endif

// Pins

/**
 * Configures the specified pin to behave either as an input or an output.
 * https://www.arduino.cc/reference/en/language/functions/digital-io/pinmode/
 * @param mode Should be INPUT or OUTPUT
 */
LIBRARY_API void pinMode(std::uint8_t pin, std::uint8_t mode);

/**
 * Write a HIGH or a LOW value to a digital pin.
 * https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/
 */
LIBRARY_API void digitalWrite(std::uint8_t pin, std::uint8_t val);

/**
 * Reads the value from a specified digital pin, either HIGH or LOW.
 * https://www.arduino.cc/reference/en/language/functions/digital-io/digitalread/
 */
LIBRARY_API int digitalRead(std::uint8_t pin);

/**
 * Reads the value from the specified analog pin.
 * https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/
 */
LIBRARY_API int analogRead(std::uint8_t pin);

/**
 * Configures the reference voltage used for analog input (i.e. the value used as the top of the input range).
 * https://www.arduino.cc/reference/en/language/functions/analog-io/analogreference/
 */
LIBRARY_API void analogReference(std::uint8_t mode);

/**
 * Writes an analog value (PWM wave) to a pin.
 * https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/
 */
LIBRARY_API void analogWrite(std::uint8_t pin, int val);

// Timing

/**
 * Returns the number of milliseconds passed since the Arduino board began running the current program.
 * https://www.arduino.cc/reference/en/language/functions/time/millis/
 */
LIBRARY_API unsigned long millis(void);

/**
 * Returns the number of microseconds since the Arduino board began running the current program.
 * https://www.arduino.cc/reference/en/language/functions/time/micros/
 */
LIBRARY_API unsigned long micros(void);

/**
 * Pauses the program for the amount of time (in milliseconds) specified as parameter.
 * https://www.arduino.cc/reference/en/language/functions/time/delay/
 */
LIBRARY_API void delay(unsigned long ms);

/**
 * Pauses the program for the amount of time (in microseconds) specified by the parameter.
 * https://www.arduino.cc/reference/en/language/functions/time/delaymicroseconds/
 * @param us Currently, the largest value that will produce an accurate delay is 16383.
 */
LIBRARY_API void delayMicroseconds(unsigned int us);

// Advanced I/O

/**
 * Reads a pulse (either HIGH or LOW) on a pin.
 * https://www.arduino.cc/reference/en/language/functions/advanced-io/pulsein/
 */
LIBRARY_API unsigned long pulseIn(std::uint8_t pin, std::uint8_t state, unsigned long timeout = 1000000L);

/**
 * An alternative to pulseIn() which is better at handling long pulse and interrupt affected scenarios.
 * https://www.arduino.cc/reference/en/language/functions/advanced-io/pulseinlong/
 */
LIBRARY_API unsigned long pulseInLong(std::uint8_t pin, std::uint8_t state, unsigned long timeout = 1000000L);

/**
 * Shifts out a byte of data one bit at a time.
 * https://www.arduino.cc/reference/en/language/functions/advanced-io/shiftout/
 */
LIBRARY_API void shiftOut(std::uint8_t dataPin, std::uint8_t clockPin, std::uint8_t bitOrder, std::uint8_t val);

/**
 * Shifts in a byte of data one bit at a time.
 * https://www.arduino.cc/reference/en/language/functions/advanced-io/shiftin/
 */
LIBRARY_API std::uint8_t shiftIn(std::uint8_t dataPin, std::uint8_t clockPin, std::uint8_t bitOrder);

/**
 * Generates a square wave of the specified frequency (and 50% duty cycle) on a pin.
 * https://www.arduino.cc/reference/en/language/functions/advanced-io/tone/
 */
LIBRARY_API void tone(std::uint8_t pin, unsigned int frequency, unsigned long duration = 0);

/**
 * Stops the generation of a square wave triggered by tone().
 * https://www.arduino.cc/reference/en/language/functions/advanced-io/notone/
 */
LIBRARY_API void noTone(std::uint8_t pin);

// Random numbers

/**
 * The random function generates pseudo-random numbers.
 * https://www.arduino.cc/reference/en/language/functions/random-numbers/random/
 */
LIBRARY_API long random(long max);

/**
 * The random function generates pseudo-random numbers.
 * https://www.arduino.cc/reference/en/language/functions/random-numbers/random/
 */
LIBRARY_API long random(long min, long max);

/**
 * Initializes the pseudo-random number generator, causing it to start at an arbitrary point in its random sequence.
 * https://www.arduino.cc/reference/en/language/functions/random-numbers/randomseed/
 */
LIBRARY_API void randomSeed(unsigned long seed);

// Math

/**
 * Re-maps a number from one range to another.
 * https://www.arduino.cc/reference/en/language/functions/math/map/
 */
LIBRARY_API long map(long value, long fromLow, long fromHigh, long toLow, long toHigh);

// Characters

LIBRARY_API bool isAlpha(int c);
LIBRARY_API bool isAlphaNumeric(int c);
LIBRARY_API bool isAscii(int c);
LIBRARY_API bool isControl(int c);
LIBRARY_API bool isDigit(int c);
LIBRARY_API bool isGraph(int c);
LIBRARY_API bool isHexadecimalDigit(int c);
LIBRARY_API bool isLowerCase(int c);
LIBRARY_API bool isPrintable(int c);
LIBRARY_API bool isPunct(int c);
LIBRARY_API bool isSpace(int c);
LIBRARY_API bool isUpperCase(int c);
LIBRARY_API bool isWhitespace(int c);

using std::min;
using std::max;

// Serial interface

enum SerialConfig {
	SERIAL_5N1,
	SERIAL_6N1,
	SERIAL_7N1,
	SERIAL_8N1,
	SERIAL_5N2,
	SERIAL_6N2,
	SERIAL_7N2,
	SERIAL_8N2,
	SERIAL_5E1,
	SERIAL_6E1,
	SERIAL_7E1,
	SERIAL_8E1,
	SERIAL_5E2,
	SERIAL_6E2,
	SERIAL_7E2,
	SERIAL_8E2,
	SERIAL_5O1,
	SERIAL_6O1,
	SERIAL_7O1,
	SERIAL_8O1,
	SERIAL_5O2,
	SERIAL_6O2,
	SERIAL_7O2,
	SERIAL_8O2,
};

enum SerialPrintFormat {
	BIN,
	OCT,
	DEC,
	HEX,
};

// A subset of Serial class
class LIBRARY_API SerialMock
{
public:
	operator bool() const;
	void begin(long speed, SerialConfig config = SERIAL_8N1);

	void print(char val, SerialPrintFormat format = DEC);
	void print(int val, SerialPrintFormat format = DEC);
	void print(long val, SerialPrintFormat format = DEC);
	void print(long long val, SerialPrintFormat format = DEC);
	void print(unsigned char val, SerialPrintFormat format = DEC);
	void print(unsigned int val, SerialPrintFormat format = DEC);
	void print(unsigned long val, SerialPrintFormat format = DEC);
	void print(unsigned long long val, SerialPrintFormat format = DEC);
	void print(double val);
	void print(const char* val);

	void println(char val, SerialPrintFormat format = DEC);
	void println(int val, SerialPrintFormat format = DEC);
	void println(long val, SerialPrintFormat format = DEC);
	void println(long long val, SerialPrintFormat format = DEC);
	void println(unsigned char val, SerialPrintFormat format = DEC);
	void println(unsigned int val, SerialPrintFormat format = DEC);
	void println(unsigned long val, SerialPrintFormat format = DEC);
	void println(unsigned long long val, SerialPrintFormat format = DEC);
	void println(double val);
	void println(const char* val);

	std::size_t available() const;
	int peek() const;
	int read();
	std::size_t readBytes(char* buffer, std::size_t length);
};

LIBRARY_API extern SerialMock Serial;

#endif
