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
                void operator() (Node *p) {
//                    std::cout << __PRETTY_FUNCTION__ << std::endl;
//                    std::cout << p << std::endl;
//                    std::cout << p->m_value << std::endl;
//                    std::cout << p->m_next.get() << std::endl;
//                    std::cout << "/////////////////////////////" << std::endl;
//                    p->~Node();
//                    p->node_allocator->deallocate(p, 1);
                }
            };

            using Ptr = std::unique_ptr<Node, NodeDeleter>;

            Node(): m_next(nullptr) {}
            explicit Node(const T& value, allocator_type* node_allocator)
                    : m_value(value),
                      m_next(nullptr),
                      node_allocator(node_allocator) {}
            ~Node() = default;

            allocator_type* node_allocator;
            T       m_value;
            Ptr     m_next;
        };

    public:
        forward_list()  = default;
        ~forward_list() {
            Node* current_node = m_head.get();
            do {
                Node* last_node = current_node;
                current_node = current_node->m_next.get();
                std::cout << "Destroy Node: " << last_node->m_value << std::endl;
                allocator.destroy(last_node);
//                allocator.deallocate(last_node);
            }
            while(current_node->m_next.get() != nullptr);
            std::cout << "Destroy Node: " << current_node->m_value << std::endl;
            allocator.destroy(current_node);
//            allocator.deallocate(current_node, 1);
        }

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
            allocator.construct(node,value, &allocator);
//            node->m_next = m_head;
//            m_head = node;
            node->m_next = nullptr;

            typename Node::Ptr node_ptr(std::move(node));

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
