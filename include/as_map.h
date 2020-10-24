#ifndef __AS_MAP_H__
#define __AS_MAP_H__

#include "as_general.h"
#include "as_list.h"


typedef as_map {
    uint64_t size;
    uint64_t element_size;
    list_t heads[MAX_MAP_HEAD];
    int(*GetCondition)(const void* elem, const void* desire);
} map_t;

void map_Init(map_t* map, const uint64_t elem_size);
void map_Destroy(map_t *map);
void map_Insert(map_t* map, const void* key, const uint64_t key_nbytes, const void* data);
void *map_Get(map_t* map, const void* key, const uint64_t key_nbytes);


#endif