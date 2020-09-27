#include <WiiChuck.h>

Accessory nunchuck;

void setup()
{
	Serial.begin(115200);
	
	nunchuck.begin();

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
}

void loop()
{
	Serial.println("-------------------------------------------");
	
	// Collect data from device
	nunchuck.readData();
	
	// Print data in automatic style
	nunchuck.printInputs();
	
	// Print all bytes in array
	for (int i = 0; i < WII_VALUES_ARRAY_SIZE; i++)
	{
		Serial.println("Controller Val " + String(i) + " = " + String((uint8_t) nunchuck.values[i]));
	}
}
