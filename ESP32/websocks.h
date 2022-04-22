#include <ArduinoWebsockets.h> // WebSocket Client Library for WebSocket

using namespace websockets;
WebsocketsClient client;

const char* WS_SERVER = "ws://192.168.1.153:9090";

void ws_events(WebsocketsEvent event, String data);
void ws_reconnect();
void ws_receive(WebsocketsMessage message);
void init_websocket();

void ws_events(WebsocketsEvent event, String data) {
    if(event == WebsocketsEvent::ConnectionOpened) {
        // Serial.println("Connnection Opened");
    } else if(event == WebsocketsEvent::ConnectionClosed) {
        Serial.println("Connnection Closed");
        ws_reconnect();
    }
}

void ws_reconnect(){
    delay(5000);
    client.connect(WS_SERVER);
}

void ws_receive(WebsocketsMessage message) {
    Serial.print("Got Message: ");
    Serial.println(message.data());

    if(message.data() == "ON_LED_1")
    	turn_on(22);
    else if(message.data() == "OFF_LED_1")
    	turn_off(22);
}

void init_websocket(){
    client.onMessage(ws_receive);
    client.onEvent(ws_events);
    client.connect(WS_SERVER);
}