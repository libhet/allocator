#include <vector>
#include <memory>
#include "newdelete.h"
#include <list>
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

    template<typename T, size_t Capacity = 64>
    class log_allocator_raw2 {
    private:
        struct mem_block {
        private:
            unsigned char* p;
        public:
            mem_block()
            {
//            std::cout << __PRETTY_FUNCTION__ << std::endl;
                p = reinterpret_cast<unsigned char*>(malloc(Capacity * sizeof(T)));
            }
            ~mem_block() {
                free(p);
            }
            T* operator[](size_t n){
                auto r = p + n*sizeof(T);
                return reinterpret_cast<T*>((unsigned char*)r);
            }
        };
        mem_block** block;
        size_t size = 0;

    public:

        using value_type = T;
        using pointer    = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference   = const T&;

        template<typename U>
        struct rebind {
            using other = log_allocator_raw2<U, Capacity>;
        };

        log_allocator_raw() = default;

        template<typename U>
        log_allocator_raw2(log_allocator_raw2<U,Capacity>& other) {}

        T* allocate(size_t n) {
//          std::cout << __PRETTY_FUNCTION__ << std::endl;
            size_t have_blocks = block.size();
            size_t need_blocks = ((size%Capacity)==0)?1 + (n/Capacity):0;

            T* p = nullptr;
            if(need_blocks > 0) {
                block.resize(have_blocks + need_blocks);
                ++size;
                p = block[size/Capacity][size%Capacity];
            }
            else {
                if(have_blocks) {
                    p = block[size/Capacity][size%Capacity];
                    ++size;
                }
                else {
                    block.emplace_back(std::move(mem_block()));
                    p = block[size/Capacity][size%Capacity];
                    ++size;
                }
            }
            return reinterpret_cast<T*>(p);
        }
        void deallocate(T* p, size_t n) {
//        std::cout << __PRETTY_FUNCTION__ << std::endl;
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


    template<typename T, size_t Capacity = 64>
    class log_allocator_raw {
    private:
        struct mem_block {
        private:
            unsigned char* p;
        public:
            mem_block()
            {
//            std::cout << __PRETTY_FUNCTION__ << std::endl;
                p = reinterpret_cast<unsigned char*>(malloc(Capacity * sizeof(T)));
            }
            ~mem_block() {
                free(p);
            }
            T* operator[](size_t n){
                auto r = p + n*sizeof(T);
                return reinterpret_cast<T*>((unsigned char*)r);
            }
        };
        std::vector<mem_block> block;
        size_t size = 0;

    public:

        using value_type = T;
        using pointer    = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference   = const T&;

        template<typename U>
        struct rebind {
            using other = log_allocator_raw<U, Capacity>;
        };

        log_allocator_raw() = default;

        template<typename U>
        log_allocator_raw(log_allocator_raw<U,Capacity>& other) {}

        T* allocate(size_t n) {
//          std::cout << __PRETTY_FUNCTION__ << std::endl;
            size_t have_blocks = block.size();
            size_t need_blocks = ((size%Capacity)==0)?1 + (n/Capacity):0;

            T* p = nullptr;
            if(need_blocks > 0) {
                block.resize(have_blocks + need_blocks);
                ++size;
                p = block[size/Capacity][size%Capacity];
            }
            else {
                if(have_blocks) {
                    p = block[size/Capacity][size%Capacity];
                    ++size;
                }
                else {
                    block.emplace_back(std::move(mem_block()));
                    p = block[size/Capacity][size%Capacity];
                    ++size;
                }
            }
            return reinterpret_cast<T*>(p);
        }
        void deallocate(T* p, size_t n) {
//        std::cout << __PRETTY_FUNCTION__ << std::endl;
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


    template<typename T, size_t Capacity = 64>
    class log_allocator_up {
    private:
        struct mem_block {
        private:
            std::unique_ptr<unsigned char> p;
        public:
            mem_block() : p(new unsigned char[Capacity*sizeof(T)])
            {
//            std::cout << __PRETTY_FUNCTION__ << std::endl;
            }
            T* operator[](size_t n){
                unsigned char* pointer = p.get();
                pointer = pointer + n*sizeof(T);
                return reinterpret_cast<T*const>((unsigned char*)pointer);
            }
        };

        std::vector<mem_block> block;
        size_t size = 0;

    public:

        using value_type = T;
        using pointer    = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference   = const T&;

        template<typename U>
        struct rebind {
            using other = log_allocator_up<U, Capacity>;
        };

        log_allocator_up() = default;

        template<typename U>
        log_allocator_up(log_allocator_up<U,Capacity>& other) {}

        T* allocate(size_t n) {
//          std::cout << __PRETTY_FUNCTION__ << std::endl;
            size_t have_blocks = block.size();
            size_t need_blocks = ((size%Capacity)==0)?1 + (n/Capacity):0;

            T* p = nullptr;
            if(need_blocks > 0) {
                block.resize(have_blocks + need_blocks);
                ++size;
                p = block[size/Capacity][size%Capacity];
            }
            else {
                if(have_blocks) {
                    p = block[size/Capacity][size%Capacity];
                    ++size;
                }
                else {
                    block.push_back(mem_block());
                    p = block[size/Capacity][size%Capacity];
                    ++size;
                }
            }
            return reinterpret_cast<T*>(p);
        }
        void deallocate(T* p, size_t n) {
//        std::cout << __PRETTY_FUNCTION__ << std::endl;
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


    template <typename T, size_t capacity = 64>
    class allocator
    {
        static_assert(capacity != 0, "no zero capacity!");

    private:
        std::vector<std::array<T,capacity>> pool;
        std::size_t index = 0;

    public:
        using value_type = T;
        typedef T*         pointer;
        typedef const T*   const_pointer;
        typedef T&         reference;
        typedef const T&   const_reference;

        template <class U> struct rebind { using other =  allocator<U, capacity>; };


        allocator() = default;
        template< class U >
        allocator( const allocator<U, capacity>& other ){};

        T* allocate(std::size_t n)
        {
            if(n != 1)
                throw std::invalid_argument( "Invalid  number of elements for allocate()" );

            pool.resize(1 + index/capacity);
            T* p = &pool[index/capacity][index%capacity];
            index += n;
            return p;
        }

        void deallocate(T*, std::size_t)
        {
        }

        template<typename U, typename ... Args>
        void construct( U* p, Args&&... args )
        {
            new(p) U(std::forward<Args>(args)...);
        }

        void destroy(T * p)
        {
            p->~T();
        }
    };

    template<typename T, size_t Capacity = 64>
    class log_allocator {
    private:
        struct mem_block {
        private:
            std::shared_ptr<unsigned char> p;
        public:
            mem_block() : p(new unsigned char[Capacity*sizeof(T)])
            {
//            std::cout << __PRETTY_FUNCTION__ << std::endl;
            }
            T* operator[](size_t n){
                unsigned char* pointer = p.get();
                pointer = pointer + n*sizeof(T);
                return reinterpret_cast<T*const>((unsigned char*)pointer);
            }
        };

        std::vector<mem_block> block;
        size_t size = 0;

    public:

        using value_type = T;
        using pointer    = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference   = const T&;

        template<typename U>
        struct rebind {
            using other = log_allocator<U, Capacity>;
        };

        log_allocator() = default;

        template<typename U>
        log_allocator(log_allocator<U,Capacity>& other) {}

        T* allocate(size_t n) {
//          std::cout << __PRETTY_FUNCTION__ << std::endl;
            size_t have_blocks = block.size();
            size_t need_blocks = ((size%Capacity)==0)?1 + (n/Capacity):0;

            T* p = nullptr;
            if(need_blocks > 0) {
                block.resize(have_blocks + need_blocks);
                ++size;
                p = block[size/Capacity][size%Capacity];
            }
            else {
                if(have_blocks) {
                    p = block[size/Capacity][size%Capacity];
                    ++size;
                }
                else {
                    block.push_back(mem_block());
                    p = block[size/Capacity][size%Capacity];
                    ++size;
                }
            }
            return reinterpret_cast<T*>(p);
        }
        void deallocate(T* p, size_t n) {
//        std::cout << __PRETTY_FUNCTION__ << std::endl;
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

    template<typename T, size_t Capacity = 64>
    class reserve_allocator_sp {
    private:
        struct MemoryBlock {
        private:
            std::shared_ptr<T> start;
            std::size_t available = Capacity;
        public:
            MemoryBlock():start(reinterpret_cast<T*>(std::malloc(Capacity * sizeof(T)),free)) {
//                start(reinterpret_cast<T*>(std::malloc(Capacity * sizeof(T))));
            }
            ~MemoryBlock() {
            }
            size_t get_available() {return Capacity - available;}
            T* operator[](size_t i) {if(i < (Capacity - 1)) return start.get() + i; else throw std::out_of_range("Capacity is less than " + i);}
            T* add_element() { --available; return (this->operator[](Capacity-available));};
        };
    private:
        size_t N = 0;
        std::vector<MemoryBlock> block;

    public:
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;

        template<typename U>
        struct rebind {
            using other = reserve_allocator_sp<U, Capacity>;
        };

        reserve_allocator_sp() = default;
        template <typename U>
        reserve_allocator_sp(const reserve_allocator_sp<U,Capacity>& other) {};
    public:
        T* allocate(std::size_t n) {
            std::cout << __PRETTY_FUNCTION__ << " " << std::endl;
            T* p;
            //n количество элементов. Сделай что нибудь с этим
            if(block.size() == 0 || block.back().get_available() == 0) {
                block.emplace_back(MemoryBlock());
                p = block.back()[0];
                std::cout << "Create New Memory Block n = " << n << std::endl;
                std::cout << p << std::endl;
            }
            else {
                if(block.back().get_available() > 0) {
                    p = block.back().add_element();
                    std::cout << "Add Element to Block: " << block.size() << std::endl;
                    std::cout << p << std::endl;
                }
            }
            return (p);
        }
        void deallocate(T* p, std::size_t n) {
            std::cout << __PRETTY_FUNCTION__ << std::endl;
            std::cout << p << std::endl;
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

