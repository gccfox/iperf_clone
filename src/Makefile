CC = g++
all: main controller models views view_controller
	$(CC) main.o concrete_controller.o tcp_client_model.o udp_client_model.o tcp_server_model.o udp_server_model.o error_view.o view_controller.o -o iperf_clone -lstdc++ -lpthread -lrt

main: main.cpp controller
	$(CC) -c main.cpp

controller: concrete_controller.cpp 
	$(CC) -c concrete_controller.cpp 

models: tcp_client_model udp_client_model tcp_server_model udp_server_model

tcp_client_model: tcp_client_model.cpp
	$(CC) -c tcp_client_model.cpp

udp_client_model: udp_client_model.cpp
	$(CC) -c udp_client_model.cpp

tcp_server_model: tcp_server_model.cpp
	$(CC) -c tcp_server_model.cpp

udp_server_model: udp_server_model.cpp
	$(CC) -c udp_server_model.cpp

views: error_view

view_controller: view_controller.cpp
	$(CC) -c view_controller.cpp
	
error_view: error_view.cpp
	$(CC) -c error_view.cpp	

clean:
	rm -f *.o
	rm iperf_clone
	rm -f *.h.gch
