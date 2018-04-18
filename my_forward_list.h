#ifndef ALLOCATOR_MY_FORWARD_LIST_H
#define ALLOCATOR_MY_FORWARD_LIST_H
#include <iterator>
#include <memory>
namespace my {
    template <typename T, typename Allocator = std::allocator<T>>
    class forward_list{
    private:
        struct Node {
            Node(): m_next(nullptr) {}
            explicit Node(const T& t) : m_t(t),m_next(nullptr) {}

            T       m_t;
            Node*   m_next = nullptr;
        };
    protected:
        using allocator_type = typename Allocator::template rebind<Node>::other;
    public:
        forward_list()  = default;
        ~forward_list() = default;

        class iterator
                : std::iterator<std::forward_iterator_tag, T>
        {
        private:
            Node* m_node = nullptr;
        public:
            iterator(Node* node): m_node(node) {}
            void operator++() {
                if(m_node) {
                    m_node = m_node->m_next;
                }
            }
            T & operator*() {
                if(m_node) {
                    return m_node->m_t;
                }
            }
            const T & operator*() const {
                if(m_node) {
                    return m_node->m_t;
                }
            }
            T * operator->() {
                if(m_node) {
                    return &(m_node->m_t);
                }
            }
            bool operator!=(const iterator& other) {
                return m_node != other.m_node;
            }
            bool operator+=(const iterator& other) {
                return !operator!=(other);
            }
        };

        iterator begin(){
            return iterator(m_head);
        }
        iterator end() {
            return iterator(nullptr);
        }
        void     append(const T& t) {
            Node* node = allocator.allocate(1);
            allocator.construct(node,t);
//            node->m_next = m_head;
//            m_head = node;
            node->m_next = nullptr;
            if(m_head == nullptr) {
                m_head = node;
            }
            else {
                Node* current_node = m_head;
                while(current_node->m_next != nullptr) {
                    current_node = current_node->m_next;
                }
                current_node->m_next = node;
            }
        }

    private:
        Node* m_head = nullptr;
        allocator_type allocator;
    };
}
#endif //ALLOCATOR_MY_FORWARD_LIST_H
