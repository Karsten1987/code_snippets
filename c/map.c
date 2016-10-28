#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void append_to_data_array(DataArray* data_array, Element data)
{
  ++data_array->size;
  data_array->data = realloc(data_array->data, data_array->size*sizeof(Element));
  data_array->data[data_array->size-1] = data;
}

void append_to_map(Map* m, const char* label, Element data)
{
  // check wether the label exits already
  for (unsigned int i=0; i<m->size; ++i)
  {
    if (strcmp(m->index_array[i].label, label) == 0)
    {
      // label exists already
      //printf("Found existing label %s. Will append new data\n", m->index_array[i].label);
      // we will append data into DataArray
      append_to_data_array(&(m->data_arrays[i]), data);
      return;
    }
  }

  //printf("Label %s does not exist yet. Will add a new one\n", label);
  // when we reach this point, the label does not exist yet
  // reallocate the index array
  Index idx = {.index = m->size, .label = label};
  ++m->size;
  m->index_array = realloc(m->index_array, m->size*sizeof(Index));
  m->index_array[idx.index] = idx;

  // reallocate the actual data array
  m->data_arrays = realloc(m->data_arrays, m->size*sizeof(DataArray));
  append_to_data_array(&m->data_arrays[idx.index], data);
}

Map initialize_map()
{
  Element d1_1 = {.element_data = "1_1"};
  Element d1_2 = {.element_data = "1_2"};
  Element d2_1 = {.element_data = "2_1"};
  Element d3_1 = {.element_data = "3_1"};
  Element d3_2 = {.element_data = "3_2"};
  Element d3_3 = {.element_data = "3_3"};

  DataArray d1;
  d1.data = malloc(2*sizeof(Element));
  d1.data[0] = d1_1;
  d1.data[1] = d1_2;
  d1.size = 2;

  DataArray d2;
  d2.data = malloc(1*sizeof(Element));
  d2.data[0] = d2_1;
  d2.size = 1;

  DataArray d3;
  d3.data = malloc(3*sizeof(Element));
  d3.data[0] = d3_1;
  d3.data[1] = d3_2;
  d3.data[2] = d3_3;
  d3.size = 3;

  Index idx1 = {.index = 0, .label = "Index 1"};
  Index idx2 = {.index = 1, .label = "Index 2"};
  Index idx3 = {.index = 2, .label = "Index 3"};

  Map m;
  m.index_array = malloc(3*sizeof(Index));
  m.index_array[idx1.index] = idx1;
  m.index_array[idx2.index] = idx2;
  m.index_array[idx3.index] = idx3;

  m.data_arrays = malloc(3*sizeof(DataArray));
  m.data_arrays[0] = d1;
  m.data_arrays[1] = d2;
  m.data_arrays[2] = d3;
  m.size = 3;

  return m;
}

DataArray* get_map_index(Map* m, const char* label)
{
  for (unsigned int i=0; i<m->size; ++i)
  {
    if (strcmp(m->index_array[i].label, label) == 0)
    {
      return &m->data_arrays[i];
    }
  }
  return NULL;
}

void print_data_array(const DataArray* da)
{
    for (unsigned int i=0; i<da->size; ++i)
    {
      printf("%s\t", da->data[i].element_data);
    }
    printf("\n");
}

void print_map(const Map* m)
{
  printf("Map size %u\n", m->size);
  for (unsigned int i=0; i<m->size; ++i)
  {
    printf("label %s ::: ", m->index_array[i].label);
    print_data_array(&(m->data_arrays[i]));
  }
}

int main()
{
  Map m = initialize_map();
  print_map(&m);

  Element d_new = {.element_data = "1_3"};
  append_to_map(&m, "Index 1", d_new);
  print_map(&m);

  Element d_new_new = {.element_data = "4_1"};
  append_to_map(&m, "Index 4", d_new_new);
  print_map(&m);

  DataArray* index_1 = get_map_index(&m, "Index 1");
  print_data_array(index_1);
  return 0;
}
