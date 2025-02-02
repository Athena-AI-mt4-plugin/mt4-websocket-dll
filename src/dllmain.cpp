#include <windows.h>
#include "websocket_handler.h"

WebSocketServer* ws_server;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            ws_server = new WebSocketServer();
            ws_server->run();
            break;
        case DLL_PROCESS_DETACH:
            delete ws_server;
            break;
    }
    return TRUE;
}
