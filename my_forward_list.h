#ifndef ALLOCATOR_MY_FORWARD_LIST_H
#define ALLOCATOR_MY_FORWARD_LIST_H
#include <iterator>
#include <memory>
namespace my {
    template <typename T, typename Allocator = std::allocator<T>>
    class forward_list{
    private:
        struct Node;

    protected:
        using allocator_type = typename Allocator::template rebind<Node>::other;

    private:
        struct Node {

            struct NodeDeleter {
                void operator() (void *p) {
                    static_cast<T*>(p)->~T();
//                    p->allocator->deallocate(p, 1);
                }
            };

            using Ptr = std::unique_ptr<Node, NodeDeleter>;

            Node(): m_next(nullptr) {}
            explicit Node(const T& value) : m_value(value),m_next(nullptr) {}
            ~Node() = default;

//            allocator_type* allocator;
            T       m_value;
            Ptr     m_next;
        };

    public:
        forward_list()  = default;
        ~forward_list() = default;

        class iterator
                : std::iterator<std::forward_iterator_tag, T>
        {
        private:
            Node *m_node = nullptr;
        public:
            iterator(Node* node): m_node(node) {}
            void operator++() {
                if(m_node) {
                    m_node = m_node->m_next.get();
                }
            }
            T & operator*() {
                if(m_node) {
                    return m_node->m_value;
                }
            }
            const T & operator*() const {
                if(m_node) {
                    return m_node->m_value;
                }
            }
            T * operator->() {
                if(m_node) {
                    return &(m_node->m_value);
                }
            }
            bool operator!=(const iterator& other) const {
                return m_node != other.m_node;
            }
            bool operator+=(const iterator& other) const {
                return !operator!=(other);
            }
        };

        iterator begin() const {
            return iterator(m_head.get());
        }
        iterator end() const {
            return iterator(nullptr);
        }
        void     append(const T& value) {
            Node* node = allocator.allocate(1);
            allocator.construct(node,value);
//            node->m_next = m_head;
//            m_head = node;
            node->m_next = nullptr;

            typename Node::Ptr node_ptr(node);

            if(m_head.get() == nullptr) {
                m_head = std::move(node_ptr);
            }
            else {
                Node* current_node = m_head.get();
                while(current_node->m_next.get() != nullptr) {
                    current_node = current_node->m_next.get();
                }
                current_node->m_next = std::move(node_ptr);
            }
        }

    private:
        typename Node::Ptr m_head = nullptr;
        allocator_type allocator;
    };
}
#endif //ALLOCATOR_MY_FORWARD_LIST_H
