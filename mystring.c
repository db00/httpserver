/**
 * @file mystring.c
 gcc mystring.c array.c -Ddebug_strings && a  
 gcc mystring.c array.c -lm -Ddebug_strings && ./a.out
 * @author db0@qq.com
 * @version 1.0.1
 * @date 2015-07-22
 */


#include "mystring.h"

char * getSubStr(char * s,int start,int len)
{
	if(s == NULL || strlen(s)==0)
		return NULL;
	if(len<= 0)
		return NULL;
	if(start < 0)
		start = 0;
	int slen = strlen(s);
	int size = (len<slen?len:slen) + 1;
	//printf("size:%d\n",size);
	char * ret = malloc(size);
	memset(ret,0,size);
	//printf("s+start:%s\n",s+start);
	snprintf(ret,size,"%s",s+start);
	return ret;
}

char * getSubString(char * s,int start,int end)
{
	if(start<0)
		start = 0;
	int len = end - start + 1;
	return getSubStr(s,start,len);
}

String * String_new(int size)
{
	if(size>0){
		String * string = malloc(sizeof(*string));
		string->size = size;
		string->value = malloc(size);
		memset(string->value,0,size);
		return string;
	}
	return NULL;
}

void String_clear(String * string)
{
	if(string)
	{
		string->size = 0;
		if(string->value)
			free(string->value);
		free(string);
	}
}

String * String_resize(String * string,int size)
{
	if(size<=0)
	{
		String_clear(string);
		return NULL;
	}
	if(string == NULL)
		string = String_new(size);
	if(string->size != size)
	{
		string->value = realloc(string->value,size);
		string->value[size-1] = '\0';
		string->size = size;
	}
	return string;
}

#ifndef linux
int getpagesize()
{
	return 1024;
}
#endif

String * String_append(String * string,const char*fmt, ...)
{
	if(fmt==NULL || strlen(fmt)==0)
		return string;
	int n, size = getpagesize();
	char *tmp = NULL;
	va_list ap;
	if ((tmp = (char *) malloc(size)) == NULL){
		String_clear(string);
		return NULL;
	}
	while (1) {
		/* 尝试在申请的空间中进行打印操作 */
		va_start(ap, fmt);
		n = vsnprintf (tmp, size-1, fmt, ap);
		va_end(ap);
		/* 如果vsnprintf调用成功，返回该字符串 */
		if (n >= 0 && n < size-1){
			break;
		}
		/* vsnprintf调用失败(n<0)，或者tmp的空间不足够容纳size大小的字符串(n>=size)，尝试申请更大的空间*/
		size += getpagesize(); /* 再申请一个内存页 */
		if ((tmp = (char *)realloc(tmp, size)) == NULL)
		{
			String_clear(string);
			return NULL;
		}
	}
	if(string ==NULL){
		string = String_new(strlen(tmp)+1);
	}else{
		string = String_resize(string,string->size + strlen(tmp));
	}
	if(string == NULL){
		free(tmp);
		String_clear(string);
		return NULL;
	}
	string->value = strcat(string->value,tmp);
	free(tmp);
	return string;
}

String * String_printf(String * string,const char*fmt, ...)
{
	if(fmt==NULL || strlen(fmt)==0)
	{
		String_clear(string);
		return NULL;
	}
	int n, size = getpagesize();
	char *tmp = NULL;
	va_list ap;
	if ((tmp = (char *) malloc(size)) == NULL){
		String_clear(string);
		return NULL;
	}
	while (1) {
		/* 尝试在申请的空间中进行打印操作 */
		va_start(ap, fmt);
		n = vsnprintf (tmp, size-1, fmt, ap);
		va_end(ap);
		/* 如果vsnprintf调用成功，返回该字符串 */
		if (n >= 0 && n < size-1){
			break;
		}
		/* vsnprintf调用失败(n<0)，或者tmp的空间不足够容纳size大小的字符串(n>=size)，尝试申请更大的空间*/
		size += getpagesize(); /* 再申请一个内存页 */
		if ((tmp = (char *)realloc(tmp, size)) == NULL)
		{
			String_clear(string);
			return NULL;
		}
	}
	if(string ==NULL){
		string = String_new(strlen(tmp)+1);
	}else{
		string = String_resize(string,strlen(tmp)+1);
	}
	if(string == NULL){
		free(tmp);
		return NULL;
	}
	sprintf(string->value,"%s",tmp);
	free(tmp);
	return string;
}


char * append_str(char*old,const char*fmt, ...)
{
	if(fmt==NULL || strlen(fmt)==0)
		return old;
	int n, size = getpagesize();
	char *tmp = NULL;
	va_list ap;
	if ((tmp = (char *) malloc(size)) == NULL)
		return NULL;
	while (1) {
		/* 尝试在申请的空间中进行打印操作 */
		va_start(ap, fmt);
		n = vsnprintf (tmp, size-1, fmt, ap);
		va_end(ap);
		/* 如果vsnprintf调用成功，返回该字符串 */
		if (n >= 0 && n < size-1){
			break;
		}
		/* vsnprintf调用失败(n<0)，或者tmp的空间不足够容纳size大小的字符串(n>=size)，尝试申请更大的空间*/
		size += getpagesize(); /* 再申请一个内存页 */
		if ((tmp = (char *)realloc(tmp, size)) == NULL)
			return NULL;
	}
	if(old==NULL){
		old = malloc(strlen(tmp)+1);
		memset(old,0,strlen(tmp)+1);
	}else if(strlen(tmp)>0){
		old = realloc(old,strlen(tmp)+strlen(old)+1);
	}
	if(old==NULL){
		free(tmp);
		return NULL;
	}
	old = strcat(old,tmp);
	free(tmp);
	return old;
}


char* memstr(char* full_data, int full_data_len, char* substr)
{
	if (full_data == NULL || full_data_len <= 0 || substr == NULL) {
		return NULL;
	}

	if (*substr == '\0') {
		return NULL;
	}

	int sublen = strlen(substr);

	int i;
	char* cur = full_data;
	int last_possible = full_data_len - sublen + 1;
	for (i = 0; i < last_possible; i++) {
		if (*cur == *substr) {
			//assert(full_data_len - i >= sublen);
			if (memcmp(cur, substr, sublen) == 0) {
				//found
				return cur;
			}
		}
		cur++;
	}
	return NULL;
}

/**
 * 调用系统命令，并获取输出（相当于使用system）
 *
 * @param cmd要调用的系统命令  
 *
 * @return  
 */
char * mysystem(char *cmd,int * retlen)
{  
	if(retlen)*retlen = 0;
	if( NULL==cmd)  
		return NULL;  
	FILE *f;  
	int num_page = 1;
	int page_size = 1024;
	int size = page_size*num_page;
	char *output = malloc(size);
	int len = 0;
	memset(output, 0, size);
	//创建管道，并将cmd里的内容写入管道  
	f = popen(cmd, "r");  
	if(f==NULL){
		return NULL;
	}
	//从管理中读出数据，并写入output数组  
	len = fread(output, 1, size, f);  
	while(len==size)
	{
		++num_page;
		size = page_size*(num_page);
		output = realloc(output,size);
		len+=fread(output+len, 1, size-len, f);  
		//printf("%d <--> %d\n",size,len);
		fflush(stdout);
	}
	if(retlen)*retlen = len;
	pclose(f);
	return output;  
}

char *string_concat(Array*arr,char *cstr)
{
	if(arr == NULL)
		return NULL;
	int len = 1;
	int i = 0;
	int cstrlen = 0;
	if(cstr)
		cstrlen = strlen(cstr);
	while(i<arr->length)
	{
		len += strlen(Array_getByIndex(arr,i)) + cstrlen;
		++i;
	}
	char *ret = malloc(len);
	memset(ret,0,len);

	i = 0;
	while(i<arr->length-1)
	{
		strcat(ret,Array_getByIndex(arr,i));
		if(cstr)strcat(ret,cstr);
		++i;
	}
	strcat(ret,Array_getByIndex(arr,i));
	return ret;
}

Array*string_split(char *s,char *split_str)
{
	if(s == NULL || strlen(s)==0)
		return NULL;
	int slen = strlen(s);
	int splitlen = 0;
	if(split_str)
		splitlen = strlen(split_str);
	Array *arr = NULL;
	char * dump = malloc(slen+1);
	memcpy(dump,s,slen);
	dump[slen]='\0';
	if(split_str==NULL || strlen(split_str)==0)
	{
		arr = Array_resize(arr,1);
		arr = Array_setByIndex(arr,0,dump);
		return arr;
	}
	arr = Array_resize(arr,slen);
	int i = 0;
	Array_setByIndex(arr,i,dump);
	char *end = strstr(dump,split_str);
	while(end && end < dump + slen){
		++i;
		Array_setByIndex(arr,i, end + splitlen);
		char * start = end+splitlen;
		*end = '\0';
		if((int)(end-dump) + splitlen <= slen)
			end = strstr(start,split_str);
	}
	arr = Array_resize(arr,++i);
	return arr;
}


int freeArr(char**arr,int *len)
{
	int i=0;
	if(arr)
	{
		while(i<*len) {
			char *p = arr[i];
			if(p){
				free(p);
				p = NULL;
				arr[i]=NULL;
			}
			++i;
		}
		*len = 0;
	}
	return 0;
}

void * sortAndsearch(void*arr,size_t arr_len,size_t element_size,int (*cmpf)(const void *,const void *),const void*key)
{
	//char arr[][10]={"bac","bca","abc","acb","cba","cab"}; /* 定义二维字符数组*/
	//char *key="bca";/* 要查找的字符串*/
	/* 使用qsort对字符数组排序*/
	qsort((void *)arr,arr_len,element_size,(int (*)(const void *,const void *))cmpf);
	/* 采用二分查找查找指定字符*/
	return (char *)bsearch(key,arr,arr_len,element_size,(int (*)(const void *,const void *))cmpf);
}


int vspf(char*buffer,char *fmt, ...)
{
	va_list argptr;
	int cnt;
	va_start(argptr, fmt);
	cnt = vsprintf(buffer, fmt, argptr);
	va_end(argptr);
	return(cnt);
}

#ifdef debug_strings

int main(int argc, char *argv[])
{
	printf("%s\n",(char*)getSubStr("01234567890",2,1));
	printf("%s\n",getSubString("01234567890",2,4));

	int len;
	Array *arr = string_split("a good test string"," ");
	if(arr && arr->length>0)
	{
		int i = 0;
		while(i<arr->length)
		{
			char * s = Array_getByIndex(arr,i);
			printf("%d:%s:%d\n",i,s,strlen(s));
			++i;
		}
		printf("contact:%s",string_concat(arr,","));
		free(Array_getByIndex(arr,0));//all new data stored in arr[0]
		Array_clear(arr);
	}

	return 0;
}
#endif
