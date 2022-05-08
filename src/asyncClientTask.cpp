#include <Arduino.h>
#include <AsyncTCP.h>
#include "connection-details.h"
#include <varint.h>

AsyncClient client;

void onConnect(void* args, AsyncClient* client) {
    Serial.println("Connected!");
}

void onData(void* args, AsyncClient* client, void *data, size_t len) {
    /*unsigned char bytesRead;
    unsigned long long varLen = varint_decode((char*) data, (int) len , &bytesRead);
    Serial.print("Got data! Length: ");
    Serial.print(len);
    Serial.print(" varint length: ");
    Serial.print(varLen);
    Serial.print(" in ");
    Serial.print((int) bytesRead);
    Serial.println(" bytes.");*/
    client->write((const char*) data, len);
}

void runAsyncClientTask(void *pvParameters) {
    Serial.print("Async client task running on core ");
    Serial.println(xPortGetCoreID());

    client.connect(WEBSOCKET_IP, WEBSOCKET_PORT);
    client.onConnect(onConnect);
    client.onData(onData);

    while(!client.connected()) {
        Serial.print(".");
        delay(500);
    }
    Serial.println("\nConnected to server!");

    while(true) {

    }
}