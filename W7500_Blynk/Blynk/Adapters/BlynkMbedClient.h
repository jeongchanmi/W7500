/**
 * @file       BlynkParam.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Jan 2015
 * @brief
 *
 */

#ifndef BlynkMbedClient_h
#define BlynkMbedClient_h

#include <BlynkApiMbed.h>
#include <Blynk/BlynkDebug.h>
#include <TCPSocketConnection.h>

#if defined(ESP8266) && !defined(BLYNK_NO_YIELD)
    #define YIELD_FIX() BLYNK_RUN_YIELD();
#else
    #define YIELD_FIX()
#endif

template <typename Client>
class BlynkMbedClientGen : public Socket
{
public:
    BlynkMbedClientGen(Client& c)
        : client(NULL), domain(NULL), port(0), isConn(false)
    {
        setClient(&c);
    }

    BlynkMbedClientGen()
        : client(NULL), domain(NULL), port(0), isConn(false)
    {}

    void setClient(Client* c) {
        client = c;
        client->set_blocking(true, BLYNK_TIMEOUT_MS*1000);
    }

    void begin(char* a, uint16_t p) {
        domain = NULL;
        port = p;
        addr = a;
    }

    void begin(const char* d, uint16_t p) {
        domain = d;
        port = p;
    }

    bool connect() {
        if (domain) {
            BLYNK_LOG4(BLYNK_F("Connecting to "), domain, ':', port);
            client->connect(domain, port);
            isConn = (1 == client->is_connected());
            return isConn;
        } else { //if (uint32_t(addr) != 0) {
            BLYNK_LOG_IP("Connecting to ", addr);
            isConn = (1 == client->connect(addr, port));
            return isConn;
        }
    }

    void disconnect() {
        isConn = false;
        if (client->getsock()) return;
        client->close();
        client->setsock(-1);
     }

#ifdef BLYNK_ENC28J60_FIX
    size_t read(void* buf, size_t len) {
        while (client->available() < len) { }
        return client->read((uint8_t*)buf, len);
    }
#else
    size_t read(void* buf, size_t len) {
        size_t res = client->receive((char*)buf, len);
        YIELD_FIX();
        return res;
    }
#endif

#ifdef BLYNK_RETRY_SEND
    size_t write(const void* buf, size_t len) {
        size_t sent = 0;
        int retry = 0;
        while (sent < len && ++retry < 10) {
            size_t w = client->write((const uint8_t*)buf+sent, len-sent);
            if (w != 0 && w != -1) {
                sent += w;
            } else {
                ::delay(50);
#if defined(BLYNK_DEBUG) && defined(BLYNK_PRINT)
                BLYNK_PRINT_TIME();
                BLYNK_PRINT.print(BLYNK_F("Retry "));
                BLYNK_PRINT.print(retry);
                BLYNK_PRINT.print(BLYNK_F(" send: "));
                BLYNK_PRINT.print(sent);
                BLYNK_PRINT.print('/');
                BLYNK_PRINT.println(len);
#endif
            }
        }
        return sent;
    }
#else
    size_t write(const void* buf, size_t len) {
        YIELD_FIX();
        size_t res = client->send((char*)buf, len);
        YIELD_FIX();
        return res;
    }
#endif

    bool connected() { YIELD_FIX(); return isConn && client->is_connected(); }
    int available() {  YIELD_FIX(); 
    //printf("readable : %d, sock: %d\r\n", eth->wait_readable(_sock_fd, 3000000, 0),_sock_fd);  
    //return eth->wait_readable(_sock_fd, 300000, 0); 
    return eth->wait_readable(client->getsock() , 1000*60*5, 0); 
    }

protected:
    Client*     client;
    char*       addr;
    const char* domain;
    uint16_t    port;
    bool        isConn;
};

typedef BlynkMbedClientGen<TCPSocketConnection> BlynkMbedClient;

#endif
