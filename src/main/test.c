#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "map.h"

#pragma warning(disable : 4996)
#define _CRT_SECURE_NO_DEPRECATE

int main()
{
	INT res = 0;
	/*--------------------------MAP-TEST-START------------------------- */
	Map map;
	res = map_init(&map);

	for (INT i = 1; i < 100; i++)
	{
		//CHAR loop[] = { 0 };
		//strcat(loop, __DATE__);	strcat(loop, STRING_SPACE);	strcat(loop, __TIME__);
		CHAR temp[10];
		_itoa_s(i, temp, 6, 10);
		CHAR keyloop[] = "KEY-";
		strcat(keyloop, temp);
		CHAR valueloop[] = "VALUE-";
		strcat(valueloop, temp);
		res = map_put(&map, keyloop, valueloop);
		//_sleep(2000);
	}

	CHAR key1[] = "key_2021_12_06_001";
	CHAR key2[] = "key_2021_12_06_002";
	CHAR key3[] = "key_2021_12_07_001";
	CHAR value1[] = "value_22:53_001";
	CHAR value2[] = "value_22:53_002";
	CHAR value3[] = "value_12:54_001";

	//put ok
	res = map_put(&map, key1, value1);
	res = map_put(&map, key2, value2);
	res = map_put(&map, key3, value3);
	//不知道为什么vs里printf放在下边就会报错，输出什么都不行，诡异

	//get ok
	CHAR get1[] = {0};
	res = map_get(&map, key1, get1);
	//printf("get1:%s\n", get1);
	//printf_s("get1:%s\n", get1);

	//put overwrite
	res = map_put(&map, key1, "999");
	CHAR get2[] = {0};
	res = map_get(&map, key1, get2);
	//printf("get2:%s\n", get2);

	//remove ok
	res = map_remove(&map, key1);
	CHAR get3[] = {0};
	res = map_get(&map, key1, get3);
	//printf("get3:%s\n", get3);

	//remove offset
	CHAR get4[] = {0};
	res = map_get(&map, key2, get4);
	//printf("get4:%s\n", get4);

	CHAR get5[] = {0};
	res = map_get(&map, key3, get5);
	//printf("get5:%s\n", get5);

	CHAR loop1[] = "temp1";
	CHAR loop2[] = "temp2";
	CHAR loop3[] = "temp3";
	res = map_put(&map, loop1, loop1);
	res = map_put(&map, loop2, loop2);
	res = map_put(&map, loop3, loop3);

	
	/*--------------------------MAP-TEST-END------------------------- */

	INT pause = 0;
	system("pause");

	return 0;
}