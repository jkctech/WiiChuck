#include <WiiChuck.h>
#if defined(ARDUINO_ARCH_ESP32)
# include <ESP32Servo.h>
#else
# include <Servo.h>
#endif

Accessory nunchuck1;

Servo servoOne;
Servo servoTwo;
Servo ServoThree;

void setup()
{
	Serial.begin(115200);
	
	nunchuck1.begin();
	
	/*
	 * If type cannot be detected, fall back to standard Nunchuck.
	 *
	 * If type is not auto-detected, you can set the type manually:
	 *  NUNCHUCK
	 *  WIICLASSIC
	 *  GuitarHeroController
	 *  GuitarHeroWorldTourDrums
	 *  DrumController
	 *  DrawsomeTablet
	 *  Turntable
	 */
	if (nunchuck.type == Unknown)
		nunchuck.type = NUNCHUCK;

	// Attach servo's to pin 33, 35 and 36
	servoOne.attach(33, 1000, 2000);
	servoTwo.attach(35, 1000, 2000);
	ServoThree.attach(36, 1000, 2000);
}

void loop()
{
	int servoOneVal;
	int ServoTwoVal;
	int ServoThreeVal;

	// Collect data from device
	nunchuck1.readData();
	
	// Map Nunchuck's X axis to servo rotation
	servoOneVal = map(nunchuck1.values[0], 0, 255, 0, 180);

	// Map Nunchuck's Y axis to servo rotation
	ServoTwoVal = map(nunchuck1.values[1], 0, 255, 0, 180);

	// If Z button is pressed, put servo on 0 degrees
	if (nunchuck1.values[10] == 255)
		ServoThreeVal = 0;
	
	// If C button is pressed, put servo on 180 degrees
	else if (nunchuck1.values[11] == 255)
		ServoThreeVal = 180;
	
	// If none are pressed, center the servo to 90 degrees
	else
		ServoThreeVal = 90;
	
	// Write data to servo's
	servoOne.write(servoOneVal);
	servoTwo.write(ServoTwoVal);
	ServoThree.write(ServoThreeVal);

	Serial.println("Set " + String(servoOneVal) + " " + String(ServoTwoVal) + " " + String(ServoThreeVal));
}
