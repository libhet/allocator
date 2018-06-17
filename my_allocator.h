//#include "newdelete.h"
#include <vector>
#include <memory>
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
        std::vector<
                std::array<
                        std::array<unsigned char, sizeof(T)>,Capacity
                >
        > block;
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
        ~allocator() {  }

        template<typename U>
        allocator(allocator<U,Capacity>& other) {}

        pointer allocate(size_t n) {

            if(n != 1)
                throw std::invalid_argument( "Invalid  number of elements for allocate()" );

//            std::cout << __PRETTY_FUNCTION__ << std::endl;

            bool    need_blocks = (size%Capacity == 0);
            pointer      p = nullptr;
            if(need_blocks) {
                    block.emplace_back(std::array<std::array<unsigned char, sizeof(T)>,Capacity>());
                auto a = &block[size/Capacity];
                auto b = &(block[size/Capacity].at(size%Capacity));
                    p = reinterpret_cast<pointer>(&(block[size/Capacity].at(size%Capacity)));
                    ++size;
            }
            else {
                p = reinterpret_cast<pointer>(&(block[size/Capacity].at(size%Capacity)));
                ++size;
            }
            return p;
        }
        void deallocate(pointer p, size_t n) {
//        std::cout << __PRETTY_FUNCTION__ << std::endl;
//            for(auto& up : block) {
//                if(reinterpret_cast<pointer>(up.data()) == p) {up.reset();}
//            }
        }
        template<typename... Args>
        void construct(T* p, Args... args) {
          std::cout << __PRETTY_FUNCTION__ << std::endl;
            std::cout << p << std::endl;
            new(p) T(std::forward<Args>(args)...);
        }
        void destroy(T* p) {
            p->~T();
        }
    };

}

