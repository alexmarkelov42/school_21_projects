#include "fcgi_stdio.h"

int main() {
    FCGX_Init();
    int socket = FCGX_OpenSocket("127.0.0.1:8080", 1024);
    FCGX_Request request;
    FCGX_InitRequest(&request, socket, 0);
    
    while (FCGX_Accept_r(&request) >= 0) {
	FCGX_FPrintF(request.out, "Content-type: text/html\r\n"
	       "\r\n"
	       "<title>Hello FCGI</title>\r\n"
	       "<h1>Hello world!</h1>\r\n");
	FCGX_Finish_r(&request);
    }
}
