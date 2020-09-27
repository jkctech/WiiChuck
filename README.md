# WiiChuck
An Arduino library for talking to every extension controller made for the Wii including the Nunchuk and Classic Controller over I²C.

## Supported Controllers:

* Nunchuk
* Classic Controller
* Guitar Hero Guitar
* Guitar Hero and Taiko Drums
* DJ Hero
* Drawsome Tablet

# General Usage

Ofcourse, working with a library, requires you to include it:
```C
#include <WiiChuck.h>
```
To use the class methods on a controller instace, you first create a new instance.
```C++
Accessory controller;
```
After that, you will have to initialize it:
```C++
controller.begin();
```
After the controller is succesfully initialized, you will be able to detect and force the type of controller connected using ENUMs:
```C++
if (controller.type == Unknown)
	controller.type = NUNCHUCK;
```
A controller can be any of these types:
```C++
NUNCHUCK
WIICLASSIC
GuitarHeroController
GuitarHeroWorldTourDrums
DrumController
DrawsomeTablet
Turntable
```
**Be aware that all public member functions can be called on ALL types of controller.**
Doing so however, will have undefined behaviour.
*(For example, calling a Wii guitar's ```getGreenButton()``` on a Drawsome Tablet controller.)*

# Getting data
There are 2 ways of collecting the data from a controller.
1. Using public member functions
2. Using the mapping array

Both ways require the following basic usage.
On every iteration of your main loop, you want to call:
```C++
controller.readData();
```
This collects the current data and stores it so you can access it.

**Please note** that the mapping array does not always contain all information from a controller.
*(For example, the stick of a Wii Guitar is not included in the mapping array.)*

## 1. Public Functions
All controller types have a list of their own designated functions.
Most of them are functions to gather the data for a specific input. (E.g. a button, a stick, etc.)

Every type also includes these standard functions:

 - ```void getValuesTYPE(uint8_t *values)``` Stores all data in a given array.
 - ```void printInputsTYPE(Stream &stream = Serial)``` Pretty prints values from this controller.

*(Where "TYPE" stands for the controller type.)*

<details>
	<summary>Nunchuck</summary>

	int getJoyX()
	int getJoyY()

	float getRollAngle()
	float getPitchAngle()

	int getAccelX()
	int getAccelY()
	int getAccelZ()

	boolean getButtonC()
	boolean getButtonZ()

	void getValuesNunchuck(uint8_t *values)
	void printInputsNunchuck(Stream &stream = Serial)
</details>

<details>
	<summary>Wii Classic Controller</summary>

	int getJoyXLeft();
	int getJoyXRight();
	int getJoyYLeft();
	int getJoyYRight();

	int getTriggerLeft();
	int getTriggerRight();

	int getPadRight();
	int getPadDown();
	int getPadUp();
	int getPadLeft();
	int getButtonX();
	int getButtonY();
	int getButtonA();
	int getButtonB();

	int getButtonMinus();
	int getButtonHome();
	int getButtonPlus();

	int getButtonZLeft();
	int getButtonZRight();

	void printInputsClassic(Stream &stream = Serial);
	void getValuesClassic(uint8_t *values);
</details>

<details>
	<summary>Guitar Hero Guitar</summary>

	int getStickXGuitar();
	int getStickYGuitar();

	int getPlusButtonGuitar();
	int getMinusButtonGuitar();

	int getGreenButton();
	int getRedButton();
	int getYellowButton();
	int getBlueButton();
	int getOrangeButton();

	int getStrumUp();
	int getStrumDown();
	int getWhammyBar();

	void printInputsGuitar(Stream &stream = Serial);
	void getValuesGuitar(uint8_t *values);
</details>

<details>
	<summary>Guitar Hero and Taiko Drums</summary>

	int getStickXDrums();
	int getStickYDrums();

	int getSoftnessDataFor();
	int getSoftness();
	int getHighHatDataFlag();
	int getSoftnessDataFlag();

	int getMinusButtonDrums();
	int getPlusButtonDrums();

	int getOrangeDrum();
	int getRedDrum();
	int getYellowDrum();
	int getGreenDrum();
	int getBlueDrumm();
	int getBassPedal();

	void printInputsDrums(Stream &stream = Serial);
	void getValuesDrums(uint8_t *values);
</details>

<details>
	<summary>DJ Hero</summary>

	int getCrossfadeSlider();
	int getEffectDial();

	int getStickX();
	int getStickY();

	int getRightDJTable();
	int getLeftDJTable();

	int getEuphoriaButton();
	int getPlusButton();
	int getMinusButton();

	int getLeftGreenButton();
	int getLeftRedButton();
	int getLeftBlueButton();
	int getRightGreenButton();
	int getRightRedButton();
	int getRightBlueButton();

	void printInputsDj(Stream &stream = Serial);
	void getValuesDj(uint8_t *values);
</details>

<details>
	<summary>Drawsome Tablet</summary>

	int getPenXPosition();
	int getPenYPosition();
	int getPenPressure();
	int getPenContact();

	void initBytesDrawsome();

	void printInputsDrawsome(Stream &stream = Serial);
	void getValuesDrawsome(uint8_t *values);
</details>


## 2. Mapping Array

All controllers have been mapped across a single readable array so that code written for one Wii accessory can be made generic for all of Wii accessory devices. The values that come from the controller are scaled to a 0-255 range for all analog and digital values. Each value is stored in a single byte in the ```values[]``` array, a public member of the ```Accessory``` class. 

<details>
	<summary>Nunchuck</summary>

	values[0] = map(getJoyX(), 0, 255, 0, 255);
	values[1] = map(getJoyY(), 0, 255, 0, 255);
	values[2] = map(getRollAngle(), 0, 1024, 0, 256);
	values[3] = map(getPitchAngle(), 0, 1024, 0, 256);
	values[4] = map(getAccelX(), 0, 1024, 0, 256);
	values[5] = map(getAccelY(), 0, 1024, 0, 256);

	values[6] = map(getAccelZ(), 0, 1024, 0, 256);
	values[7] = 0;
	values[8] = 0;
	values[9] = 0;
	values[10] = getButtonZ() ? 255 : 0;
	values[11] = getButtonC() ? 255 : 0;
	values[12] = 0;
	values[13] = 0;

	values[14] = 0;
	values[15] = 0;
	values[16] = 0;

	values[17] = 0;
	values[18] = 0;
</details>

<details>
	<summary>Classic Controller Mapping</summary>

	values[0] = map(getJoyXLeft(),0,64,0,256);
	values[1] = map(getJoyYLeft(),0,64,0,256);
	values[2] = map(getJoyXRight(),0,32,0,256);
	values[3] = map(getJoyYRight(),0,32,0,256);
	values[4] = 0;
	values[5] = 0;

	values[6] = getPadRight() ? 255 : (getPadLeft() ? 0 : 128);
	values[7] = getPadDown() ? 0:(getPadUp() ? 255 : 128);
	values[8] = getButtonX() ? 255 : 0;
	values[9] = getButtonY() ? 255 : 0;
	values[10] = getButtonZLeft() ? 255 : 0;
	values[11] = map(getTriggerLeft(), 0, 32, 0, 256);
	values[12] = getButtonA() ? 255 : 0;
	values[13] = getButtonB() ? 255 : 0;

	values[14] = getButtonMinus() ? 0 : (getButtonPlus() ? 255 : 128);
	values[15] = getButtonHome() ? 255 : 0;
	values[16] = 0;

	values[17] = map(getTriggerRight(), 0, 32, 0, 256);
	values[18] = getButtonZRight() ? 255 : 0;
</details>

<details>
	<summary>Guitar Hero Guitar Mapping</summary>

	values[0] = map(getWhammyBar(), 0, 255, 0, 256);
	values[1] = 0;
	values[2] = 0;
	values[3] = 0;
	values[4] = 0;
	values[5] = 0;

	values[6] = getPlusButtonGuitar() ? 255 : (getMinusButtonGuitar() ? 0 : 128);
	values[7] = getStrumUp() ? 255 : (getStrumDown() ? 0 : 128);
	values[8] = 0;
	values[9] = 0;
	values[10] = getGreenButton() ? 255 : 0;
	values[11] = getRedButton() ? 255 : 0;
	values[12] = getYellowButton() ? 255 : 0;
	values[13] = getBlueButton() ? 255 : 0;

	values[14] = getOrangeButton() ? 255 : 0;
	values[15] = getLeftGreenButton() ? 255: 0;
	values[16] = getButtonPlus() ? 255 : 0;

	values[17] = 0;
	values[18] = 0;
</details>

<details>
	<summary>Guitar Hero and Taiko Drums Mapping</summary>

	values[0] = map(getCrossfadeSlider(), 0, 255, 0, 256);
	values[1] = map(getEffectDial(), 0, 255, 0, 256);
	values[2] = map(getStickXGuitar(), 0, 255, 0, 256);
	values[3] = map(getStickYGuitar(), 0, 255, 0, 256);
	values[4] = map(getRightDJTable(), 0, 255, 0, 256);
	values[5] = map(getLeftDJTable(), 0, 255, 0, 256);

	values[6] = getPlusButtonGuitar() ? 255 : (getMinusButtonGuitar() ? 0 : 128);
	values[7] = getEuphoriaButton() ? 255 : 0;
	values[8] = 0;
	values[9] = 0;
	values[10] = getRightBlueButton() ? 255 : 0;
	values[11] = getRightRedButton() ? 255 : 0;
	values[12] = getRightGreenButton() ? 255 : 0;
	values[13] = getLeftBlueButton() ? 255 : 0;

	values[14] = getLeftRedButton() ? 255 : 0;
	values[15] = getLeftGreenButton() ? 255 : 0;
	values[16] = getButtonPlus() ? 255 : 0;

	values[17] = getButtonZLeft() ? 255 : 0;
	values[18] = getButtonZRight() ? 255 : 0;
</details>

<details>
	<summary>DJ Table Mapping</summary>

	values[0] = map(getCrossfadeSlider(), 0, 255, 0, 256);
	values[1] = map(getEffectDial(), 0, 255, 0, 256);
	values[2] = map(getStickX(), 0, 255, 0, 256);
	values[3] = map(getStickY(), 0, 255, 0, 256);
	values[4] = map(getRightDJTable(), 0, 255, 0, 256);
	values[5] = map(getLeftDJTable(), 0, 255, 0, 256);

	values[6] = getPlusButton() ? 255 : (getMinusButton() ? 0 : 128);
	values[7] = getEuphoriaButton() ? 255:0;
	values[8] = 0;
	values[9] = 0;
	values[10] = getRightBlueButton() ? 255 : 0;
	values[11] = getRightRedButton() ? 255 : 0;
	values[12] = getRightGreenButton() ? 255 : 0;
	values[13] = getLeftBlueButton() ? 255 : 0;

	values[14] = getLeftRedButton() ? 255 : 0;
	values[15] = getLeftGreenButton() ? 255 : 0;
	values[16] = getButtonPlus() ? 255 : 0;

	values[17] = getButtonZLeft() ? 255 : 0;
	values[18] = getButtonZRight() ? 255 : 0;
</details>

<details>
	<summary>Drawsome Mapping</summary>

	values[0] = map(getPenXPosition(), 0, 64, 0, 256);
	values[1] = map(getPenYPosition(), 0, 64, 0, 256);
	values[2] = map(getPenPressure(), 0, 32, 0, 256);
	values[3] = 0;
	values[4] = 0;
	values[5] = 0;

	values[6] = 0;
	values[7] = 0;
	values[8] = 0;
	values[9] = 0;
	values[10] = getPenContact() ? 255 : 0;
	values[11] = 0;
	values[12] = 0;
	values[13] = 0;

	values[14] = 0;
	values[15] = 0;
	values[16] = 0;

	values[17] = 0;
	values[18] = 0;
</details>

# Repository Structure 
This repository is forked from a curated set of old Arduino Libraries. I kept the old commits and the fork linking to keep attribution to the work done before I picked up the torch. In my mind we all see farther by standing on the shoulders of giants, so it is only proper to give credit where credit is due.

## Additional Credit
This repository is forked from [madhephaestus](https://github.com/madhephaestus/WiiChuck). While working with this library for a project, I noticed some things were not so easy to find in the documentation and required you to dig into the sourcecode. While doing so, I decided to refactor the code to make it more readable.