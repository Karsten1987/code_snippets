#include <new>
#include <limits>
#include <iostream>
#include <vector>
#include <memory>

typedef struct rcutils_allocator_t
{
  /// Allocate memory, given a size and the `state` pointer.
  /** An error should be indicated by returning `NULL`. */
  void * (*allocate)(size_t size, void * state);
  /// Deallocate previously allocated memory, mimicking std::free().
  /** Also takes the `state` pointer. */
  void (* deallocate)(void * pointer, void * state);
  /// Reallocate if possible, otherwise it deallocates and allocates.
  /**
   * Also takes the `state` pointer.
   *
   * If unsupported then do deallocate and then allocate.
   * This should behave as std::realloc() does, as opposed to posix's
   * [reallocf](https://linux.die.net/man/3/reallocf), i.e. the memory given
   * by pointer will not be free'd automatically if std::realloc() fails.
   * For reallocf-like behavior use rcutils_reallocf().
   * This function must be able to take an input pointer of `NULL` and succeed.
   */
  void * (*reallocate)(void * pointer, size_t size, void * state);
  /// Allocate memory with all elements set to zero, given a number of elemets and their size.
  /** An error should be indicated by returning `NULL`. */
  void * (*zero_allocate)(size_t number_of_elements, size_t size_of_element, void * state);
  /// Implementation defined state storage.
  /**
   * This is passed as the final parameter to other allocator functions.
   * Note that the contents of the state can be modified even in const-qualified
   * allocator objects.
   */
  void * state;
} rcutils_allocator_t;

static void *
__default_allocate(size_t size, void * state)
{
  (void)state;  // unused
  return malloc(size);
}

static void
__default_deallocate(void * pointer, void * state)
{
  (void)state;  // unused
  free(pointer);
}

static void *
__default_reallocate(void * pointer, size_t size, void * state)
{
  (void)state;  // unused
  return realloc(pointer, size);
}

static void *
__default_zero_allocate(size_t number_of_elements, size_t size_of_element, void * state)
{
  (void)state;  // unused
  return calloc(number_of_elements, size_of_element);
}

rcutils_allocator_t
rcutils_get_zero_initialized_allocator(void)
{
  static rcutils_allocator_t zero_allocator = {
    .allocate = NULL,
    .deallocate = NULL,
    .reallocate = NULL,
    .zero_allocate = NULL,
    .state = NULL,
  };
  return zero_allocator;
}

rcutils_allocator_t
rcutils_get_default_allocator()
{
  static rcutils_allocator_t default_allocator = {
    .allocate = __default_allocate,
    .deallocate = __default_deallocate,
    .reallocate = __default_reallocate,
    .zero_allocate = __default_zero_allocate,
    .state = NULL,
  };
  return default_allocator;
}

namespace MyLib {
   template <class T>
   class MyAlloc {
     public:
       // type definitions
       typedef T        value_type;
       typedef T*       pointer;
       typedef const T* const_pointer;
       typedef T&       reference;
       typedef const T& const_reference;
       typedef std::size_t    size_type;
       typedef std::ptrdiff_t difference_type;

       // rebind allocator to type U
       template <class U>
       struct rebind {
           typedef MyAlloc<U> other;
       };

       // return address of values
       pointer address (reference value) const {
           return &value;
       }
       const_pointer address (const_reference value) const {
           return &value;
       }

       /* constructors and destructor
        * - nothing to do because the allocator has no state
        */
       MyAlloc() throw() {
       }
       MyAlloc(const MyAlloc&) throw() {
       }
       template <class U>
         MyAlloc (const MyAlloc<U>&) throw() {
       }
       ~MyAlloc() throw() {
       }

       // return maximum number of elements that can be allocated
       size_type max_size () const throw() {
           return std::numeric_limits<std::size_t>::max() / sizeof(T);
       }

       // allocate but don't initialize num elements of type T
       pointer allocate (size_type num, const void* = 0) {
           // print message and allocate memory with global new
           std::cerr << "allocate " << num << " element(s)"
                     << " of size " << sizeof(T) << std::endl;
           pointer ret = (pointer)(::operator new(num*sizeof(T)));
           std::cerr << " allocated at: " << (void*)ret << std::endl;
           return ret;
       }

//       // initialize elements of allocated storage p with value value
//       void construct (pointer p, const T& value) {
//           // initialize memory with placement new
//         std::cerr << "new is called" << std::endl;
//           new((void*)p)T(value);
//       }
//
//       // destroy elements of initialized storage p
//       void destroy (pointer p) {
//           // destroy objects by calling their destructor
//           p->~T();
//       }

       // deallocate storage p of deleted elements
       void deallocate (pointer p, size_type num) {
           // print message and deallocate memory with global delete
           std::cerr << "deallocate " << num << " element(s)"
                     << " of size " << sizeof(T)
                     << " at: " << (void*)p << std::endl;
           ::operator delete((void*)p);
       }
   };

   // return that all specializations of this allocator are interchangeable
   template <class T1, class T2>
   bool operator== (const MyAlloc<T1>&,
                    const MyAlloc<T2>&) throw() {
       return true;
   }
   template <class T1, class T2>
   bool operator!= (const MyAlloc<T1>&,
                    const MyAlloc<T2>&) throw() {
       return false;
   }
}

namespace rcutils {
   template <class T>
   class DefaultAllocator {
     public:
       // type definitions
       typedef T        value_type;
       typedef T*       pointer;
       typedef const T* const_pointer;
       typedef T&       reference;
       typedef const T& const_reference;
       typedef std::size_t    size_type;
       typedef std::ptrdiff_t difference_type;

       // rebind allocator to type U
       template <class U>
       struct rebind {
           typedef DefaultAllocator<U> other;
       };

       // return address of values
       pointer address (reference value) const {
           return &value;
       }
       const_pointer address (const_reference value) const {
           return &value;
       }

       /* constructors and destructor
        * - nothing to do because the default allocator has no state
        */
       DefaultAllocator() throw()
       : default_allocator_(rcutils_get_default_allocator())
       {
       }
       DefaultAllocator(const DefaultAllocator&) throw() {
       }
       template <class U>
       DefaultAllocator(const DefaultAllocator<U>&) throw() {
       }

       ~DefaultAllocator() throw() {
       }

       // return maximum number of elements that can be allocated
       size_type max_size () const throw() {
           return std::numeric_limits<std::size_t>::max() / sizeof(T);
       }

       // allocate but don't initialize num elements of type T
       pointer allocate (size_type num, const void* = 0) {
           // print message and allocate memory with global new
           std::cerr << "allocate " << num << " element(s)"
                     << " of size " << sizeof(T) << std::endl;
           pointer ret = (pointer)default_allocator_.allocate(num * sizeof(T), default_allocator_.state);
           std::cerr << " allocated at: " << (void*)ret << std::endl;
           return ret;
       }

       // deallocate storage p of deleted elements
       void deallocate (pointer p, size_type num) {
           // print message and deallocate memory with global delete
           std::cerr << "deallocate " << num << " element(s)"
                     << " of size " << sizeof(T)
                     << " at: " << (void*)p << std::endl;
           default_allocator_.deallocate(p, default_allocator_.state);

       }

private:
       rcutils_allocator_t default_allocator_;
   };

   // return that all specializations of this allocator are interchangeable
   template <class T1, class T2>
   bool operator== (const DefaultAllocator<T1>&,
                    const DefaultAllocator<T2>&) throw() {
       return true;
   }
   template <class T1, class T2>
   bool operator!= (const DefaultAllocator<T1>&,
                    const DefaultAllocator<T2>&) throw() {
       return false;
   }
}

class FunnyStuff
{
public:
  FunnyStuff() = default;

  void print_i(size_t i) { std::cerr << "FunnyStuff class got " << i << std::endl; }
};

template<class T>
void * do_funny_template_stuff(size_t i, void * alloc) {
  T * funny_stuff = static_cast<T *>(alloc);
  funny_stuff->print_i(i);

  return nullptr;
}

int main(int argc, char ** argv) {
  // auto vecMyAlloc = std::vector<int, MyLib::MyAlloc<int>>(10);
  auto vecRcutils = std::vector<int, rcutils::DefaultAllocator<int>>(10);

  auto rcutils_alloc = rcutils_get_zero_initialized_allocator();
  //rcutils_alloc.allocate = static_cast<decltype(rcutils_alloc.allocate)>(std::allocator_traits<std::allocator<void>>::allocate);

  FunnyStuff fs;
  rcutils_alloc.allocate = &do_funny_template_stuff<FunnyStuff>;
  rcutils_alloc.state = &fs;

  rcutils_alloc.allocate(3, rcutils_alloc.state);
}
