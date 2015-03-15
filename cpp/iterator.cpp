#include <stdio.h>
#include <vector>
#include <iostream>

typedef std::vector<std::vector<int> >  		OuterVector_T;
typedef std::vector<int>  				InnerVector_T;

void fillVector(OuterVector_T& vec, 
                 const size_t outer_size,
                 const size_t inner_size)
{
   for (size_t i=0; i<outer_size; ++i)
   {
       // CHECK FOR COPY CONSTRUCTOR HERE
       InnerVector_T inner_vector(inner_size);
       for(size_t j=0; j<inner_size; ++j)
       {
          int index = i*inner_size + j;
	  inner_vector[j] = index;
       }
       vec[i] = inner_vector;
   }
}

void indexVector(const OuterVector_T& vec,
                 const size_t outer_size,
                 const size_t inner_size)
{
   for (size_t i=0; i<outer_size; ++i)
   {
       for (size_t j=0; j<inner_size; ++j)
       {
           std::cerr << "index value at: " << i << " " << j  << " " << vec[i][j] << std::endl;
       }
   }
}

void iterateVector(const OuterVector_T& vec,
                   const size_t outer_size,
                   const size_t inner_size)
{
	OuterVector_T::const_iterator outer_iter;
        for (outer_iter=vec.begin(); outer_iter!=vec.end(); ++outer_iter)
        {
            const size_t i = outer_iter - vec.begin();
            const InnerVector_T& inner_vector = *outer_iter;
            InnerVector_T::const_iterator inner_iter;
            for (inner_iter=inner_vector.begin(); inner_iter!=inner_vector.end(); ++inner_iter)
            {
	       const size_t j = inner_iter - inner_vector.begin();
               std::cerr<< "iterator value at " <<i << " " << j << " "<< *inner_iter << std::endl;
            }
        }
           
}


int main()
{
   const size_t OUTER_SIZE = 3;
   const size_t INNER_SIZE = 5;

   OuterVector_T outer_vector(OUTER_SIZE);
   fillVector(outer_vector, OUTER_SIZE, INNER_SIZE);
   iterateVector(outer_vector, OUTER_SIZE, INNER_SIZE);

   return 0;

}
