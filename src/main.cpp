#include <Arduino.h>
#include <ESPmDNS.h>
#include <WiFi.h>
#include <WebSocketsClient.h>
#include "connection-details.h"

WebSocketsClient webSocket;

void onWebSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
	switch(type) {
		case WStype_DISCONNECTED:
			Serial.println("Disconnected from websocket!");
			break;
		case WStype_CONNECTED:
			Serial.println("Connected to websocket!");
			break;
		case WStype_TEXT:
            // Send text data back
            webSocket.sendTXT((char*) payload);
			break;
		case WStype_BIN:
            Serial.print("Got binary message of length ");
            Serial.println(length);
			break;
		case WStype_ERROR:			
            Serial.println("Websocket error!");
            break;
		case WStype_FRAGMENT_TEXT_START:
		case WStype_FRAGMENT_BIN_START:
		case WStype_FRAGMENT:
		case WStype_FRAGMENT_FIN:
		case WStype_PING:
		case WStype_PONG:
			break;
	}

}

void websocketTask(void *pvParameters) {
    // Connect to websocket server
    Serial.print("WS running on core ");
    Serial.println(xPortGetCoreID());

    webSocket.onEvent(onWebSocketEvent);
    webSocket.begin(WEBSOCKET_IP, WEBSOCKET_PORT, "/");
    while(true) {
        webSocket.loop();
    }
}

TaskHandle_t wsTask;

void setup() {
    setCpuFrequencyMhz(240);

    Serial.begin(115200);
    Serial.println("");
    Serial.println("Starting ping test receiver...");

    // Connect to wifi
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while(WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println("");
    Serial.print("Connected! IP address: ");
    Serial.println(WiFi.localIP());

    Serial.print("Main running on core ");
    Serial.println(xPortGetCoreID());

    xTaskCreatePinnedToCore(websocketTask, "WS Task", 10000, NULL, 0, &wsTask, 0);
}

void loop() {
    delay(1);
}