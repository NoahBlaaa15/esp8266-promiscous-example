# Espressif 8266 Promiscous-mode example
A Test for the Promiscous Mode on the Esp8266 12E
In the following text i am going to discribe how i have done it and what can be done with it.

## How is it working? 

The ESP8266 SDK supports a function called promiscous Mode, when you enter this mode you can "sniff" Wifi Packets. 
From them you can get the MAC of the Reciever and Sender, the SSID of the AP and the encrypted Data when it is a DATA Packet.
  
## Code Examples

First you have to set the WIFI Mode of the ESP to STATION_MODE, only there you can use Promiscous Mode.
```C
wifi_set_opmode(STATION_MODE);
```
Then you need to enter Promiscous Mode and define a Callback when a PAcket is recieved.
```C
wifi_promiscuous_enable(0);
wifi_set_promiscuous_rx_cb(promiscCb);
wifi_promiscuous_enable(1);
```
Now everytime a Packet is recieved the Callback function promiscCB is called.
```C
void promiscCb(uint8_t *buf, uint16_t len)
{
}
```
Currently no Channel(WIFI Channels 1-14) is set so you have to set one yourself or let it cycle through them in a nonblocking loop function.
```C
wifi_set_channel(channel);
```
At the end we will have to define some structures to decrypt the buffer of the Callback.
```C
struct RxControl {};
struct LenSeq {};
struct sniffer_buf {};
struct sniffer_buf2 {};
```
You can find all Structures in include/structures.h

## Questions
If you have any Questins write me a Mail or contact me on some other way.
This Project was done with Platformio
