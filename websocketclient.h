#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <uWS.h>

class WebSocketClient
{
public:
    WebSocketClient();
    ~WebSocketClient();
protected:
    bool handShakeWithServer(uWS::WebSocket<uWS::CLIENT> *ws);
private:
    uWS::Hub h;
    char messageIndex;

};

#endif // WEBSOCKETCLIENT_H
