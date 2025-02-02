#include "websocket_handler.h"
#include "encryption.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

WebSocketServer::WebSocketServer() {
    kill_existing_process_on_port(6058); // Ensure port is free

    server.init_asio();
    server.set_message_handler(std::bind(&WebSocketServer::on_message, this, std::placeholders::_1, std::placeholders::_2));
    server.set_tls_init_handler([](websocketpp::connection_hdl) {
        auto ctx = std::make_shared<boost::asio::ssl::context>(boost::asio::ssl::context::tlsv12);
        ctx->use_certificate_chain_file("certs/server-cert.pem");
        ctx->use_private_key_file("certs/server-key.pem", boost::asio::ssl::context::pem);
        return ctx;
    });
    server.listen(6058);
    server.start_accept();
}

void WebSocketServer::run() {
    server.run();
}

void WebSocketServer::on_message(websocketpp::connection_hdl hdl, websocketpp::server<websocketpp::config::asio>::message_ptr msg) {
    std::string decrypted = AES_Decrypt(msg->get_payload());
    std::cout << "Received Encrypted Message: " << msg->get_payload() << std::endl;
    std::cout << "Decrypted Message: " << decrypted << std::endl;
    
    std::string response = AES_Encrypt("Response from MT4 DLL");
    server.send(hdl, response, websocketpp::frame::opcode::text);
}

void WebSocketServer::kill_existing_process_on_port(int port) {
    std::string command = "netstat -ano | findstr :" + std::to_string(port);
    FILE* pipe = _popen(command.c_str(), "r");
    if (!pipe) return;

    char buffer[128];
    std::string result = "";
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    _pclose(pipe);

    if (!result.empty()) {
        std::string pid = result.substr(result.find_last_of(" ") + 1);
        std::string killCmd = "taskkill /PID " + pid + " /F";
        system(killCmd.c_str());
    }
}
