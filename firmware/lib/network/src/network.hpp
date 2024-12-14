#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <WiFi.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <vector>

#include "../../../include/data.h"

#define MAX_SIZE_DATA 2048

//////////////////////////////////////////////////////////////
// Connection to the Wifi
//////////////////////////////////////////////////////////////
int Wifi_connect();

/////////////////////////////////////////////////////////////////////
// Classes for the different integrations
/////////////////////////////////////////////////////////////////////
class todoist_task
{
private:
    String m_content;
    std::vector<String> m_labels;
    int m_priority;

public:
    todoist_task(): m_content(), m_labels(), m_priority()
    {}
    todoist_task(String content, std::vector<String> labels, int priority): m_content(content), m_labels(labels), m_priority(priority)
    {}

    String get_content() const { return m_content; }
    std::vector<String> get_labels() const { return m_labels; }
    int get_priority() const { return m_priority; }
};

//////////////////////////////////////////////////////////////
// Classes for the APIs
//////////////////////////////////////////////////////////////
/* Generic class */
class generic_API
{
protected:
    const char* m_request_url;
    JsonDocument m_data;

protected:
    generic_API(): m_request_url("undefined"), m_data()
    {m_data = m_data.to<JsonArray>();}
    generic_API(const char* url_request): m_request_url(url_request), m_data()
    {}

public:
    const char* get_request_url() const { return m_request_url; };
    JsonDocument get_data() const { return m_data; };
    virtual void send_request() = 0;
    virtual void print_data() = 0;
};

/* Todoist API class */
class todoist_API : public generic_API
{
private:
    const std::pair<String,String> m_request_header = {String("Authorization"), String("Bearer ") + TODOIST_API_TOKEN};
    
public:
    todoist_API(): generic_API(TODOIST_API_URL)
    {}

    void send_request();
    void print_data();
    std::vector<todoist_task> get_tasks_from_label(const char* label);
};

#endif