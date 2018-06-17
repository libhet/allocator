#ifndef ALLOCATOR_MY_DEBUGER_H
#define ALLOCATOR_MY_DEBUGER_H

#include <iostream>

// Создавать сингл тон my::debuger если аргумент --debug задан.
//
namespace my {

    class debuger {
    private:
//        std::ostream m_ostream;
        bool m_debug = false;
        debuger() {};
        debuger(const debuger&) = delete;
        debuger& operator=( debuger& ) = delete;
    public:

//        template <typename T>
//        friend std::ostream& operator <<(std::ostream& os, T str) {
//            if(debuger::getInstance().get()) {
//                os << str ;
//                return os;
//            }
//        }
//        template <typename T>
//        std::ostream& operator << (T str) {
//            if(m_debug) {
//                return std::cout << str ;
//            }
//            else {
//                return std::cout;
//            }
//        }

        template <typename T>
        debuger& operator << (T s) {
//            if(m_debug) {
//                m_ostream << s ;
                return *this;
//            }
        }

        inline void set(bool force) {
            m_debug = force;
        }

        inline bool get() {
            return m_debug;
        }

        static debuger& getInstance() {
            static debuger instance;
            return instance;
        }
    };
}

#endif //ALLOCATOR_MY_DEBUGER_H
