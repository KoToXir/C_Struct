#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "map.h"
 
int main ()
{
   int res = 0;

   Map map;
   res = map_init(&map);

   char *key1 = "k1";
   char *key2 = "k2";
   char *value1 = "v1";
   char *value2 = "v2";

   res = map_put(&map,key1,value1);
   res = map_put(&map,key2,value2);

   return 0;
}