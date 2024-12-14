#include <Arduino.h>
#include "network.hpp"
#include "data.h"

//////////////////////////////////////////////////////////////
// Declaration of APIs
//////////////////////////////////////////////////////////////
todoist_API theTodoistAPI;

//////////////////////////////////////////////////////////////
// Setup
//////////////////////////////////////////////////////////////
void setup()
{
    // Start Serial communication
    Serial.begin(9600);

    // Start the wifi connection
    if(Wifi_connect()!=0){
        Serial.println("Error while connecting to Wifi");
        return;
    }


}

void loop()
{
    theTodoistAPI.send_request();
    theTodoistAPI.print_data();
    delay(10000);
}