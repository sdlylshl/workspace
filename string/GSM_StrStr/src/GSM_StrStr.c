/*
 ============================================================================
 Name        : GSM_StrStr.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
//strstr(string,search) 函数搜索一个字符串在另一个字符串中的第一次出现。找到所搜索的字符串，则该函数返回第一次匹配的字符串的地址
char strstr (const char * Main_str,const char * search_str)
{
    char i;
    char *cp = (char *)Main_str;
    char *s1, *s2;

    if ( !*search_str )
        return(-1);

    while (*cp) {

        s1 = cp;
        s2 = (char *) search_str;

        while ( *s1 && *s2 && !(*s1-*s2) )
            s1++, s2++;

        if (!*s2)
            return(i);

        cp++;i++;
    }

    return(-1);

}
char *  mystrstr (
        const char * str1,
        const char * str2
        )
{
        char *cp = (char *) str1;
        char *s1, *s2;

        if ( !*str2 )
            return((char *)str1);

        while (*cp)
        {
                s1 = cp;
                s2 = (char *) str2;

                while ( *s1 && *s2 && !(*s1-*s2) )
                        s1++, s2++;

                if (!*s2)
                        return(cp);

                cp++;
        }

        return(NULL);

}
int strlens (const char * str)
{
        const char *eos = str;

        while( *eos++ ) ;

        return( (int)(eos - str - 1) );
}
int main(void) {
	char num;
	num = strstr("12345678","78");
	printf("%d",strlens("1"));
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	return EXIT_SUCCESS;
}
