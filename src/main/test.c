#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "map.h"

int main()
{
	INT res = 0;

	/*--------------------------map²âÊÔ´úÂë-START------------------------- */
	Map map;
	res = map_init(&map);

	CHAR* key1 = "key_2021_12_06_001";
	CHAR* key2 = "key_2021_12_06_002";
	CHAR* value1 = "value_22:53_001";
	CHAR* value2 = "value_22:53_002";

	res = map_put(&map, key1, value1);
	res = map_put(&map, key2, value2);
	CHAR* get1 = map_get(&map, key1);

	//CHAR* get2 = map_get(&map, key2);
	printf("get1:%p\n", get1);
	//printf("get2:%s", get2);
	res = map_remove(&map, key2);
	CHAR* get3 = map_get(&map, key2);

	/*--------------------------map²âÊÔ´úÂë-END------------------------- */

	INT pause = 0;

	return 0;
}