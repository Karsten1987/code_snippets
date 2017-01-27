#ifndef MAP_H_
#define MAP_H_

#if __cplusplus
extern "C"
{
#endif

typedef struct _element
{
  const char* element_data;
} Element;

typedef struct _data_array
{
  Element* data;
  unsigned int size;
} DataArray;

typedef struct _index
{
  unsigned int index;
  const char* label;
} Index;

typedef struct _map
{
  Index* index_array;
  DataArray* data_arrays;
  unsigned int size;
} Map;

void append(Map* m, const char* label, Element data);

DataArray* get_map_index(Map* m, const char* label);

void print_data_array(const DataArray* da);
void print_map(const Map* m);

#if __cplusplus
}
#endif

#endif
