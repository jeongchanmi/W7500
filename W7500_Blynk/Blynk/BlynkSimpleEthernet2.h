/**
 * @file       BlynkSimpleEthernet2.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Jan 2016
 * @brief
 *
 */

#ifndef BlynkSimpleEthernet2_h
#define BlynkSimpleEthernet2_h

#ifndef BLYNK_INFO_CONNECTION
#define BLYNK_INFO_CONNECTION "W5500"
#endif

#include <TCPSocketConnection.h>
#include <Adapters/BlynkEthernet.h>

static TCPSocketConnection _blynkEthernetClient;
static BlynkMbedClient _blynkTransport(_blynkEthernetClient);
BlynkEthernet Blynk(_blynkTransport);

#include <BlynkWidgets.h>

#endif
