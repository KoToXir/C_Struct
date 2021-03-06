#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compile.h"
#ifdef VSC_COMPILE
#include "../include/type.h"
#include "../include/map.h"
#else
#include "type.h"
#include "map.h"
#endif

//版本区分函数声明
INT map_get_1_0(Map *obj, const CHAR *key, CHAR *value);
INT map_remove_1_0(Map *obj, const CHAR *key);
INT map_put_1_0(Map *obj, const CHAR *key, const CHAR *value);
INT map_init_1_0(Map *obj);

//实际调用函数
INT map_get(Map *obj, const CHAR *key, CHAR *value)
{
#ifdef MAP_VERSION_1_0
	return map_get_1_0(obj, key, value);
#endif
}

INT map_remove(Map *obj, const CHAR *key)
{
#ifdef MAP_VERSION_1_0
	return map_remove_1_0(obj, key);
#endif
}

INT map_put(Map *obj, const CHAR *key, const CHAR *value)
{
#ifdef MAP_VERSION_1_0
	return map_put_1_0(obj, key, value);
#endif
}

INT map_init(Map *obj){
#ifdef MAP_VERSION_1_0
	return map_init_1_0(obj);
#endif
}

//版本区分函数定义
INT map_get_1_0(Map *obj, const CHAR *key, CHAR *value)
{
	if (obj == NULL || key == NULL)
	{
		return RES_PARAM_FAILED;
	}

	if (obj->map_size <= 0)
	{
		return RES_PARAM_FAILED;
	}

	if (obj->map_used < 0)
	{
		return RES_PARAM_FAILED;
	}

	for (INT index = 0; index < obj->map_used; index++)
	{
		MapItem *item = NULL;
		item = (MapItem *)(obj->map + index * sizeof(MapItem));
		//key is exitis
		if (item->key != NULL && strcmp(key, item->key) == 0)
		{
			strcpy(value, item->value);
			return RES_SUCCESS;
		}
	}

	return RES_MATCH_FAILED;
}

INT map_remove_1_0(Map *obj, const CHAR *key)
{
	if (obj == NULL || key == NULL)
	{
		return RES_PARAM_FAILED;
	}

	if (obj->map_size <= 0)
	{
		return RES_PARAM_FAILED;
	}

	if (obj->map_used < 0)
	{
		return RES_PARAM_FAILED;
	}

	BOOL match = FALSE;
	for (INT index = 0; index < obj->map_used; index++)
	{

		MapItem *item = NULL;
		item = (MapItem *)(obj->map + index * sizeof(MapItem));
		//key is exist
		if (item->key != NULL && strcmp(key, item->key) == 0)
		{
			match = TRUE;
			free(item->key);
			item->key = NULL;
			free(item->value);
			item->value = NULL;
			//把删掉的这块置空
			memset(item, 0x00, sizeof(MapItem));
			//从中间删除的场合，要把后边的内存往前移
			if ((index + 1) != obj->map_used)
			{
				//逐个往前移动，如果直接整块移后边的无法覆盖前边有数据的地址
				for (INT delete_index = index; delete_index + 1 < obj->map_used; delete_index++)
				{
					memcpy(obj->map + delete_index * sizeof(MapItem), obj->map + (delete_index + 1) * sizeof(MapItem), sizeof(MapItem));
				}
				obj->map_used--;
				//往前移动完成后把最后一组置0
				memset(obj->map + (obj->map_used) * sizeof(MapItem), 0x00, sizeof(MapItem));
			}
			break;
		}
	}

	//key isn't exist
	if (match == FALSE)
	{
		return RES_MATCH_FAILED;
	}

	return RES_SUCCESS;
}

INT map_put_1_0(Map *obj, const CHAR *key, const CHAR *value)
{
	if (obj == NULL || key == NULL || value == NULL)
	{
		return RES_PARAM_FAILED;
	}

	if (obj->map_size <= 0)
	{
		return RES_PARAM_FAILED;
	}

	if (obj->map_used < 0)
	{
		return RES_PARAM_FAILED;
	}

	CHAR *key_new = NULL;
	CHAR *value_new = NULL;
	BOOL match = FALSE;
	MapItem *item;
	for (INT index = 0; index < obj->map_used; index++)
	{
		item = NULL;
		item = (MapItem *)(obj->map + index * sizeof(MapItem));
		//key is exist
		if (item->key != NULL && strcmp(key, item->key) == 0)
		{
			//create new space
			value_new = (CHAR *)malloc(strlen(value) + 1);
			if (value_new == NULL)
			{
				return RES_XALLOC_FAILED;
			}
			memset(value_new, 0x00, strlen(value + 1));
			strcpy(value_new, value);
			//delete old space
			free(item->value);
			item->value = NULL;
			//point updata
			item->value = value_new;
			match = TRUE;
			break;
		}
	}

	//key isn't exist
	if (match == FALSE)
	{
		//size expand if used 75% then up to 150%
		FLOAT size = obj->map_size;
		FLOAT used = obj->map_used;
		FLOAT aim = (used / size);
		if (used != 0 && aim >= 0.75)
		{
			INT size_new = (INT)(used * 1.5 + 1);
			//1.5=>1 no effictive! aim+1
			MapItem *map_new = (MapItem *)malloc(size_new * sizeof(MapItem));
			if (map_new == NULL)
			{
				return RES_XALLOC_FAILED;
			}
			memset(map_new, 0x00, size_new * sizeof(MapItem));
			memcpy(map_new, obj->map, obj->map_size * sizeof(MapItem));
			free(obj->map);
			obj->map = map_new;
			obj->map_size = size_new;
		}

		//add new item
		item = (MapItem *)obj->map + obj->map_used * sizeof(MapItem);
		key_new = (CHAR *)malloc(strlen(key) + 1);
		if (key_new == NULL)
		{
			return RES_XALLOC_FAILED;
		}
		memset(key_new, 0x00, strlen(key) + 1);
		value_new = (CHAR *)malloc(strlen(value) + 1);
		if (value_new == NULL)
		{
			free(key_new);
			key_new = NULL;
			return RES_XALLOC_FAILED;
		}
		memset(value_new, 0x00, strlen(value) + 1);
		strcpy(key_new, key);
		strcpy(value_new, value);
		item->key = key_new;
		item->value = value_new;
		obj->map_used++;
	}

	return RES_SUCCESS;
}

INT map_init_1_0(Map *obj)
{
	obj->map = (MapItem *)malloc(MAP_INIT_SIZE * sizeof(MapItem));
	if (obj->map == NULL)
	{
		return RES_XALLOC_FAILED;
	}
	memset(obj->map, 0x00, MAP_INIT_SIZE * sizeof(MapItem));
	obj->map_size = MAP_INIT_SIZE;
	obj->map_used = 0;
	return RES_SUCCESS;
}