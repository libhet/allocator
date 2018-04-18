#include <vector>
#include <memory>
//#include "newdelete.h"
#include <list>
namespace my{

    /**
     *
     * @tparam T
     * @tparam Capacity
     */
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

//            std::cout << __PRETTY_FUNCTION__ << std::endl;

            bool    need_blocks = (size%Capacity == 0);
            T*      p = nullptr;
            if(need_blocks) {
                    block.emplace_back(std::unique_ptr<T>(new T[Capacity]));
                    p = block[size/Capacity].get() + (size%Capacity);
                    ++size;
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

