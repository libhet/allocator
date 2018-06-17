
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