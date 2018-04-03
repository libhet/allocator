#include <iostream>
#include <vector>
#include "my_allocator.h"
#include <map>

int main() {
//    auto v = std::vector<int, std::allocator<int>>{};
//    v.reserve(5);
//    v.emplace_back(2);
//    v.emplace_back(3);
//    v.emplace_back(4);
    auto m = std::map<int, int,std::less<int>, my::reserve_allocator<std::pair<const int,int>,3>>{};
   // auto m1 = std::map<int, int,std::less<int>, my::allocator<std::pair<const int,int>>>{};
    m[0] = 0;
    //m1[0] = 0;
    m[1] = 0;
    //m1[1] = 0;
    m[2] = 0;
    //m1[2] = 0;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}