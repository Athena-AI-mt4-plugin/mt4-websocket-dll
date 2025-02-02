#ifndef WEBSOCKET_HANDLER_H
#define WEBSOCKET_HANDLER_H

#include <websocketpp/config/asio.hpp>
#include <websocketpp/server.hpp>
#include <string>

class WebSocketServer {
public:
    WebSocketServer();
    void run();
    void send_message(const std::string& message);
    static void kill_existing_process_on_port(int port);
    
private:
    void on_message(websocketpp::connection_hdl hdl, websocketpp::server<websocketpp::config::asio>::message_ptr msg);
    websocketpp::server<websocketpp::config::asio> server;
};

#endif // WEBSOCKET_HANDLER_H
