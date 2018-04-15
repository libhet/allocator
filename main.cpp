#include <iostream>
#include <vector>
#include "my_allocator.h"
#include <map>
#include <list>

template<typename T>
struct Deleter {
    void operator() (T* p) {delete[] p;std::cout<< "deleter call" <<std::endl;}
};
int main() {
    {
//        auto v = std::list<int, my::allocator<int,500>>{};
////    v.reserve(64);
//    for(int i = 0; i < 100; ++i) {
//        v.emplace_back(2);
//        v.emplace_back(3);
//        v.emplace_back(4);
//    }

        std::unique_ptr<int> up(new int[10],Deleter<int>);
        up.release();
    }
//std::cout << "v2" << std::endl;
//    auto v2 = std::list<int, my::allocator<int>>{};
////    v.reserve(64);
//    for(int i = 0; i < 100; ++i) {
//        v2.emplace_back(2);
//        v2.emplace_back(3);
//        v2.emplace_back(4);
//    }

//    auto m = std::map<int, int,std::less<int>, my::reserve_allocator_sp<std::pair<const int,int>,64>>{};
   // auto m1 = std::map<int, int,std::less<int>, my::allocator<std::pair<const int,int>>>{};
//    m[0] = 0;
//    //m1[0] = 0;
//    m[1] = 0;
//    //m1[1] = 0;
//    m[2] = 0;
//    //m1[2] = 0;
//    for(auto item : v)  {
//        std::cout << item;
//    }
    std::cout << "Hello, World!" << std::endl;
    return 0;
}