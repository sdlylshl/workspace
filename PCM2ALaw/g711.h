/*******************************************************
*	��������ҵĲ��͡�JRTPLIB@Conference DIY��Ƶ����ϵͳ��
*	��д��һ���׶���ʵ�顣
*	���ߣ��븻�� tinnal
*	���䣺tinnal@163.com
*	���ͣ�www.cnitblog.com/tinnal/
*	Ŀ�ڣ�2009-01-03
*	�汾��1.00
*********************************************************/

#ifndef _G711_H_
#define _G711_H_

//����һ��ʵ��
unsigned char ALawEncode(int pcm16);
int ALawDecode(unsigned char alaw);

//��һ��ʵ��
unsigned char	linear2alaw	( int pcm_val);
int				alaw2linear	( unsigned char a_val);
unsigned char	linear2ulaw	( int pcm_val);
int				ulaw2linear	( unsigned char u_val);
unsigned char	alaw2ulaw	( unsigned char aval);
unsigned char	ulaw2alaw	( unsigned char uval);

#endif