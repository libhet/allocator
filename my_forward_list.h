#ifndef ALLOCATOR_MY_FORWARD_LIST_H
#define ALLOCATOR_MY_FORWARD_LIST_H
#include <iterator>

namespace my {
    template <typename T, typename allocator_type>
    class forward_list{
    public:
        forward_list() = default;
        ~forward_list() = default;

        /** reserve
         * вызывает аллокатор с нужным капасити
         * или аллокэйт
         */
        class iterator
                : std::iterator<std::forward_iterator_tag, T>
        {
        private:
            std::vector<T>::iterator it;
        public:
            iterator(const std::vector<T>::iterator vit)
                    : it(vit) {}
            iterator & operator++() {
                ++it;
                return *this;
            }
            Image & operator*() {
                return *it;
            }
            const Image & operator*() const {
                return *it;
            }
            Image * operator->() {
                return &*(it);
            }
            bool operator!=(iterator _it) {
                return _it.it != it;
            }
        };
        iterator begin(){
            return iterator(mImages.begin());
        }
        iterator end() {
            return iterator(mImages.end());
        }

    private:

    };
}
#endif //ALLOCATOR_MY_FORWARD_LIST_H
