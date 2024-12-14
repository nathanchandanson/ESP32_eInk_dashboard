#include "network.hpp"

/* Connect to the given Wifi */
int Wifi_connect()
{
    Serial.println("Connecting to the wifi with SSID :" + String(NETWORK_SSID));

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

/* Methods of the generic API */
void generic_API::print_data() const
{
    // JsonArray array = m_data.as<JsonArray>();
    // for(JsonObject task : array){
    //     const char* content = task["content"];
    //     Serial.println(content);
    // }
}

/* Methods for the Todoist API */
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