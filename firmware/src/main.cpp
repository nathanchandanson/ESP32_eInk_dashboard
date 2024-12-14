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
    Serial.println("\nSending the request to the API");
    theTodoistAPI.send_request();
    Serial.println("\nTasks with A faire label :");
    std::vector<todoist_task> tasks = theTodoistAPI.get_tasks_from_label("A faire");
    for(todoist_task task : tasks){
        Serial.println(task.get_content() + " : " + task.get_priority());
    }

    delay(10000);
}