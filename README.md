# ComputerZ80
## Step 1. ROM Emulator
Using Arduino Uno we emulate ROM. In the firmware of ROM it has array of values (command opcodes or data). When processor Z80 sets some address on *address bus* and make memory request, Arduino sets the value of this memory cell on *data bus*. But to test ROM, we can choose addresses by overselves. To show how it works, we use this construction: 4 buttons to choose address and 8 LEDs to show binary representation of value.
![image_2021-11-13_13-17-03](https://user-images.githubusercontent.com/44781809/141636375-8cedacd9-56b2-43ee-9ef2-e50469a8e96e.png)
## Step 2. Computer with ROM
![scheme1](https://user-images.githubusercontent.com/73237406/146649732-eb3be2c9-224a-4370-9a25-bebd65be9237.png)
## Step 3. Computer with ROM & RAM
![scheme2](https://user-images.githubusercontent.com/44781809/149593135-c011ff70-edae-4cca-b45a-8c10bd4a4f19.png)
## Step 4. Computer with Network Interface Card (using Arduino Mega 2560)
![scheme3](https://user-images.githubusercontent.com/44781809/149598967-2192eff7-9e4b-4e9b-8fe7-e38556c9d816.png)
