/* Copyright (c) ARM Ltd 2007, All Rights Reserved. */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define NoOfElements 16
#define NoOfBits 4
#define DUMP 1
typedef struct 
{
    int R;
    int I;
} Complex;

typedef struct 
{
    long int R;
    long int I;
} LongComplex;

static Complex  Spectrum[NoOfElements];

static Complex W[]= 
{   
    {16383, 0},
    {15136, -6269},
    {11585, -11585},
    {6269, -15136},
    {0, -16383},
    {-6269, -15136},
    {-11585, -11585},
    {-15136, -6269},
    {-16383, 0},
    {-15136, 6269},
    {-11585, 11585},
    {-6269, 15136},
    {0, 16384},
    {6269, 15136},
    {11585, 11585},
    {15136, 6269} 
};

static Complex Data[]= 
{ 
    {90, 0},
    {0, 0},
    {-90, 0},
    {127, 0},
    {-90, 0},
    {0, 0},
    {90, 0},
    {-127, 0},
    {90, 0},
    {0, 0},
    {-90, 0},
    {127, 0},
    {-90, 0},
    {0, 0},
    {90, 0},
    {-127, 0} 
};

static unsigned Rot(unsigned num, unsigned lsb)
{
    return (num << 1) + lsb;
}

static unsigned BitReverse (unsigned num)
{
    unsigned Looper,
             Result;

    Result = 0;
    for (Looper = 0; Looper < NoOfBits; ++Looper) 
    {
        Result = Rot(Result, num & 1);
        num = num >> 1;
    }
    return (Result);
}

static void FFT (Complex *Data, Complex *Spectrum, Complex *W)
{
    Complex m, fp, fq, Wnum;
    unsigned p, q, Pof2, KStep, JLimit;
    LongComplex modifier;
    int Looper, L, J, K;

    for (Looper = 0; Looper < NoOfElements; ++Looper)
        Spectrum[BitReverse(Looper)] = Data[Looper];

    Pof2 = NoOfBits;
    KStep = 1;
    for (L = 1; L <= NoOfBits; ++L) 
    {
        JLimit = KStep-1;
        KStep <<= 1;
        --Pof2;
        for (J = 0; J <= JLimit; ++J) 
        {
            Wnum = W[(J << Pof2) & (NoOfElements-1)];
            for (K = 0; K <= NoOfElements-KStep; K+=KStep) 
            {
                p = J+K;
                q = p + JLimit + 1;
                fq = Spectrum[q];
                fp = Spectrum[p];
                modifier.R = (long int) fq.R * (long int) Wnum.R - 
                             (long int) fq.I * (long int) Wnum.I;
                modifier.I = (long int) fq.R * (long int) Wnum.I + 
                             (long int) fq.I * (long int)Wnum.R;
                m.R = (int) (modifier.R >> 14);
                m.I = (int) (modifier.I >> 14);
                Spectrum[q].R = fp.R - m.R;
                Spectrum[q].I = fp.I - m.I;
                Spectrum[p].R = fp.R + m.R;
                Spectrum[p].I = fp.I + m.I;
            }
        }
    }
}

int main(int argc, char **argv) {
	int Looper;
	for ( Looper = 0; Looper < 100000; Looper++) {
		FFT(Data, Spectrum, W);
	}
#if DUMP
	for ( Looper = 0 ; Looper < NoOfElements ; ++Looper ) {
    	double Power = Spectrum[Looper].R*Spectrum[Looper].R + Spectrum[Looper].I*Spectrum[Looper].I;
      	Power = sqrt(Power);
      	printf(" n = %4d  \tS[n].R = %10G   \tS[n].I = %10G  \tPower = %10G\n",
             Looper,
             (double)Spectrum[Looper].R,
             (double)Spectrum[Looper].I, 
             Power );
   	}
#endif
	return 0;
}
