/**
 * @file array.c
 gcc -Wall array.c -D test_array  && a 0
 gcc -Wall array.c -D test_array -o array && ./array 0
 * @author db0@qq.com
 * @version 1.0.1
 * @date 2016-01-12
 */
#include "array.h"

Array * Array_new()
{
	Array * array = malloc(sizeof(Array));
	memset(array,0,sizeof(Array));
	return array;
}
void Array_clear(Array * array)
{
	if(array)
	{
		if(array->length>0)
		{
			free(array->data);
		}
		free(array);
	}
}
Array * Array_resize(Array* array,int i)
{
	if(array==NULL)
		array = Array_new();
	if(i>0)
	{
		if(array->length==0)
		{
			array->data = malloc(i*sizeof(void*));
			memset(array->data,0,i*sizeof(void*));
		}else{
			array->data = realloc(array->data,i*sizeof(void*));
			if(i>array->length)
				memset(&(array->data[array->length]),0,(i-array->length)*sizeof(void*));
		}
		array->length = i;
		return array;
	}
	if(array->length>0)
		free(array->data);
	array->length = 0;
	array->data = NULL;
	return array;
}
Array* Array_push(Array * array,void * d)
{
	if(array==NULL)
		array = Array_new();
	array = Array_resize(array,array->length+1);
	array->data[array->length-1] = d;
	return array;
}
void * Array_getByIndex(Array * array,int i)
{
	if(array==NULL)
		return NULL;
	void * data = NULL;
	if(0<=i && i<array->length)
	{
		data = array->data[i];
	}
	return data;
}
Array * Array_setByIndex(Array * array,int i,void * data)
{
	if(array==NULL)
		array = Array_new();
	if(i>=0)
	{
		if(i>=array->length)
		{
			array = Array_resize(array,i+1);
		}
		array->data[i]=data;
	}
	return array;
}
Array * Array_insert(Array * array,int i,void * data)
{
	if(array==NULL)
		array = Array_new();
	if(i>=0)
	{
		if(i>array->length)
		{
			array = Array_resize(array,i+1);
		}else{
			array = Array_resize(array,array->length+1);
			memmove(&(array->data[i+1]),&(array->data[i]),(array->length-i-1)*sizeof(void*));
		}
		array->data[i]=data;
	}
	return array;
}
Array * Array_removeByIndexs(Array*array,int start,int end)
{
	if(array==NULL)
		return NULL;
	if(start<0)
		start = 0;
	if(end>=array->length)
		end = array->length-1;
	int num = end-start+1;
	if(num>=0 && num<=array->length)
	{
		memmove(&(array->data[start]),&(array->data[start+num]),(array->length-start-num)*sizeof(void*));
		array = Array_resize(array,array->length-num);
	}
	return array;
}
Array * Array_removeByIndex(Array*array,int i)
{
	if(array==NULL)
		return NULL;
	if(i>=0 && i<array->length)
	{
		memmove(&(array->data[i]),&(array->data[i+1]),(array->length-i-1)*sizeof(void*));
		array = Array_resize(array,array->length-1);
	}
	return array;
}
int Array_getIndexByValue(Array *array,void * value)
{
	if(array && value){
		int i = 0;
		while(i<array->length)
		{
			if(Array_getByIndex(array,i)==value)
				return i;
			++i;
		}
	}
	return -1;
}
Array * Array_getByIndexs(Array * array,int start,int end)
{
	if(start>=array->length)
		return NULL;
	if(end<0)
		return NULL;
	if(array==NULL)
		array = Array_new();
	Array * ret=NULL;
	end = array->length-1;
	if(start<0)
		start=0;
	if(end>=array->length)
		end = array->length-1;
	if(end>=start)
	{
		int i = start;
		while(i<=end)
		{
			char * data = array->data[i];
			Array_push(ret,data);
			++i;
		}
	}
	return ret;
}

Array * Array_concat(Array * array,Array * array2)
{
	if(array ==NULL)
	{
		array = Array_new();
	}
	if(array2==NULL || array2->length==0)
		return array;
	int len = array->length;
	array = Array_resize(array,array->length+array2->length);
	memcpy(&(array->data[len]),array2->data,array2->length*sizeof(void*));
	return array;
}

Array * Array_sort(Array * array,int (*sort)(const void *,const void *))
{
	qsort((void *)array->data,array->length,sizeof(void*),(int (*)(const void *,const void *))sort);
	return array;
}

void* Array_search(Array * array,void * key,int (*sort)(const void *,const void *))//必须先排序
{
	//qsort((void *)array->data,array->length,sizeof(void*),(int (*)(const void *,const void *))sort);//
	return (void *)bsearch(key,array->data,array->length,sizeof(void*),(int (*)(const void *,const void *))sort);
}

void Array_print(Array * array)
{
	if(array==NULL)
	{
		printf("NULL\n");
		return;
	}
	int i=0;
	printf("[");
	while(i<array->length)
	{
#ifdef __x86_64__
		printf("%d:%llx,",i,(unsigned long long )(array->data[i]));
#elif __i386__
		printf("%d:%x,",i,(unsigned)(array->data[i]));
#endif
		//printf("%d:%s,",i,(array->data[i]));
		++i;
	}
	printf("]\n");
}

#ifdef test_array
int main(int argc,char**argv)
{
	int i=0;
	while(i<argc)
	{
		printf("%d:%s\n",i,argv[i]);
		++i;
	}

	Array * array =Array_new();
	Array_print(array);
	char * a="1";
	Array_push(array,a);
	Array_print(array);
	a = "2";
	Array_push(array,a);
	a = "3";
	Array_push(array,a);
	a = "4";
	Array_push(array,a);
	a = "5";
	Array_push(array,a);
	a = "6";
	Array_push(array,a);
	Array_print(array);
	Array_removeByIndex(array,0);
	Array_print(array);
	Array_removeByIndexs(array,0,1);
	Array_print(array);
	a = "iiiiiiiiii";
	Array_insert(array,9,a);
	Array_print(array);
	Array_removeByIndexs(array,1,8);
	Array_print(array);
	return 0;
}
#endif
