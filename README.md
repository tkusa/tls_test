# Simple HTTP Server

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

- [RFC 9112](https://datatracker.ietf.org/doc/html/rfc9112)