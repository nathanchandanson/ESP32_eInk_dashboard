#include "network.hpp"

//////////////////////////////////////////////////////////////
// Connection to the Wifi
//////////////////////////////////////////////////////////////
int Wifi_connect()
{
    Serial.println("Connecting to the wifi with SSID : " + String(NETWORK_SSID));

    if(WiFi.begin(NETWORK_SSID, NETWORK_PASSWORD) == WL_CONNECT_FAILED){
        Serial.println("Error during the connection");
        return -1;
    }

    while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(500);
    }

    Serial.println("Successfully connected !");

    WiFi.setAutoReconnect(true);
    return 0;
}

//////////////////////////////////////////////////////////////
// Methods for the Todoist API
//////////////////////////////////////////////////////////////
void todoist_API::send_request()
{
    // Check Wifi connection
    if(WiFi.status() != WL_CONNECTED){
        Serial.println("Error while sending the API request : WiFi not connected");
        return;
    }
    
    // Setup of the HTTP request
    HTTPClient http;
    http.begin(m_request_url);
    http.addHeader(m_request_header.first, m_request_header.second);

    // Sending the request
    int httpResponseCode = http.GET();
    if (httpResponseCode != 200){
        Serial.println("Error while fetching data");
        return;
    }

    // Extracting the data
    String payload = http.getString();
    DeserializationError error = deserializeJson(m_data, payload);
    if(error){
        Serial.println("Error while extracting the data");
        return;
    }
}

void todoist_API::print_data()
{
    for(JsonObject task : m_data.as<JsonArray>()){
        const char* content = task["content"];
        Serial.println(content);
    }
}

std::vector<todoist_task> todoist_API::get_tasks_from_label(const char* label)
{
    std::vector<todoist_task> res;

    // Parcourt de toutes les taches
    for(JsonObject task : m_data.as<JsonArray>()){
        // Get labels of the task
        std::vector<String> labels;
        for(String curr_label : task["labels"].as<JsonArray>()){
            labels.push_back(curr_label);
        }

        // Parcourt des labels
        for(String curr_label : labels){
            if(curr_label == label){
                // res.push_back(todoist_task("test1", {"label1", "label2"}, 2));
                res.push_back(todoist_task(task["content"], labels, task["priority"]));
            }
        }
    }

    return res;
}