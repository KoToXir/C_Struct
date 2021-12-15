#include <stdint.h>
#include "type.h"
#ifndef MAP_H_
#define MAP_H_

#define MAP_INIT_SIZE 16

//版本控制预编译开关 只能保留一个开启不然会有大问题！
#define MAP_VERSION_1_0
//#define MAP_VERSION_1_1
//#define MAP_VERSION_1_2

typedef struct
{
	CHAR *key;
	CHAR *value;
} MapItem;

typedef struct
{
	MapItem *map;
	INT map_size;
	INT map_used;
} Map_1_0;

typedef struct
{
	INT map_size;
	INT map_used;
	MapItem map_data[];
} Map_1_1;

//根据map版本确定使用哪种结构
#ifdef MAP_VERSION_1_0
typedef Map_1_0 Map;
#endif
#ifdef MAP_VERSION_1_1
typedef Map_1_1 Map;
#endif


INT map_get(Map *obj, const CHAR *key, CHAR *value);
INT map_remove(Map *obj, const CHAR *key);
INT map_put(Map *obj, const CHAR *key, const CHAR *value);
INT map_init(Map *obj);

#endif /* MAP_H_ */
