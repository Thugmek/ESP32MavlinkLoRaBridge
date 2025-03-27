#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include <cstdint>

#include "config.h"

void LoRa_RX_callback(int packet_size){
    if(packet_size == 0) return;

    
}

void LoRa_init(){
    LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
    while (!LoRa.begin(868E6)) {
        delay(100);
    }
    LoRa.setSyncWord(0x7C);
    LoRa.onReceive(LoRa_RX_callback);
    LoRa.receive();
}

void LoRa_send_message(uint8_t *data, uint8_t len){
    LoRa.beginPacket();
    LoRa.write(data, len);
    LoRa.endPacket()
}