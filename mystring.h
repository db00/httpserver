#ifndef __mystring_h__
#define __mystring_h__

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <malloc.h>
#include <string.h>
#include <unistd.h> //getpagesize

#include "array.h" //getpagesize

typedef struct String
{
	int size;
	char * value;
}String;


char * mysystem(char *cmd,int * retlen);
int vspf(char*buffer,char *fmt, ...);
char * append_str(char*old,const char*fmt, ...);
int freeArr(char**arr,int *len);
Array *string_split(char *s,char *split_str);
char * string_concat(Array *arr,char *cstr);
char * memstr(char* full_data, int full_data_len, char* substr);
char * String_sprintf(const char *fmt,...);
char * getSubString(char * s,int start,int end);
char * getSubStr(char * s,int start,int len);

String * String_new(int size);
void String_clear(String * string);
String * String_resize(String * string,int size);
String * String_append(String * string,const char*fmt, ...);
String * String_printf(String * string,const char*fmt, ...);

#endif
