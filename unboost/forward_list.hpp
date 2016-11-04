// forward_list.hpp --- Unboost forward_list
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_FORWARD_LIST_HPP_
#define UNBOOST_FORWARD_LIST_HPP_

#include "unboost.hpp"
#include "rvalref.hpp"  // for r-value reference

// If not choosed, choose one
#if ((defined(UNBOOST_USE_CXX11_FORWARD_LIST) + defined(UNBOOST_USE_UNBOOST_FORWARD_LIST)) == 0)
    #ifdef UNBOOST_CXX11
        #define UNBOOST_USE_CXX11_FORWARD_LIST
    #else
        #define UNBOOST_USE_UNBOOST_FORWARD_LIST
    #endif
#endif

// Adapt choosed one
#ifdef UNBOOST_USE_CXX11_FORWARD_LIST
    #include <forward_list>
    namespace unboost {
        using std::forward_list;
    }
#elif defined(UNBOOST_USE_UNBOOST_FORWARD_LIST)
    #include <iterator>     // for std::forward_iterator_tag
    #include <functional>   // for std::less
    namespace unboost {
        template <typename T>
        struct _ctor_helper {
            T   m_obj;

            _ctor_helper() : m_obj() { }

            template <typename ARG1>
            _ctor_helper(const ARG1& arg1) : m_obj(arg1) { }
            template <typename ARG1, typename ARG2>
            _ctor_helper(const ARG1& arg1, const ARG2& arg2) : m_obj(arg1, arg2) { }
            template <typename ARG1, typename ARG2, typename ARG3>
            _ctor_helper(const ARG1& arg1, const ARG2& arg2, ARG2 arg3) : m_obj(arg1, arg2, arg3) { }
            template <typename ARG1, typename ARG2, typename ARG3, typename ARG4>
            _ctor_helper(const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4) : m_obj(arg1, arg2, arg3, arg4) { }
            template <typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
            _ctor_helper(const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4, const ARG5& arg5) : m_obj(arg1, arg2, arg3, arg4, arg5) { }

            static void *operator new(size_t, void *ptr) {
                return ptr;
            }

            static void operator delete(void *) { }
        }; // _ctor_helper<T>

        template <typename T>
        struct _forward_list_node {
            typedef _forward_list_node<T>    self_type;

            self_type*      m_next;
            char            m_data[sizeof(T)];

            _forward_list_node() : m_next(NULL) { }

                  T *get()       { return reinterpret_cast<T *>(m_data); }
            const T *get() const { return reinterpret_cast<const T *>(m_data); }

            self_type *_transfer_after(self_type *_begin, self_type *_end) {
                self_type *save = _begin->m_next;
                if (_end) {
                    _begin->m_next = _end->m_next;
                    _end->m_next = m_next;
                } else {
                    _begin->m_next = NULL;
                }
                m_next = save;
                return _end;
            }

            void reverse_after() {
                self_type *tail = m_next;
                if (tail == NULL) {
                    return;
                }
                self_type *temp;
                while (temp = tail->m_next) {
                    self_type *save = m_next;
                    m_next = temp;
                    tail->m_next = temp->m_next;
                    m_next->m_next = save;
                }
            }
        }; // _forward_list_node<T>

        template <typename T>
        struct _forward_list_iterator {
            typedef _forward_list_iterator<T>       self_type;
            typedef _forward_list_node<T>           node_type;
            typedef T                               value_type;
            typedef T&                              reference;
            typedef T *                             pointer;
            typedef const T *                       const_pointer;
            typedef ptrdiff_t                       difference_type;
            typedef std::forward_iterator_tag       iterator_category;

            node_type *m_node;

            _forward_list_iterator() : m_node(NULL) { }
            explicit _forward_list_iterator(node_type *n) : m_node(n) { }

            reference operator*() const { return *m_node->get(); }
            pointer operator->() const { return m_node->get(); }

            self_type& operator++() {
                m_node = m_node->m_next;
                return *this;
            }
            self_type operator++(int) {
                self_type temp(*this);
                m_node = m_node->m_next;
                return temp;
            }

            bool operator==(const self_type& other) const {
                return m_node == other.m_node;
            }
            bool operator!=(const self_type& other) const {
                return m_node != other.m_node;
            }

            self_type _next() const {
                if (m_node)
                    return self_type(m_node->m_next);
                else
                    return self_type();
            }
        }; // _forward_list_iterator<T>

        template <typename T>
        struct _forward_list_const_iterator {
            typedef _forward_list_const_iterator<T> self_type;
            typedef _forward_list_node<T>           node_type;
            typedef _forward_list_iterator<T>       iterator;
            typedef T                               value_type;
            typedef const T&                        reference;
            typedef const T *                       pointer;
            typedef ptrdiff_t                       difference_type;
            typedef std::forward_iterator_tag       iterator_category;

            const _forward_list_node<T>* m_node;

            _forward_list_const_iterator() : m_node(NULL) { }
            explicit _forward_list_const_iterator(const node_type *n) : m_node(n) { }
            _forward_list_const_iterator(const iterator& it) : m_node(it.m_node) { }

            reference operator*() const { return *m_node->get(); }
            pointer operator->() const { return m_node->get(); }

            self_type& operator++() {
                m_node = m_node->m_next;
                return *this;
            }
            self_type operator++(int) {
                self_type temp(*this);
                m_node = m_node->m_next;
                return temp;
            }

            bool operator==(const self_type& other) const {
                return m_node == other.m_node;
            }
            bool operator!=(const self_type& other) const {
                return m_node != other.m_node;
            }

            self_type _next() const {
                if (m_node)
                    return self_type(m_node->m_next);
                else
                    return self_type();
            }
        }; // _forward_list_const_iterator<T>

        template <typename T>
        class forward_list {
        public:
            typedef forward_list<T>                 self_type;
            typedef T                               value_type;
            typedef T&                              reference;
            typedef const T&                        const_reference;
            typedef T *                             pointer;
            typedef const T *                       const_pointer;
            typedef size_t                          size_type;
            typedef ptrdiff_t                       difference_type;
            typedef _forward_list_iterator<T>       iterator;
            typedef _forward_list_const_iterator<T> const_iterator;
            typedef _forward_list_node<T>           node_type;

            forward_list() { }
            forward_list(size_type n, const T& value) {
                assign(n, value);
            }
            forward_list(size_type n) {
                assign(n, T());
            }
            template <class InputIterator>
            forward_list(InputIterator first, InputIterator end) {
                assign(first, end);
            }
            forward_list(const self_type& other) {
                assign(other.begin(), other.end());
            }

            ~forward_list() {
                clear();
            }

            self_type& operator=(const self_type& other) {
                assign(other.begin(), other.end());
                return *this;
            }

            template <class InputIterator>
            void assign(InputIterator first, InputIterator end) {
                clear();
                insert_after(before_begin(), first, end);
            }
            void assign(size_type n, const T& t) {
                clear();
                insert_after(before_begin(), n, t);
            }

            bool empty() const {
                return m_head.m_next == NULL;
            }

            void clear() {
                node_type *next;
                node_type *node = m_head.m_next;
                while (node) {
                    next = node->m_next;
                    _destroy_node(node);
                    node = next;
                }
                m_head.m_next = NULL;
            }

            iterator before_begin() {
                iterator it(&m_head);
                return it;
            }
            const_iterator before_begin() const {
                return before_cbegin();
            }
            const_iterator before_cbegin() const {
                const_iterator it(&m_head);
                return it;
            }

            iterator begin() {
                iterator it = before_begin();
                ++it;
                return it;
            }
            const_iterator begin() const { return cbegin(); }
            const_iterator cbegin() const {
                const_iterator it = before_cbegin();
                ++it;
                return it;
            }

            iterator end() {
                iterator it(NULL);
                return it;
            }
            const_iterator end() const { return cend(); }
            const_iterator cend() const {
                const_iterator it(NULL);
                return it;
            }

            iterator emplace_after(const_iterator pos) {
                iterator it(_insert_after(pos));
                return it;
            }
            template <typename ARG1>
            iterator emplace_after(const_iterator pos, const ARG1& arg1) {
                iterator it(_insert_after(pos, arg1));
                return it;
            }
            template <typename ARG1, typename ARG2>
            iterator emplace_after(const_iterator pos, const ARG1& arg1, const ARG2& arg2) {
                iterator it(_insert_after(pos, arg1, arg2));
                return it;
            }
            template <typename ARG1, typename ARG2, typename ARG3>
            iterator emplace_after(const_iterator pos, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3) {
                iterator it(_insert_after(pos, arg1, arg2, arg3));
                return it;
            }
            template <typename ARG1, typename ARG2, typename ARG3, typename ARG4>
            iterator emplace_after(const_iterator pos, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4) {
                iterator it(_insert_after(pos, arg1, arg2, arg3, arg4));
                return it;
            }
            template <typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
            iterator emplace_after(const_iterator pos, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4, const ARG5& arg5) {
                iterator it(_insert_after(pos, arg1, arg2, arg3, arg4, arg5));
                return it;
            }
            void emplace_front() {
                _insert_after(before_cbegin());
            }
            template <typename ARG1>
            void emplace_front(const ARG1& arg1) {
                _insert_after(before_cbegin(), arg1);
            }
            template <typename ARG1, typename ARG2>
            void emplace_front(const ARG1& arg1, const ARG2& arg2) {
                _insert_after(before_cbegin(), arg1, arg2);
            }
            template <typename ARG1, typename ARG2, typename ARG3>
            void emplace_front(const ARG1& arg1, const ARG2& arg2, const ARG3& arg3) {
                _insert_after(before_cbegin(), arg1, arg2, arg3);
            }
            template <typename ARG1, typename ARG2, typename ARG3, typename ARG4>
            void emplace_front(const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4) {
                _insert_after(before_cbegin(), arg1, arg2, arg3, arg4);
            }
            template <typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
            void emplace_front(const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4, const ARG5& arg5) {
                _insert_after(before_cbegin(), arg1, arg2, arg3, arg4, arg5);
            }

            iterator erase_after(const_iterator pos) {
                node_type *node = _node_from_cit(pos);
                iterator it(_erase_after(node));
                return it;
            }
            iterator erase_after(const_iterator _before, const_iterator _end) {
                node_type *b = _node_from_cit(_before);
                node_type *e = _node_from_cit(_end);
                iterator it(_erase_after(b, e));
                return it;
            }

            reference front() {
                node_type *fr = m_head.m_next;
                assert(fr);
                return *fr->get();
            }
            const_reference front() const {
                const node_type *fr = m_head.m_next;
                assert(fr);
                return *fr->get();
            }

            void push_front(const T& value) {
                _insert_after(before_cbegin(), value);
            }
            void pop_front() {
                _destroy_node(_erase_after(&m_head));
            }

            void remove(const T& value) {
                node_type *next;
                node_type *node = &m_head;
                while (node->m_next) {
                    next = node->m_next;
                    if (*next->get() == value)
                        _erase_after(node);
                    else
                        node = next;
                }
            }
            template <class Predicate>
            void remove_if(Predicate pred) {
                node_type *next;
                node_type *node = &m_head;
                while (node->m_next) {
                    next = node->m_next;
                    if (pred(*next->get()))
                        _erase_after(node);
                    else
                        node = next;
                }
            }

            void resize(size_type siz) {
                node_type *next;
                node_type *node = m_head.m_next;
                size_type count = 0;
                while (node) {
                    next = node->m_next;
                    if (count == siz) {
                        if (next == NULL)
                            return;     // same size

                        _erase_after(node, NULL);
                        return;
                    }
                    ++count;
                    node = next;
                }

                // less than siz
                while (count < siz) {
                    _insert_after(m_head.m_next);
                    ++count;
                }
            }
            void resize(size_type siz, const T& value) {
                node_type *next;
                node_type *node = m_head.m_next;
                size_type count = 0;

                while (node) {
                    next = node->m_next;
                    if (count == siz) {
                        if (next == NULL)
                            return;     // same size

                        _erase_after(node, NULL);
                        return;
                    }
                    ++count;
                    node = next;
                }

                // less than siz
                while (count < siz) {
                    _insert_after(m_head.m_next, value);
                    ++count;
                }
            }

            void reverse() {
                node_type *list = NULL;
                node_type *next;
                node_type *node = m_head.m_next;
                while (node) {
                    next = node->m_next;
                    node->m_next = list;
                    list = node;
                    node = next;
                }
                m_head.m_next = list;
            }

            template <typename Compare>
            struct _node_compare {
                bool operator()(const node_type *n1, const node_type *n2) const {
                    Compare cmp;
                    return !cmp(*n1->get(), *n2->get());
                };
            };

            void sort() {
                std::less<T> l;
                sort(l);
            }
            template <class Compare>
            void sort(Compare comp) {
                std::vector<node_type *> v;
                node_type *node = m_head.m_next;
                while (node) {
                    v.push_back(node);
                    node = node->m_next;
                }

                _node_compare<Compare> compare;
                std::sort(v.begin(), v.end(), compare);
                m_head.m_next = NULL;

                typename std::vector<node_type *>::iterator it, end = v.end();
                for (it = v.begin(); it != end; ++it) {
                    (*it)->m_next = m_head.m_next;
                    m_head.m_next = *it;
                }
            }

            void splice_after(const_iterator pos, self_type& other) {
                node_type *node1, *node2, *next1, *next2;
                if (other.empty()) {
                    return;
                }
                other.reverse();
                node1 = _node_from_cit(pos);
                node2 = other.m_head.m_next;
                do {
                    next1 = node1->m_next;
                    next2 = node2->m_next;
                    node1->m_next = node2;
                    node2->m_next = next1;
                    node2 = next2;
                } while (node2);
                other.m_head.m_next = NULL;
            }
            void splice_after(const_iterator pos, self_type& other,
                              const_iterator it)
            {
                node_type *pos_node = pos.m_node;
                assert(pos_node);
                node_type *it_node = it.m_node;
                if (it_node == NULL)
                    return;

                // remove node from other
                node_type *node = it_node->m_next;
                it_node->m_next = node->m_next;

                // insert node after pos_node
                node_type *next = pos_node->m_next;
                node->m_next = (next ? next->m_next : NULL);
                pos_node->m_next = node;

                if (other.m_head.m_next == it_node)
                    other.m_head.m_next = NULL;
            }

            typedef forward_list<char> FL;

            void print(const FL& fl) {
                FL::const_iterator it = fl.begin();
                while (it != fl.end()) {
                    std::cout << (int)*it << " ";
                    ++it;
                }
                std::cout << std::endl;
            }

            void splice_after(const_iterator pos, self_type& other,
                              const_iterator _before, const_iterator _end)
            {
                node_type *list = NULL;
                node_type *next1;
                node_type *next2 = _node_from_cit(_before);
                node_type *b = next2->m_next;
                node_type *e = _node_from_cit(_end);
                while (b != e) {
                    next1 = b->m_next;
                    b->m_next = list;
                    list = b;
                    b = next1;
                }
                next2->m_next = e;

                node_type *node1 = _node_from_cit(pos);
                node_type *node2 = list;
                while (node2) {
                    next1 = node1->m_next;
                    next2 = node2->m_next;
                    node1->m_next = node2;
                    node2->m_next = next1;
                    node2 = next2;
                }
            }

            void swap(self_type& other) {
                swap(m_head, other.m_head);
            }

            iterator insert_after(const_iterator pos, const T& value) {
                iterator it(_insert_after(pos, value));
                return it;
            }
            iterator insert_after(const_iterator pos, size_t n, const T& value) {
                iterator it;
                while (n-- > 0) {
                    it = insert_after(pos, value);
                }
                return it;
            }
            template <class InputIterator>
            iterator insert_after(const_iterator pos,
                                  InputIterator _begin, InputIterator _end)
            {
                if (_begin == _end)
                    return iterator(NULL);

                InputIterator it = _begin;
                ++it;
                insert_after(pos, it, _end);
                return insert_after(pos, *_begin);
            }

            size_type max_size() const {
                return (size_type(-1) - sizeof(*this)) / sizeof(node_type);
            }

            void merge(self_type& other) {
                std::less<T> l;
                merge(other, l);
            }
            template <class Compare>
            void merge(self_type& other, Compare comp) {
                if (this == &other)
                    return;

                node_type *list = NULL;
                node_type *next;
                node_type *node1 = m_head.m_next;
                node_type *node2 = other.m_head.m_next;
                for (;;) {
                    if (node1 == NULL && node2 == NULL)
                        break;
                    if (node1 == NULL) {
                        while (node2) {
                            next = node2->m_next;
                            node2->m_next = list;
                            list = node2;
                            node2 = next;
                        }
                        break;
                    }
                    if (node2 == NULL) {
                        while (node1) {
                            next = node1->m_next;
                            node1->m_next = list;
                            list = node1;
                            node1 = next;
                        }
                        break;
                    }
                    if (comp(*node1->get(), *node2->get())) {
                        next = node1->m_next;
                        node1->m_next = list;
                        list = node1;
                        node1 = next;
                    } else {
                        next = node2->m_next;
                        node2->m_next = list;
                        list = node2;
                        node2 = next;
                    }
                }
                m_head.m_next = list;
                other.m_head.m_next = NULL;
                reverse();
            }

            void unique() {
                std::equal_to<T> eq;
                unique(eq);
            }
            template <class BinaryPredicate>
            void unique(BinaryPredicate pred) {
                iterator it = begin(), e = end();
                while (it != e) {
                    if (pred(*it, *it._next())) {
                        _erase_after(it.m_node);
                    } else {
                        ++it;
                    }
                }
            }

        #ifdef UNBOOST_RVALREF
            forward_list(UNBOOST_RVALREF_TYPE(self_type) other) {
                m_head.m_next = UNBOOST_RVALREF(other).m_head.m_next;
                UNBOOST_RVALREF(other).m_head.m_next = NULL;
            }

            self_type& operator=(UNBOOST_RVALREF_TYPE(self_type) other) {
                clear();
                m_head.m_next = UNBOOST_RVALREF(other).m_head.m_next;
                UNBOOST_RVALREF(other).m_head = NULL;
                return *this;
            }

            void push_front(UNBOOST_RVALREF_TYPE(T) value) {
                _insert_after(before_cbegin(), value);
            }

            void splice_after(const_iterator pos, UNBOOST_RVALREF_TYPE(self_type) other) {
                node_type *node1, *node2, *next1, *next2;
                if (UNBOOST_RVALREF(other).empty()) {
                    return;
                }
                UNBOOST_RVALREF(other).reverse();
                node1 = _node_from_cit(pos);
                node2 = UNBOOST_RVALREF(other).m_head.m_next;
                do {
                    next1 = node1->m_next;
                    next2 = node2->m_next;
                    node1->m_next = node2;
                    node2->m_next = next1;
                    node2 = next2;
                } while (node2);
                UNBOOST_RVALREF(other).m_head.m_next = NULL;
            }
            void splice_after(const_iterator pos, UNBOOST_RVALREF_TYPE(self_type) other,
                              const_iterator it)
            {
                node_type *pos_node = pos.m_node;
                assert(pos_node);
                node_type *it_node = it.m_node;
                if (it_node == NULL)
                    return;

                // remove node from other
                node_type *node = it_node->m_next;
                it_node->m_next = node->m_next;

                // insert node after pos_node
                node_type *next = pos_node->m_next;
                node->m_next = (next ? next->m_next : NULL);
                pos_node->m_next = node;

                if (UNBOOST_RVALREF(other).m_head.m_next == it_node)
                    UNBOOST_RVALREF(other).m_head.m_next = NULL;
            }
            void splice_after(const_iterator pos, UNBOOST_RVALREF_TYPE(self_type) other,
                              const_iterator _before, const_iterator _end)
            {
                node_type *list = NULL;
                node_type *next1;
                node_type *next2 = _node_from_cit(_before);
                node_type *b = next2->m_next;
                node_type *e = _node_from_cit(_end);
                while (b != e) {
                    next1 = b->m_next;
                    b->m_next = list;
                    list = b;
                    b = next1;
                }
                next2->m_next = e;

                node_type *node1 = _node_from_cit(pos);
                node_type *node2 = list;
                while (node2) {
                    next1 = node1->m_next;
                    next2 = node2->m_next;
                    node1->m_next = node2;
                    node2->m_next = next1;
                    node2 = next2;
                }
            }

            iterator insert_after(const_iterator pos, UNBOOST_RVALREF_TYPE(T) value) {
                iterator it(_insert_after(pos, move(value)));
                return it;
            }

            void merge(UNBOOST_RVALREF_TYPE(self_type) other) {
                std::less<T> l;
                merge(other, l);
            }

            template <class Compare>
            void merge(UNBOOST_RVALREF_TYPE(self_type) other, Compare comp) {
                if (this == &UNBOOST_RVALREF(other))
                    return;

                node_type *next;
                node_type *node1 = &m_head;
                node_type *node2 = &UNBOOST_RVALREF(other).m_head;
                m_head.m_next = NULL;
                UNBOOST_RVALREF(other).m_head.m_next = NULL;
                while (node1->m_next && node2->m_next) {
                    if (comp(*node1->get(), *node2->get())) {
                        node1->m_next = m_head.m_next;
                        m_head.m_next = node1;
                        node1 = node1->m_next;
                    } else {
                        next = node2->m_next;
                        node2->m_next = node1->m_next;
                        node1->m_next = node2;
                        node1 = node2;
                        node2 = next;
                    }
                }
                if (node2->m_next) {
                    node1->m_next = node2;
                }
                UNBOOST_RVALREF(other).m_head.m_next = NULL;
            }
        #endif  // def UNBOOST_RVALREF

        protected:
            node_type m_head;

            node_type *_create_node() {
                node_type *node = new node_type();
                _construct_in_place(node->get());
                return node;
            }
            template <typename ARG1>
            node_type *_create_node(const ARG1& arg1) {
                node_type *node = new node_type();
                _construct_in_place(node->get(), arg1);
                return node;
            }
            template <typename ARG1, typename ARG2>
            node_type *_create_node(const ARG1& arg1, const ARG2& arg2) {
                node_type *node = new node_type();
                _construct_in_place(node->get(), arg1, arg2);
                return node;
            }
            template <typename ARG1, typename ARG2, typename ARG3>
            node_type *_create_node(const ARG1& arg1, const ARG2& arg2, const ARG3& arg3) {
                node_type *node = new node_type();
                _construct_in_place(node->get(), arg1, arg2, arg3);
                return node;
            }
            template <typename ARG1, typename ARG2, typename ARG3, typename ARG4>
            node_type *_create_node(const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4) {
                node_type *node = new node_type();
                _construct_in_place(node->get(), arg1, arg2, arg3, arg4);
                return node;
            }
            template <typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
            node_type *_create_node(const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4, const ARG5& arg5) {
                node_type *node = new node_type();
                _construct_in_place(node->get(), arg1, arg2, arg3, arg4, arg5);
                return node;
            }

            node_type *_insert_after(const_iterator pos) {
                node_type *node = _create_node();
                node->m_next = pos.m_node->m_next;
                _node_from_cit(pos)->m_next = node;
                return node;
            }
            template <typename ARG1>
            node_type *_insert_after(const_iterator pos, const ARG1& arg1) {
                node_type *node = _create_node(arg1);
                node->m_next = pos.m_node->m_next;
                _node_from_cit(pos)->m_next = node;
                return node;
            }
            template <typename ARG1, typename ARG2>
            node_type *_insert_after(const_iterator pos, const ARG1& arg1, const ARG2& arg2) {
                node_type *node = _create_node(arg1, arg2);
                node->m_next = pos.m_node->m_next;
                _node_from_cit(pos)->m_next = node;
                return node;
            }
            template <typename ARG1, typename ARG2, typename ARG3>
            node_type *_insert_after(const_iterator pos, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3) {
                node_type *node = _create_node(arg1, arg2, arg3);
                node->m_next = pos.m_node->m_next;
                _node_from_cit(pos)->m_next = node;
                return node;
            }
            template <typename ARG1, typename ARG2, typename ARG3, typename ARG4>
            node_type *_insert_after(const_iterator pos, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4) {
                node_type *node = _create_node(arg1, arg2, arg3, arg4);
                node->m_next = pos.m_node->m_next;
                _node_from_cit(pos)->m_next = node;
                return node;
            }
            template <typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
            node_type *_insert_after(const_iterator pos, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4, const ARG5& arg5) {
                node_type *node = _create_node(arg1, arg2, arg3, arg4, arg5);
                node->m_next = pos.m_node->m_next;
                _node_from_cit(pos)->m_next = node;
                return node;
            }

            void _destroy_node(node_type *node) {
                if (node && node != &m_head) {
                    _destruct(node->get());
                    delete node;
                }
            }

            node_type *_erase_after(node_type *pos) {
                assert(pos);
                node_type *next = pos->m_next;
                if (next == NULL)
                    return NULL;
                pos->m_next = next->m_next;
                _destroy_node(next);
                return pos->m_next;
            }
            node_type *_erase_after(node_type *_before, node_type *_end) {
                node_type *next;
                if (_before == NULL || _before == _end)
                    return NULL;

                next = _before->m_next;
                _before->m_next = _end;
                for (;;) {
                    _before = next;
                    if (_before == _end)
                        break;

                    next = _before->m_next;
                    _destroy_node(_before);
                }

                return _end;
            }

            node_type *_node_from_cit(const_iterator cit) const {
                node_type *node = const_cast<node_type *>(cit.m_node);
                return node;
            }

            void _construct_in_place(void *ptr) {
                new (ptr) _ctor_helper<T>();
            }
            template <typename ARG1>
            void _construct_in_place(void *ptr, const ARG1& arg1) {
                new (ptr) _ctor_helper<T>(arg1);
            }
            template <typename ARG1, typename ARG2>
            void _construct_in_place(void *ptr, const ARG1& arg1, const ARG2& arg2) {
                new (ptr) _ctor_helper<T>(arg1, arg2);
            }
            template <typename ARG1, typename ARG2, typename ARG3>
            void _construct_in_place(void *ptr, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3) {
                new (ptr) _ctor_helper<T>(arg1, arg2, arg3);
            }
            template <typename ARG1, typename ARG2, typename ARG3, typename ARG4>
            void _construct_in_place(void *ptr, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4) {
                new (ptr) _ctor_helper<T>(arg1, arg2, arg3, arg4);
            }
            template <typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
            void _construct_in_place(void *ptr, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4, const ARG5& arg5) {
                new (ptr) _ctor_helper<T>(arg1, arg2, arg3, arg4, arg5);
            }
            void _destruct(T *ptr) {
                ptr->~T();
            }
        }; // forward_list<T>

        template <typename T>
        inline void swap(forward_list<T>& lhs, forward_list<T>& rhs) {
            lhs.swap(rhs);
        }

        //
        // comparisons
        //
        template <typename T>
        inline bool
        operator==(const forward_list<T>& lhs, const forward_list<T>& rhs) {
            if (std::distance(lhs.begin(), lhs.end()) != std::distance(rhs.begin(), rhs.end()))
                return false;
            return std::equal(lhs.begin(), lhs.end(), rhs.begin());
        }
        template <typename T>
        inline bool
        operator!=(const forward_list<T>& lhs, const forward_list<T>& rhs) {
            return !(lhs == rhs);
        }
        template <typename T>
        inline bool
        operator>(const forward_list<T>& lhs, const forward_list<T>& rhs) {
            typename forward_list<T>::const_iterator
                it1 = lhs.cbegin(), end1 = lhs.cend(),
                it2 = rhs.cbegin(), end2 = rhs.cend();
            for (; it1 != end1 && it2 != end2; ++it1, ++it2) {
                if (*it1 <= *it2)
                    return false;
            }
            if (it1 == end1 && it2 == end2)
                return false;
            return (it2 == end2);
        }
        template <typename T>
        inline bool
        operator<=(const forward_list<T>& lhs, const forward_list<T>& rhs) {
            return !(lhs > rhs);
        }
        template <typename T>
        inline bool
        operator<(const forward_list<T>& lhs, const forward_list<T>& rhs) {
            typename forward_list<T>::const_iterator
                it1 = lhs.cbegin(), end1 = lhs.cend(),
                it2 = rhs.cbegin(), end2 = rhs.cend();
            for (; it1 != end1 && it2 != end2; ++it1, ++it2) {
                if (*it1 >= *it2)
                    return false;
            }
            if (it1 == end1 && it2 == end2)
                return false;
            return (it1 == end1);
        }
        template <typename T>
        inline bool
        operator>=(const forward_list<T>& lhs, const forward_list<T>& rhs) {
            return !(lhs < rhs);
        }
    } // namespace unboost
#else
    #error Your compiler is not supported yet. You lose.
#endif

#endif  // ndef UNBOOST_FORWARD_LIST_HPP_
