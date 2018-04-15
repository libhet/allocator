#include <vector>
#include <memory>
#include "newdelete.h"
#include <list>
namespace my{
//    template <typename T, size_t capacity = 64>
//    class allocator
//    {
//        static_assert(capacity != 0, "no zero capacity!");
//
//    private:
//        std::vector<std::vector<std::array<unsigned char,sizeof(T)>>> pool;
//        std::size_t index = 0;
//
//    public:
//        using value_type = T;
//        typedef T*         pointer;
//        typedef const T*   const_pointer;
//        typedef T&         reference;
//        typedef const T&   const_reference;
//
//        template <class U> struct rebind { using other =  allocator<U, capacity>; };
//
//
//        allocator() = default;
//        template< class U >
//        allocator( const allocator<U, capacity>& other ){};
//
//        T* allocate(std::size_t n)
//        {
//            if(n != 1)
//                throw std::invalid_argument( "Invalid  number of elements for allocate()" );
//
//            pool.resize(1 + index/capacity);
//            pool[index/capacity].resize(capacity);
//            T* p = reinterpret_cast<T*>(&pool[index/capacity][index%capacity]);
//            index += n;
//            return p;
//        }
//
//        void deallocate(T*, std::size_t)
//        {
//        }
//
//        template<typename U, typename ... Args>
//        void construct( U* p, Args&&... args )
//        {
//            new(p) U(std::forward<Args>(args)...);
//        }
//
//        void destroy(T * p)
//        {
//            p->~T();
//        }
//    };

//
//    template <typename T>
//    class my_up :
//            public std::unique_ptr<T>
//    {
//        my_up(T* p) : std::unique_ptr<T>(p)
//            {}
//        ~my_up() {
//            std::cout << "UP destructor" << std::endl;
//        }
//
//        using std::unique_ptr<T> get;
//    };

    template<typename T, size_t Capacity = 64>
    class allocator {
    private:
        std::vector<std::unique_ptr<T>> block;
        size_t size = 0;

    public:
        using value_type = T;
        using pointer    = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference   = const T&;

        template<typename U>
        struct rebind {
            using other = allocator<U, Capacity>;
        };

        allocator() = default;

        template<typename U>
        allocator(allocator<U,Capacity>& other) {}

        T* allocate(size_t n) {

            if(n != 1)
                throw std::invalid_argument( "Invalid  number of elements for allocate()" );

            std::cout << __PRETTY_FUNCTION__ << std::endl;

            bool    need_blocks = (size%Capacity == 0);
            T*      p = nullptr;
            if(need_blocks) {
//                if(size == 0) {
                    block.emplace_back(std::unique_ptr<T>(new T[Capacity]));
                    p = block[size/Capacity].get() + (size%Capacity);
                    ++size;
//                }
//                else {
//
////                    throw std::invalid_argument( "You can't explode this allocated memory, cause you set max size is " + Capacity);
//                }
            }
            else {
                p = block[size/Capacity].get() + (size%Capacity);
                ++size;
            }
            return p;
        }
        void deallocate(T* p, size_t n) {
//        std::cout << __PRETTY_FUNCTION__ << std::endl;
            for(auto& up : block) {
                if(up.get() == p) {up.reset();}
            }
        }
        template<typename... Args>
        void construct(T* p, Args... args) {
//          std::cout << __PRETTY_FUNCTION__ << std::endl;
            new(p) T(std::forward<Args>(args)...);
        }
        void destroy(T* p) {
            p->~T();
        }
    };


}

