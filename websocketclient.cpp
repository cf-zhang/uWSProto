#include "websocketclient.h"
#include "Login.pb.h"
#include <iostream>
using namespace com::genesis::protobuf;
WebSocketClient::WebSocketClient()
{
    h.onError([](void *user) {
        switch ((long) user) {
        case 1:
            std::cout << "Client emitted error on" << std::endl;
            break;
        default:
            std::cout << "FAILURE: " << user << " should not emit error!" << std::endl;
            exit(-1);
        }
    });
    h.onMessage([=](uWS::WebSocket<uWS::CLIENT> *ws, char *message, size_t length, uWS::OpCode opCode) {
        size_t len = *(uint32_t*)message;
        uint16_t type = *(uint16_t*)(message+4);
        std::cout<< len<<" "<<type;
        uint8_t data[length-6];
        switch (type) {
        case SCMessageType::SC_HANDSHAKE_REPLY:
        {
            SCHandshakeReply scReply;
            scReply.ParseFromArray(data+6, len);
            messageIndex = scReply.indexbegin();
            std::cout<<"message index"<< messageIndex<<std::endl;

            CSClientType csClientType;
            csClientType.set_type(ClientType::Robot);
            size_t length = csClientType.ByteSize();
            uint8_t *data = new uint8_t[length+7];
            *(uint32_t *)data = length;
            *(uint16_t *)(data+4) = CSMessageType::CS_CLIENT_TYPE;
            messageIndex++;
            *(uint16_t *)(data+6) = messageIndex;

            csClientType.SerializeToArray(data+7, length);
            ws->send((char*)data, length + 7, uWS::OpCode::BINARY);
            delete [] data;

            break;
        }
        default:
            break;
        }

//        std::cout << std::string(message, length) << std::endl;
//        ws->send(message, length, opCode);
    });
    h.onConnection([=](uWS::WebSocket<uWS::CLIENT> *ws, uWS::HttpRequest req) {
        switch ((long) ws->getUserData()) {
        case 1:
            std::cout << "Client established a remote connection!" << std::endl;
//            ws->close(1000);
            handShakeWithServer(ws);
            break;
        default:
            std::cout << "FAILURE: " << ws->getUserData() << " should not connect!" << std::endl;
            exit(-1);
        }
    });

    h.onDisconnection([](uWS::WebSocket<uWS::CLIENT> *ws, int code, char *message, size_t length) {
        std::cout << "Client got disconnected with data: " << ws->getUserData() << ", code: " << code << ", message: <" << std::string(message, length) << ">" << std::endl;
    });

    h.connect("ws://10.0.20.103:22001", (void *) 1);
//    h.connect("ws://127.0.0.1:3000", (void *) 1);

    h.run();


}

WebSocketClient::~WebSocketClient(){

}

bool WebSocketClient::handShakeWithServer(uWS::WebSocket<uWS::CLIENT> *ws){

    CSHandshake handShake;

    size_t length = handShake.ByteSize();
    uint8_t *data = new uint8_t[ length + 7];
    *(uint32_t *)data = length;
    *(uint16_t *)(data+4) = CSMessageType::CS_HANDSHAKE;
    handShake.SerializeToArray(data+7,length);
    ws->send((char*)data, length + 7, uWS::OpCode::BINARY);
    delete []data;
}

