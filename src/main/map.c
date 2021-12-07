#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "type.h"
#include "map.h"


INT map_get(Map* obj, const CHAR* key, CHAR* value)
{
	if (obj == NULL || key == NULL) {
		return RES_PARAM_FAILED;
	}

	if (obj->map_size <= 0) {
		return RES_PARAM_FAILED;
	}

	if (obj->map_used < 0) {
		return RES_PARAM_FAILED;
	}

	BOOL match = FALSE;
	MapItem* item;
	for (INT index = 0; index < obj->map_used; index++) {
		item = NULL;
		item = (MapItem*)obj->map + index * sizeof(MapItem);
		//key is exitis
		if (item->key != NULL && strcmp(key, item->key) == 0) {
			match = TRUE;
         	strcpy(value,item->value);
			return RES_SUCCESS;
		}
	}

	if (match == FALSE) {
		return RES_MATCH_FAILED;
	}

	return RES_SUCCESS;
}


INT map_remove(Map* obj, const CHAR* key)
{
	if (obj == NULL || key == NULL) {
		return RES_PARAM_FAILED;
	}

	if (obj->map_size <= 0) {
		return RES_PARAM_FAILED;
	}

	if (obj->map_used < 0) {
		return RES_PARAM_FAILED;
	}

	BOOL match = FALSE;
	MapItem* item;
	for (INT index = 0; index < obj->map_used; index++) {
		item = NULL;
		item = (MapItem*)obj->map + index * sizeof(MapItem);
		//key is exist
		if (item->key != NULL && strcmp(key, item->key) == 0) {
			match = TRUE;
			free(item->key);
			item->key = NULL;
			free(item->value);
			item->value = NULL;
			//把删掉的这块置空
			memset(item, 0x00, sizeof(MapItem));
			//从中间删除的场合，要把后边的内存往前移
			if ((index + 1) != obj->map_used) {
				//这块有点乱，有空在验证下
				memcpy(obj->map + index * sizeof(MapItem), obj->map + (index + 1) * sizeof(MapItem), (obj->map_used - index - 1) * sizeof(MapItem));
				obj->map_used--;
				//往前移动完成后把最后一组置0
				memset(obj->map + (obj->map_used) * sizeof(MapItem), 0x00, sizeof(MapItem));
			}
			break;
		}
	}

	//key isn't exist
	if (match == FALSE) {
		return RES_MATCH_FAILED;
	}

	return RES_SUCCESS;
}

INT map_put(Map* obj, const CHAR* key, const CHAR* value)
{
	if (obj == NULL || key == NULL || value == NULL) {
		return RES_PARAM_FAILED;
	}

	if (obj->map_size <= 0) {
		return RES_PARAM_FAILED;
	}

	if (obj->map_used < 0) {
		return RES_PARAM_FAILED;
	}

	CHAR* key_new;
	CHAR* value_new;
	BOOL match = FALSE;
	MapItem* item;
	for (INT index = 0; index < obj->map_used; index++) {
		item = NULL;
		item = (MapItem*)obj->map + index * sizeof(MapItem);
		//key is exist
		if (item->key != NULL && strcmp(key, item->key) == 0) {
			//create new space
			value_new = (char*)calloc(1, strlen(value) + 1);
			if (value_new == NULL) {
				return RES_XALLOC_FAILED;
			}
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
	if (match == FALSE) {
		//size expand if used 75% then up to 150%
		FLOAT size = obj->map_size;
		FLOAT used = obj->map_used;
		FLOAT aim = (used/size);
		if(used != 0 && aim >= 0.75){
			INT size_new = (INT)(used * 1.5 + 1);
			//1.5=>1 no effictive! aim+1
			MapItem *map_new = (MapItem*)calloc(size_new, sizeof(MapItem));
			if(map_new == NULL){
				return RES_XALLOC_FAILED;
			}
			memcpy(map_new,obj->map,obj->map_size * sizeof(MapItem));
			free(obj->map);
			obj->map = map_new;
			obj->map_size = size_new;
		}

		//add new item
		item = (MapItem*)obj->map + obj->map_used * sizeof(MapItem);
		key_new = (char*)calloc(1, strlen(key) + 1);
		if (key_new == NULL) {
			return RES_XALLOC_FAILED;
		}
		value_new = (char*)calloc(1, strlen(value) + 1);
		if (value_new == NULL) {
			return RES_XALLOC_FAILED;
		}
		strcpy(key_new, key);
		strcpy(value_new, value);
		item->key = key_new;
		item->value = value_new;
		obj->map_used ++;
	}

	return RES_SUCCESS;
}

INT map_init(Map* obj) {
	obj->map = (MapItem*)calloc(MAP_INIT_SIZE, sizeof(MapItem));
	if (obj->map == NULL) {
		return RES_XALLOC_FAILED;
	}
	obj->map_size = MAP_INIT_SIZE;
	obj->map_used = 0;
	return RES_SUCCESS;
}