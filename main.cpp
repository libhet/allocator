#include <iostream>
#include <vector>
#include "my_allocator.h"
#include <map>
#include <list>
#include "my_forward_list.h"
#include "factorial.h"

int main() {

    /**
     * Создание экземпляра std::map
     * Заполнение 10 элементами, где ключ это чисо от 0 до 9, а значение - факториал ключа.
     */
    {
        std::map<int,int> std_map;
        for(int i = 0; i < 10; ++i) {
            std_map.insert(std::make_pair(i,factorial(i)));
        }
    }

    /**
     * Создание экземпляра std::map с новым аллокатором ограниченным 10 элементами,
     * заполнение 10 элементами, где ключ это число от 0 до 9, а значение - факториал ключа.
     * Вывод на экран всех значений (ключ и значение разделены пробелом) хранящихся в контейнере.
     */
    {
        std::map<int, int, std::less<int>, my::allocator<std::pair<const int, int>,10>> std_map_with_my_allocator;
        for(int i = 0; i < 10; ++i) {
            std_map_with_my_allocator.insert(std::make_pair(i,factorial(i)));
        }
        for(auto _pair : std_map_with_my_allocator) {
            std::cout << _pair.first << " " << _pair.second << std::endl;
        }
    }

    /**
     * Создание экземпляра своего контейнера для хранения int
     * заполнение 10 элементами от 0 до 9
     */
    {
        my::forward_list<int> my_forward_list_with_std_allocator;
        for(int i = 0; i < 10; ++i) {
            my_forward_list_with_std_allocator.append(i);
        }
    }

    /**
     * Создание экземпляра своего контейнера для хранения int
     * с новым аллокатором ограниченным 10 элементами,
     * заполнение 10 элементами от 0 до 9.
     * Вывод на экран всех значений хранящихся в контейнере.
     */
    {
        my::forward_list<int, my::allocator<int,10>> my_fl_with_my_allocator;
        for(int i = 0; i < 10; ++i) {
            my_fl_with_my_allocator.append(i);
        }
        for(auto _int : my_fl_with_my_allocator) {
            std::cout << _int << std::endl;
        }
    }

//    /**
//     * Map Test Block
//     */
//    {
//        {
//            std::map<const int, int, std::less<int>, my::allocator<std::pair<const int, int>>> map_with_my_allocator;
//            map_with_my_allocator.insert(std::make_pair(1, 2));
//            map_with_my_allocator.insert(std::make_pair(2, 4));
//            map_with_my_allocator.insert(std::make_pair(3, 6));
//            for (auto const i : map_with_my_allocator) {
//                std::cout << i.first;
//            }
//        }
//        {
//            std::map<const int, int, std::less<int>> map_with_std_allocator;
//            map_with_std_allocator.insert(std::make_pair(1, 2));
//            map_with_std_allocator.insert(std::make_pair(2, 4));
//            map_with_std_allocator.insert(std::make_pair(3, 6));
//            for (auto const i : map_with_std_allocator) {
//                std::cout << i.first;
//            }
//        }
//    }

//    /**
//     * ltrace test
//     * Выделяется три блока, по 5 элементов в каждом.
//     * Один нод имеет размер 24 байта.
//     * Определеить будет ли очищаться память.
//     * С помощью программы ltrace.
//     * Успех!
//     */
//    {
//        std::list<int, my::allocator<int,5>> list_with_my_allocator;
//        for(int i = 0 ; i < 15; ++i) {
//            list_with_my_allocator.emplace_back(i);
//        }
//        for(auto item:list_with_my_allocator) std::cout << item << " ";
//        std::cout << std::endl;
//    }

    return 0;
}