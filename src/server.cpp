#include <iostream>
#include <string>
#include <signal.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include "connection/socket.h"
#include "http/parser.h"
#include "http/request.h"
#include "http/response.h"
#include "tls/context.h"

using namespace std;
using namespace Connection;
using namespace Http;
using namespace Tls;

int main() {
    
    Parser parser;
    Socket socket;
    Context tls_context;
    SSL_CTX *ctx;
    cout << "Start simple TLS Server" << endl;
    ctx = tls_context.create_context();
    tls_context.configure_context(ctx);

    socket.create(443);

    while (true) {

        SSL *ssl;
        char *buf[8196] = {0};

        int client = socket.serve();
        ssl = SSL_new(ctx);
        SSL_set_fd(ssl, client);

        SSL_read(ssl, buf, sizeof(buf));
        cout << "----- Request ------" << endl;
        cout << buf << endl;
        cout << "--------------------" << endl;

        // Request request = parser.parse(data);
        Response response;
        response.version = "HTTP/1.1";
        response.status = 200;
        response.fields["Content-Length"] = "13";
        response.body = "Hello World";
        string result = parser.build(response);
        cout << "----- Response -----" << endl;
        cout << result << endl;
        cout << "--------------------" << endl;

        const char reply[] = "HTTP/1.1 200\nContent-Length:13\n\nHello World!\n";

        if (SSL_accept(ssl) <= 0) {
            ERR_print_errors_fp(stderr);
        } else {
            SSL_write(ssl, reply, strlen(reply));
        }

        SSL_shutdown(ssl);
        SSL_free(ssl);
        // close(client);
    }
    SSL_CTX_free(ctx);
    socket.finish();
    cout << "Stop" << endl;
}

