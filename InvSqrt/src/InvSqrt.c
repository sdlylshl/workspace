/*
 ============================================================================
 Name        : InvSqrt.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "math.h"
//最精简的1/sqrt()函数：
//卡马克(quake3作者) 0x5f3759df
//普渡大学的数学家Chris Lomont 0x5f375a86
float InvSqrt(float x)
{
	float xhalf = 0.5f*x;
	int i = *(int*)&x; // get bits for floating VALUE
	i = 0x5f375a86- (i>>1); // gives initial guess y0
	x = *(float*)&i; // convert bits BACK to float
	x = x*(1.5f-xhalf*x*x); // Newton step, repeating increases accuracy
	return x;
}
int main(void) {
	int j;
	float i= 15;
	float r;
	r = (float)(1/sqrt(i));
	printf("%f\n",r);
	r = (float)(InvSqrt(i));
	printf("%f\n",r);
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	return EXIT_SUCCESS;

}
