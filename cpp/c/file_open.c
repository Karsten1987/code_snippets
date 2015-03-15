#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{

  FILE *fh;
  char buf[10];
  char string_ptr[10];

  fh = fopen( "foo.txt", "r" );
  if (fh == NULL)
  {
    fprintf( stderr, "error: Unable to open file");
    exit(8);
  }

  while (1)
  {
    char* c = fgets(buf, sizeof(buf), fh);
    fprintf( stderr, "read file; %i ", sizeof(c) );
    if ( c == NULL)
    {
      break;
    }
  }

  fclose(fh);

return 0;
}
