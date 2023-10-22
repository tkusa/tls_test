# compiler setting
CC = g++
CFLAGS = -Wall -g
LDFLAGS = -L/usr/lib/x86_64-linux-gnu/
LDLIBS = -lssl -lcrypto

SERVER_PROG = server
SERVER_OBJECTS = server.o socket.o request.o response.o parser.o context.o
OBJ = ./build/obj
BIN = ./build/bin
SRC = ./src
BINPROGS = $(addprefix $(BIN)/, $(SERVER_PROG))

all: prepare $(BINPROGS)

clean:
	rm -f $(OBJ)/* $(BIN)/*

prepare:
	mkdir -p $(OBJ);
	mkdir -p $(BIN);
	
# compile obj
$(OBJ)/%.o : $(SRC)/%.cpp
	$(COMPILE.cpp) $< -o $@

$(OBJ)/%.o : $(SRC)/connection/%.cpp
	$(COMPILE.cpp) $< -o $@

$(OBJ)/%.o : $(SRC)/http/%.cpp
	$(COMPILE.cpp) $< -o $@

$(OBJ)/%.o : $(SRC)/tls/%.cpp
	$(COMPILE.cpp) $< -o $@

# link server program
$(BIN)/$(SERVER_PROG): $(addprefix $(OBJ)/, $(SERVER_OBJECTS))
	$(LINK.o) $^ $(LDLIBS) -o $@

