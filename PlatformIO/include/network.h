#ifndef NETWORK_H
#define NETWORK_H

#include <WiFi.h>
#include "task.h"
#include "queue.h"

struct ssidInfo_t
{
    uint8_t count;
    char ssidName[33];
    wifi_auth_mode_t auth;
}; 

extern QueueHandle_t networkScanQueueHandle;
extern TaskHandle_t  networkScanTaskHandle;

extern String connectedSSID;
extern String connectedPASS;

extern String selectedSSID;
extern String selectedPASS;

void networkScanTask(void *param);



#endif

