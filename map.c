#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "map.h"

int map_remove(Map *obj,const CHAR *key)
{
   // if(obj == NULL){
   //    return -1;
   // }

   // if(obj->map_size <= 0){
   //    return -1;
   // }

   // if(obj->map_used < 0 || obj->map_used >= obj->map_size){
   //    return -1;
   // }

   // BOOL match = FALSE;
   // MapItem *item;
   // for(int index = 0;index < obj->map_used; index++){
   //    item = NULL;
   //    item = (MapItem*)obj->map + index * sizeof(MapItem);

   //    if(item->key != NULL && strcmp(key,item->key) == 0){
   //       item->value = (char*) realloc(item->value,strlen(value)+1);
   //       strcpy(item->value, value);
   //       match = TRUE;
   //       break;
   //    }
   // }

   // if(match == FALSE){
   //    item = (MapItem*)obj->map + obj->map_used * sizeof(MapItem);
   //    item->key = (char*) calloc(1,strlen(key)+1);
   //    strcpy(item->key, key);
   //    item->value = (char*) calloc(1,strlen(value)+1);
   //    strcpy(item->value, value);
   //    obj->map_used += 1;
   // }
   
   return 0;
}

int map_put(Map *obj,const CHAR *key, const CHAR *value)
{
   if(obj == NULL){
      return -1;
   }

   if(obj->map_size <= 0){
      return -1;
   }

   if(obj->map_used < 0){
      return -1;
   }

   BOOL match = FALSE;
   MapItem *item;
   for(int index = 0;index < obj->map_used; index++){
      item = NULL;
      item = (MapItem*)obj->map + index * sizeof(MapItem);

      if(item->key != NULL && strcmp(key,item->key) == 0){
         item->value = (char*) realloc(item->value,strlen(value)+1);
         strcpy(item->value, value);
         match = TRUE;
         break;
      }
   }

   if(match == FALSE){
      item = (MapItem*)obj->map + obj->map_used * sizeof(MapItem);
      item->key = (char*) calloc(1,strlen(key)+1);
      strcpy(item->key, key);
      item->value = (char*) calloc(1,strlen(value)+1);
      strcpy(item->value, value);
      obj->map_used += 1;
   }

   return 0;
}

int map_init(Map *obj){
   obj->map = (MapItem*)calloc(MAP_INIT_SIZE, sizeof(MapItem));
   if(obj->map == NULL){
      return 1;
   }
   obj->map_size = MAP_INIT_SIZE;
   obj->map_used = 0;
   return 0;
}