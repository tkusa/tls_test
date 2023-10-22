# Simple TLS Server

## Usage
openssl is required
```
sudo apt install libssl-dev
```

build
```
make
```

generate cert
```
openssl genrsa 4096 > key.pem
openssl req -new -key key.pem > server.csr
openssl x509 -req -days 3650 -signkey key.pem < server.csr > cert.pem
```
place them to build/bin

start
```
sudo ./build/bin/server
```


## Reference
- [OpenSSL Simple TLS Server](https://wiki.openssl.org/index.php/Simple_TLS_Server)
- [RFC 8446](https://www.rfc-editor.org/rfc/rfc8446)