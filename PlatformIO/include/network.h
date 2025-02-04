#ifndef NETWORK_H
#define NETWORK_H

#include <WiFi.h>
#include "task.h"

extern TaskHandle_t  networkScanTaskHandler;
extern bool runNetworkTask;

void networkScanTask(void *param);

#endif

