/*
 ============================================================================
 Name        : unionBits.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
typedef union {
  unsigned char value;
	struct {
		unsigned char prim_rx : 1;
		unsigned char pwr_up : 1;
		unsigned char crc0 : 1;
		unsigned char en_crc : 1;
		unsigned char mask_max_rt : 1;
		unsigned char mask_tx_ds : 1;
		unsigned char mask_rx_dr : 1;
		const unsigned char : 1;
	} bits;
} config_t;
int main_Bits(void) {

	config_t config;
	config.value = 0;
	config.bits.prim_rx = 1;
	printf("value%2x\n",config.value);
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	return EXIT_SUCCESS;
}
