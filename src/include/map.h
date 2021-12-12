

#include <stdint.h>
#include "type.h"
#ifndef MAP_H_
#define MAP_H_

#define MAP_INIT_SIZE 16
typedef struct
{
	CHAR* key;
	CHAR* value;
} MapItem;

typedef struct
{
	MapItem *map;
	INT map_size;
	INT map_used;
}Map;

typedef struct
{
	INT map_size;
	INT map_used;
	MapItem map_data[];
}Map_Arr;

INT map_get(Map *obj, const CHAR *key, CHAR *value);
int map_remove(Map *obj,const CHAR *key);
int map_put(Map *obj,const CHAR *key, const CHAR *value);
int map_init(Map *obj);

#endif /* MAP_H_ */
