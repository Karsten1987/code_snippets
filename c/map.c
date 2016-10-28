#include <stdio.h>
#include <stdlib.h>

typedef struct _element
{
  const char* label;
} Element;

typedef struct _element_array
{
  Element* elements;
  unsigned int size;
} ElementArray;

typedef struct _map
{
  ElementArray* idx_to_elements;
  unsigned int size;
} Map;

Map initialize()
{
  Element e1_1 = {.label = "1_1"};
  Element e1_2 = {.label = "1_2"};
  Element e2_1 = {.label = "2_1"};
  Element e3_1 = {.label = "3_1"};
  Element e3_2 = {.label = "3_2"};
  Element e3_3 = {.label = "3_3"};

  ElementArray e1;
  e1.elements = malloc(2*sizeof(Element));
  e1.elements[0] = e1_1;
  e1.elements[1] = e1_2;
  e1.size = 2;

  ElementArray e2;
  e2.elements = malloc(1*sizeof(Element));
  e2.elements[0] = e2_1;
  e2.size = 1;

  ElementArray e3;
  e3.elements = malloc(3*sizeof(Element));
  e3.elements[0] = e3_1;
  e3.elements[1] = e3_2;
  e3.elements[2] = e3_3;
  e3.size = 3;

  Map m;
  m.idx_to_elements = malloc(3*sizeof(ElementArray));
  m.idx_to_elements[0] = e1;
  m.idx_to_elements[1] = e2;
  m.idx_to_elements[2] = e3;
  m.size = 3;
  return m;
}

int main()
{
  Map m = initialize();

  for (unsigned int i=0; i<m.size; ++i)
  {
    for (unsigned int j=0; j<m.idx_to_elements[i].size; ++j)
    {
      printf("%s\t", m.idx_to_elements[i].elements[j].label);
    }
    printf("\n");
  }
  return 0;
}
