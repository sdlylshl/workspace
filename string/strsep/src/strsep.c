/*
 ============================================================================
 Name        : strsep.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
//在字符串中查找给定字符第一个匹配处
char * strchr (
        const char * string,
        int ch
        )
{
        while (*string && *string != (char)ch)
                string++;

        if (*string == (char)ch)
                return((char *)string);
        return(NULL);
}
//在字符串中查找给定字符集中的字符
char * strpbrk( register const char *cs, register const char *delim )
{
        register const char *search;

        do
        {
                for( search=delim; *search && *search!=*cs; search++ )
                        ;       /* look if character from cs is also in delim */

                if( *search )           /* if found the character in delim, */
                        return( (char *)cs );   /* return pointer        */
        } while( *cs++ );

        return( NULL );                 /* no matching character found     */
}
//字符串分隔
char * strsep (char **stringp, const char *delim)
{
  char *begin, *end;

  begin = *stringp;
  if (begin == NULL)
    return NULL;

  /** A frequent case is when the delimiter string contains only one
     character.  Here we don't need to call the expensive `strpbrk'
     function and instead work using `strchr'.  */
  if (delim[0] == '\0' || delim[1] == '\0')
    {
      char ch = delim[0];

      if (ch == '\0')
	end = NULL;
      else
	{
	  if (*begin == ch)
	    end = begin;
	  else if (*begin == '\0')
	    end = NULL;
	  else
	    end = strchr (begin + 1, ch);
	}
    }
  else
    /** Find the end of the token.  */
    end = strpbrk (begin, delim);

  if (end)
    {
      /** Terminate the token and set *STRINGP past NUL character.  */
      *end++ = '\0';
      *stringp = end;
    }
  else
    /** No more delimiters; this is the last token.  */
    *stringp = NULL;

  return begin;
}
int main(void) {
	char str1[]="x=\n12\nab";
	char *p=str1;
	char *tk,tk1;

	tk=strsep (&p, "\n");

	printf("%s\n",tk); /* prints !!!Hello World!!! */
	tk=strsep (&p, "\n");

	printf("%s\n",tk); /* prints !!!Hello World!!! */

	return EXIT_SUCCESS;
}
