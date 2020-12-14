# Plug-&-Play Game Console
## Team 10:
Terrence Randall (terrencetjr24@gmail.com),

Gokul Srinivasan (gokss14@gmail.com),
Eric Bankert, 
Arpan Adhikari

## Project Description

A gaming console developed around the STM32F407 microcontroller. The device outputs a VGA signal to provide video,
line level audio, and uses two generic NES controllers to receive user inputs.

The VGA signal is achieved by using of the DMA, timers, and an external DAC (made from resistor network).

The line level audio was achieved by using of the internal DAC and a wave table.

Connecting the controllers was achieved by using of SPI and an external multiplexer to decide which controller to recieve outputs from.

The games that were developed were chess, pong, and snake. Chess was sourced from https://github.com/fogleman/MisterQueen and modified to 
get rid of the computer and to allow for direct user inputs.

## Note on running the project

Currently, the project needs to be imported directly and the name of the folder needs to be changed to "dummyFolder"

## Sources:

Chess game -> https://github.com/fogleman/MisterQueen

