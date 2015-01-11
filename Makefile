INC = -Iinclude
SRC = src/address.c src/networking.c src/packet.c src/socket.c
OUT = libnetworking.so

build: $(SRC)
	gcc -fpic -shared -o $(OUT) $(INC) $(SRC)

clean:
	rm $(OUT)

install:
	cp $(OUT) /usr/local/lib/

rebuild: clean build

