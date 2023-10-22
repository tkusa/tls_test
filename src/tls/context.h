#include <iostream>
#include "openssl/ssl.h"
#include "openssl/err.h"

using namespace std;

#ifndef TLS_CONTEXT_H
#define TLS_CONTEXT_H

namespace Tls
{
    class Context {
        public: 
            SSL_CTX *create_context();
            void configure_context(SSL_CTX *ctx);
    };
}

#endif