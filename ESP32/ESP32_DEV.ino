#include "wifiSetting.h"
#include "leds.h"
#include "websocks.h"

void setup() {
    pinMode(22, OUTPUT);
    connect_wifi();
    init_websocket();
}

void loop() {

    // poll the devices for incoming messages
    if(client.available()){
        // Serial.println("Waiting for WS messages...");
        client.poll();
    }
    // reconnect closed websocket
    else{
        // Serial.println("Recon to WS SERVER...");
        ws_reconnect();
    }

    // check wifi connection
    check_and_reconnect();

    delay(1000);
}

// client.send("sending message");
