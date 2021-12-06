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


   char key1[128] = "k1";
   char key2[128] = "k2";
   char value1[128] = "v1";
   char value2[128] = "v2";

   res = map_put(&map,key1,value1);
   res = map_put(&map,key1,value2);

   
   int  var = 20;   /* 实际变量的声明 */
   int  *ip;        /* 指针变量的声明 */
 
   ip = &var;  /* 在指针变量中存储 vfar 的地址 */
 
   printf("Address of var variable: %p\n", &var  );
 
   /* 在指针变量中存储的地址 */
   printf("Address stored in ip variable: %p\n", ip );
 
   /* 使用指针访问值 */
   printf("Value of *ip variable: %d\n", *ip );
 
   return 0;
}