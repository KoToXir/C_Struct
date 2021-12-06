#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "type.h"
#include "map.h"


CHAR* map_get(Map* obj, const CHAR* key)
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
	for (int index = 0; index < obj->map_used; index++) {
		item = NULL;
		item = (MapItem*)obj->map + index * sizeof(MapItem);
		//key is exitis
		if (item->key != NULL && strcmp(key, item->key) == 0) {
			/*INT val_len = strlen(item->value) + 1;
			if()*/
			CHAR res[STRING_LEN_100];
			strcpy(res, item->value);
			return &res;
		}
	}

	if (match == FALSE) {
		return NULL;
	}

	return STRING_EMPTY;
}


int map_remove(Map* obj, const CHAR* key)
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
	for (int index = 0; index < obj->map_used; index++) {
		item = NULL;
		item = (MapItem*)obj->map + index * sizeof(MapItem);
		//key is exist
		if (item->key != NULL && strcmp(key, item->key) == 0) {
			match = TRUE;
			free(item->key);
			item->key = NULL;
			free(item->value);
			item->value = NULL;
			//��ɾ��������ÿ�
			memset(item, 0x00, sizeof(MapItem));
			//���м�ɾ���ĳ��ϣ�Ҫ�Ѻ�ߵ��ڴ���ǰ��
			if (index != obj->map_used) {
				//����е��ң��п�����֤��
				memcpy(obj->map + index * sizeof(MapItem), obj->map + (index + 1) * sizeof(MapItem), (obj->map_used - index) * sizeof(MapItem));
				//��ǰ�ƶ���ɺ�����һ����0
				memset(obj->map + (obj->map_used - 1) * sizeof(MapItem), 0x00, sizeof(MapItem));
			}
			obj->map_used--;
			break;
		}
	}

	//key isn't exist
	if (match == FALSE) {
		return RES_MATCH_FAILED;
	}

	return RES_SUCCESS;
}

int map_put(Map* obj, const CHAR* key, const CHAR* value)
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
	for (int index = 0; index < obj->map_used; index++) {
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

int map_init(Map* obj) {
	obj->map = (MapItem*)calloc(MAP_INIT_SIZE, sizeof(MapItem));
	if (obj->map == NULL) {
		return RES_XALLOC_FAILED;
	}
	obj->map_size = MAP_INIT_SIZE;
	obj->map_used = 0;
	return RES_SUCCESS;
}