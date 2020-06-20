#include <HardwareSerial.h>
#include <user_interface.h>
#include "Arduino.h"
#include "structures.h"
#include "osapi.h"

#define MAX_CLIENTS_TRACKED 200

int mac_known_count = 0;
static char macAddr[MAX_CLIENTS_TRACKED][18];

uint8_t channel = 1;
ulong timer = 0;

void promiscCb(uint8_t *buf, uint16_t len)
{
    if (len == 60){
        struct sniffer_buf *sniffer = (struct sniffer_buf*) buf;

        uint8_t mac[6];
        int i=0;
        for (i=0; i<6; i++) {
            mac[i] = sniffer->buf[i+6];
        }

        static char macString[18];
        sprintf(macString, "%02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        Serial.printf("MAC: %s\n", macString);
        if(mac_known_count > 0){
            for (int j = 0; j < mac_known_count; ++j) {
                Serial.printf("%s / %s : %d\n", macAddr[j], macString, j);
                if(strcmp(macAddr[j],macString) == 0){
                    Serial.printf("Already added! %d\n", mac_known_count);
                    return;
                }
            }
        }


        memcpy(macAddr[mac_known_count], macString, sizeof(macString));
        mac_known_count = mac_known_count + 1;
        Serial.printf("MAC added! %d\n", mac_known_count);


    }
}

void setup(){
    Serial.begin(9600);
    Serial.printf("SDK version:%s", system_get_sdk_version());

    wifi_set_opmode(STATION_MODE);
    wifi_station_disconnect();
    wifi_set_channel(channel);
    Serial.println("WIFI disconnected!");

    wifi_promiscuous_enable(0);

    wifi_set_promiscuous_rx_cb(promiscCb);
    wifi_promiscuous_enable(1);

    Serial.println("WIFI promiscuous!");

    Serial.println("Type:   /-------MAC------/-----WiFi Access Point SSID-----/  /----MAC---/  Chnl  RSSI");

}

void loop(){
    delay(10);
    if(millis() > timer + 10000) {
        timer = millis();
        channel++;
        if (channel == 15) {
            channel = 1;
        }
        Serial.printf("Changing Channel: %d;\n", channel);
        wifi_set_channel(channel);
    }
}
