#pragma once
#define TCP_DATA_PACKET_SIZE	256

/**
  *		TCP data packet
  */
struct tcp_data_packet {
	int number;
	char data[TCP_DATA_PACKET_SIZE];
};
