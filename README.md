# Projekt zespołowy

## DONE
- Modules connected
- Can communicates with main board
 

## TODO:
- Communicate 4G with main board via RX and TX pin
- Connect 4G to the network
- Develop CAN signal interpretation
-everything else

## Final project idea:
![image](https://github.com/Pyzaaa/Projekt-zespolowy/assets/107617424/a37b8844-01dc-4a8e-8270-4e7782471b2f)

## Current cable connection schematic:
![image](https://github.com/Pyzaaa/Projekt-zespolowy/assets/107617424/2dd2fa63-3669-4903-9059-bcc4a9f2f85f)


## Problems and considerations overview:
- 4G modules selection (Not many high speed connective options availible on the market)
- SIM modules frequency (Some modules only work in some countries/continents)
- Power consumption (High speed connections and GPS might use more power than arduino circuits can provide, might require a dedicated USB power cable for 4G module)
- Antenna positioning (Antenna needs to be attached to the board and still be somewhere in the cabin)
- GPS Antenna position (Likely requires LOS to sky)
- Depending on solution, there might be too much data to collect/process/send even via 4G
<br><br>

- Problem with dedicated Waveshare SIM7600 Libraries (parts code needs to be rewritten to work)
- SIM module communicates via Serial, board needs to support sending Serial1 to module and Serial0 for development and debugging
- WaveShare SIM7600 module communicates with high Baud rate (115200)
- There are many libraries for CAN modules and some code for SIM but they need testing and review
- It is possible to connect an SD card to SIM module but not sure if it can be written from arduino via Serial
- 