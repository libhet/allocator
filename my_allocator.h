#include <vector>

namespace my{
/*
template<typename T>
    class allocator {
    public:
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;

        template<typename U>
        struct rebind {
            using other = allocator<U>;
        };

    public:
        T* allocate(std::size_t n) {
            std::cout << __PRETTY_FUNCTION__ << " " << std::endl;
            auto p = std::malloc(n * sizeof(T));
            if(!p)
                throw std::bad_alloc();
            return reinterpret_cast<T*>(p);
        }
        void deallocate(T* p, std::size_t n) {
            std::cout << __PRETTY_FUNCTION__ << std::endl;
            free(p);
        }
        template<typename U, typename ...Args>
        void construct(U *p, Args&& ...args) {
            std::cout << __PRETTY_FUNCTION__ << std::endl;
            //new(p) - вызов конструктора (память не выделяется)
            //p - уже выделенная память
            new(p) U(std::forward<Args>(args)...);
        }
        void destroy(T *p) {
            std::cout << __PRETTY_FUNCTION__ << std::endl;
            p->~T();
        }
};
*/
    template<typename T, std::size_t Size>
    class reserve_allocator {
    private:
        struct MemoryBlock {
            T* start = nullptr;
            std::size_t available = Size;

            T* Start() {return start;}
            T* Current() {return start+(Size - available - 1);}
        };
    private:
        std::size_t blocks = 0;
        std::vector<MemoryBlock> block;

    public:
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;

        template<typename U>
        struct rebind {
            using other = reserve_allocator<U, Size>;
        };

    public:
        // Если Size больче чем n то выделять Size, если нет, то наоборот
        T* allocate(std::size_t n) {
            std::cout << __PRETTY_FUNCTION__ << " " << std::endl;
            T* p;
            if(blocks == 0) {
                block.emplace_back(MemoryBlock());
                block[0].start = reinterpret_cast<T*>(std::malloc(Size * sizeof(T)));
                p = block[0].start;
                blocks++;
            }
            else {
                if(block.back().available > 0) {
                    p = block.back().start + (Size - block.back().available - 1);
                    block.back().available--;
                }
                else {
                    block.emplace_back(MemoryBlock());
                    block.back().start = reinterpret_cast<T*>(std::malloc(Size * sizeof(T)));
                    p = block.back().start;
                    blocks++;
                }
            }


//            if(CurrentSize < Size-1) {
//                p = m_mem_block[blocks-1].Current; //std::malloc(Size * sizeof(T));
//                CurrentSize++;
//            }
//            else {
//                LastPointer = std::malloc(Size * sizeof(T));
//                p = LastPointer;
//                CurrentSize = 1;
//            }

            if(!p)
                throw std::bad_alloc();
            return reinterpret_cast<T*>(p);
        }
        void deallocate(T* p, std::size_t n) {
            std::cout << __PRETTY_FUNCTION__ << std::endl;
            //сравнивает p с поинтерами во всех блоках, если одинаковые - то вызывает фри
            for(auto it: block) {
                if(p == it.start) {
                    free(p);
                }
            }

        }
        template<typename U, typename ...Args>
        void construct(U *p, Args&& ...args) {
            std::cout << __PRETTY_FUNCTION__ << std::endl;
            //new(p) - вызов конструктора (память не выделяется)
            //p - уже выделенная память
            new(p) U(std::forward<Args>(args)...);
        }
        void destroy(T *p) {
            std::cout << __PRETTY_FUNCTION__ << std::endl;
            p->~T();
        }
    };
}

