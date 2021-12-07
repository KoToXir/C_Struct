#include <stdint.h>
#include "type.h"
#ifndef LIST_H_
#define LIST_H_

#define LIST_INIT_SIZE 16
typedef struct
{
	CHAR* value;
} ListItem;

typedef struct
{
	ListItem *head;
	INT map_size;
	INT map_used;
}List;

// INT map_get(Map *obj,const CHAR *key, CHAR* value);
// INT map_remove(Map *obj,const CHAR *key);
// INT map_put(Map *obj,const CHAR *key, const CHAR *value);
INT list_init(List *obj);

#endif /* LIST_H_ */
