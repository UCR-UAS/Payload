all: client server

client: client.cc
	g++ client.cc -pthread -o client

server: server.cc
	g++ server.cc -pthread -o server

clean:
	rm client server