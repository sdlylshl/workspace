/*
 ============================================================================
 Name        : LFSR.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
static uint8_t gzll_lfsr_get(uint8_t seed, uint8_t max_limit)
{
  static uint8_t pseudoreg = 0xff; // Can never be zero
  uint8_t shiftbit;

  if(seed > 0)
  {
    pseudoreg = seed;
  }

  shiftbit = (pseudoreg << 7) & 0x80;
  shiftbit ^= (pseudoreg << 6) & 0x80;
  shiftbit ^= (pseudoreg << 5) & 0x80;
  shiftbit ^= (pseudoreg & 0x80);

  pseudoreg = (shiftbit | (pseudoreg >> 1));

  return pseudoreg % max_limit;
}


//! \brief random seed
static uint16_t s_hwRandomSeed = 0xAA55;
static uint8_t s_chRandomTable[] = {
		0x12,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,
                0xF1,0xE2,0xD3,0xC4,0xB5,0xA6,0x97,0x88};


/*! \note set random generator seed
*  \param hwSeed random seed
*  \return none
*/
void set_random_seed( uint16_t hwSeed )
{
    s_hwRandomSeed ^= hwSeed;
}

/*! \note get a random integer
*  \param none
*  \return random integer value
*/
uint16_t get_random_u16( uint16_t hwSeed )
{
	static uint16_t s_hwRandomSeed = 0xAA55;
	static uint8_t s_chRandomTable[] = {0x21,0x23,0x45,0x76,0x89,0xAB,0xCD,0xEF,0x1F,0xE2,0xD3,0xC4,0xB5,0xA6,0x97,0x88};
    uint16_t *phwResult = (uint16_t *)&s_chRandomTable[(s_hwRandomSeed & 0x0E)];

    s_hwRandomSeed ^= hwSeed;
    *phwResult += s_hwRandomSeed;
    s_hwRandomSeed ^= *phwResult;

    return *phwResult;
}


int main(void) {
	int i;
	for(i=0;i<65000;i++){
		printf("%x ",get_random_u16(4)%0xff);
	}
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	return EXIT_SUCCESS;
}
