#include <iostream>
#include <memory>

struct MyStruct
{
  char * data;
};

void delete_my_struct(MyStruct * ms) {
  delete ms->data;
  delete ms;
}

int main(int argc, char ** argv)
{
  auto my_struct = std::shared_ptr<MyStruct>(new MyStruct, delete_my_struct);
  my_struct->data = new char[1000];


  return 0;
}
