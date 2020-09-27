#include <WiiChuck.h>

Accessory nunchuck1;
Accessory nunchuck2;

void setup()
{
	Serial.begin(115200);
	
	// Multiplexer located at address 0x70
	nunchuck1.addMultiplexer(0x70, 0); // Port 0
	nunchuck2.addMultiplexer(0x70, 1); // Port 1
	
	nunchuck1.begin();
	nunchuck2.begin();
	
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
	if (nunchuck1.type == Unknown)
		nunchuck1.type = NUNCHUCK;

	if (nunchuck2.type == Unknown)
		nunchuck2.type = NUNCHUCK;
}

void loop()
{
	Serial.println("-------------------------------------------");
	
	// Collect data from devices
	nunchuck1.readData();
	nunchuck2.readData();

	// Print data in automatic style for Nunchuck 1
	nunchuck1.printInputs();

	// Print all bytes in array of Nunchuck 1
	for (int i = 0; i < WII_VALUES_ARRAY_SIZE; i++)
	{
		Serial.println("Controller Val " + String(i) + " = " + String((uint8_t) nunchuck1.values[i]));
	}

	// Print data in automatic style for Nunchuck 2
	nunchuck2.printInputs();

	// Print all bytes in array of Nunchuck 2
	for (int i = 0; i < WII_VALUES_ARRAY_SIZE; i++)
	{
		Serial.println("Controller Val " + String(i) + " = " + String((uint8_t) nunchuck2.values[i]));
	}

}
