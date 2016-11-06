// unordered_set.hpp --- Unboost unordered_set and unordered_multiset
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_UNORDERED_SET_HPP_
#define UNBOOST_UNORDERED_SET_HPP_

#include "unboost.hpp"

// If not choosed, choose one
#if ((defined(UNBOOST_USE_CXX11_UNORDERED_SET) + defined(UNBOOST_USE_TR1_UNORDERED_SET) + defined(UNBOOST_USE_BOOST_UNORDERED_SET) + defined(UNBOOST_USE_UNBOOST_UNORDERED_SET)) == 0)
    #ifdef UNBOOST_USE_CXX11
        #define UNBOOST_USE_CXX11_UNORDERED_SET
    #elif defined(UNBOOST_USE_TR1)
        #define UNBOOST_USE_TR1_UNORDERED_SET
    #elif defined(UNBOOST_USE_BOOST)
        #define UNBOOST_USE_BOOST_UNORDERED_SET
    #else
        #if defined(_MSC_VER)
            #if (_MSC_VER >= 1600)
                // Visual C++ 2010 and later
                #ifndef UNBOOST_NO_CXX11
                    #define UNBOOST_USE_CXX11_UNORDERED_SET
                #else
                    #ifndef UNBOOST_NO_TR1
                        #define UNBOOST_USE_TR1_UNORDERED_SET
                    #else
                        #define UNBOOST_USE_UNBOOST_UNORDERED_SET
                    #endif
                #endif
            #elif (_MSC_VER >= 1500)
                // Visual C++ 2008
                #ifndef UNBOOST_NO_TR1
                    #define UNBOOST_USE_TR1_UNORDERED_SET
                #else
                    #define UNBOOST_USE_UNBOOST_UNORDERED_SET
                #endif
            #else
                #define UNBOOST_USE_BOOST_UNORDERED_SET
            #endif
        #elif defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3))
            // GCC 4.3 and later
            #ifndef UNBOOST_NO_TR1
                #define UNBOOST_USE_TR1_UNORDERED_SET
            #else
                #define UNBOOST_USE_UNBOOST_UNORDERED_SET
            #endif
        #else
            #define UNBOOST_USE_UNBOOST_UNORDERED_SET
        #endif
    #endif
#endif

// Adapt choosed one
#ifdef UNBOOST_USE_CXX11_UNORDERED_SET
    #include <unordered_set>            // for std::unordered_set, ...
    namespace unboost {
        using std::unordered_set;
        using std::unordered_multiset;
    }
#elif defined(UNBOOST_USE_TR1_UNORDERED_SET)
    #ifdef _MSC_VER
        #include <unordered_set>
    #else
        #include <tr1/unordered_set>    // for std::tr1::unordered_set, ...
    #endif
    namespace unboost {
        using std::tr1::unordered_set;
        using std::tr1::unordered_multiset;
    }
#elif defined(UNBOOST_USE_BOOST_UNORDERED_SET)
    #include <boost/unordered_set.hpp>  // for boost::unordered_set, ...
    namespace unboost {
        using boost::unordered_set;
        using boost::unordered_multiset;
    }
#elif defined(UNBOOST_USE_UNBOOST_UNORDERED_SET)
    #include <vector>   // for std::vector
    #include <cmath>    // for std::ceil
    #include <iterator> // for std::forward_iterator_tag
    #include "forward_list.hpp"     // for unboost::forward_list
    #include "functional/hash.hpp"  // for unboost::hash

    namespace unboost {
        template <typename Key,
                  typename Hash = unboost::hash<Key>,
                  typename KeyEq = std::equal_to<Key> >
        class unordered_set {
        public:
            typedef unordered_set<Key, Hash, KeyEq>   self_type;
            typedef Key                 key_type;
            typedef Key                 value_type;
            typedef Hash                hasher;
            typedef size_t              size_type;
            typedef ptrdiff_t           difference_type;
            typedef       Key&          reference;
            typedef const Key&          const_reference;
            typedef       Key *         pointer;
            typedef const Key *         const_pointer;
            typedef KeyEq               key_equal;

            struct node_data {
                Key     m_key;
                size_t  m_hash_value;

                node_data() : m_key() { }
                template <typename ARG1>
                node_data(ARG1 arg1) : m_key(arg1) { }
                template <typename ARG1, typename ARG2>
                node_data(ARG1 arg1, ARG2 arg2) : m_key(arg1, arg2) { }
                template <typename ARG1, typename ARG2, typename ARG3>
                node_data(ARG1 arg1, ARG2 arg2, ARG3 arg3) : m_key(arg1, arg2, arg3) { }
                template <typename ARG1, typename ARG2, typename ARG3, typename ARG4>
                node_data(ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4) : m_key(arg1, arg2, arg3, arg4) { }
                template <typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
                node_data(ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5) : m_key(arg1, arg2, arg3, arg4, arg5) { }
            };
            typedef forward_list<node_data>                 list_type;
            typedef typename list_type::node_type           node_type;

            typedef typename list_type::iterator            super_iterator;
            typedef typename list_type::const_iterator      super_const_iterator;

            struct iterator {
                typedef iterator        self_type;
                typedef Key             value_type;
                typedef       Key&      reference;
                typedef const Key&      const_reference;
                typedef       Key *     pointer;
                typedef const Key *     const_pointer;
                typedef size_t          size_type;
                typedef ptrdiff_t       difference_type;
                typedef std::forward_iterator_tag       iterator_category;

                super_iterator          m_super_it;

                iterator() : m_super_it() { }
                iterator(super_iterator si) : m_super_it(si) { }
                iterator(node_type *node) : m_super_it(node) { }
                iterator& operator=(super_iterator si) {
                    m_super_it = si;
                    return *this;
                }

                self_type& operator++() {
                    ++m_super_it;
                    return *this;
                }
                self_type operator++(int) {
                    self_type temp(*this);
                    ++m_super_it;
                    return temp;
                }

                reference operator*() const { return m_super_it->m_key; }
                pointer operator->() const { return &m_super_it->m_key; }

                bool operator==(const self_type& other) const {
                    return m_super_it == other.m_super_it;
                }
                bool operator!=(const self_type& other) const {
                    return m_super_it != other.m_super_it;
                }

                      node_data *_get_data()       { return &*m_super_it; }
                const node_data *_get_data() const { return &*m_super_it; }
                      size_type& _get_hash_value()       { return _get_data()->m_hash_value; }
                const size_type& _get_hash_value() const { return _get_data()->m_hash_value; }
            }; // iterator
            struct const_iterator {
                typedef const_iterator  self_type;
                typedef Key             value_type;
                typedef const Key&      reference;
                typedef const Key *     pointer;
                typedef size_t          size_type;
                typedef ptrdiff_t       difference_type;
                typedef std::forward_iterator_tag       iterator_category;

                super_const_iterator    m_super_it;

                const_iterator() : m_super_it() { }
                const_iterator(iterator it) : m_super_it(it.m_super_it) { }
                const_iterator(super_const_iterator si) : m_super_it(si) { }
                const_iterator(const node_type *node) : m_super_it(node) { }
                const_iterator& operator=(super_const_iterator si) {
                    m_super_it = si;
                    return *this;
                }

                reference operator*() const { return m_super_it->m_key; }
                pointer operator->() const { return &m_super_it->m_key; }

                bool operator==(const self_type& other) const {
                    return m_super_it == other.m_super_it;
                }
                bool operator!=(const self_type& other) const {
                    return m_super_it != other.m_super_it;
                }

                const node_data *_get_data() const { return m_super_it->get(); }
                const size_type& _get_hash_value() const { return _get_data()->m_hash_value; }
            }; // const_iterator

            struct local_iterator {
                typedef local_iterator  self_type;
                typedef Key             value_type;
                typedef       Key&      reference;
                typedef const Key&      const_reference;
                typedef       Key *     pointer;
                typedef const Key *     const_pointer;
                typedef size_t          size_type;
                typedef ptrdiff_t       difference_type;
                typedef std::forward_iterator_tag                           iterator_category;

                super_iterator          m_super_it;
                size_type               m_b_index;
                size_type               m_b_count;

                local_iterator() : m_super_it(), m_b_index(0), m_b_count(0) { }

                local_iterator(super_iterator si, size_type index, size_type count)
                    : m_super_it(si), m_b_index(index), m_b_count(count) { }

                reference _get_key() {
                    return *m_super_it.m_node->get()->m_key;
                }
                const_reference _get_key() const {
                    return *m_super_it.m_node->get()->m_key;
                }
                size_type& _get_hash_value() {
                    return *m_super_it.m_node->get()->m_hash_value;
                }
                const size_type& _get_hash_value() const {
                    return *m_super_it.m_node->get()->m_hash_value;
                }

                reference operator*() const { return _get_key(); }
                pointer operator->() const { return &_get_key(); }

                void _fix() {
                    if (m_super_it.m_node) {
                        if (_get_hash_value() % m_b_count != m_b_index)
                            m_super_it.m_node = NULL;
                    }
                }

                self_type& operator++() {
                    ++m_super_it;
                    _fix();
                    return *this;
                }
                self_type operator++(int) {
                    self_type temp(*this);
                    ++m_super_it;
                    _fix();
                    return temp;
                }

                bool operator==(const self_type& other) const {
                    return m_super_it == other.m_super_it;
                }
                bool operator!=(const self_type& other) const {
                    return m_super_it != other.m_super_it;
                }
            }; // local_iterator

            struct local_const_iterator {
                typedef local_const_iterator    self_type;
                typedef       Key               value_type;
                typedef const Key&              reference;
                typedef const Key *             pointer;
                typedef size_t                  size_type;
                typedef ptrdiff_t               difference_type;

                super_const_iterator            m_super_it;
                size_type                       m_b_index;
                size_type                       m_b_count;

                local_const_iterator() : m_super_it(), m_b_index(0), m_b_count(0) { }

                local_const_iterator(local_iterator it) : m_super_it(it.m_super_it),
                    m_b_index(it.m_b_index), m_b_count(it.m_b_count) { }

                local_const_iterator(super_const_iterator si, size_type index, size_type count)
                    : m_super_it(si), m_b_index(index), m_b_count(count) { }

                const_reference _get_key() const {
                    return *m_super_it.m_node->get()->key;
                }
                const size_type& _get_hash_value() const {
                    return *m_super_it.m_node->get()->hash_value;
                }

                reference operator*() const { return _get_key(); }
                pointer operator->() const { return &_get_key(); }

                void _fix() {
                    if (m_super_it.m_node) {
                        if (_get_hash_value() % m_b_count != m_b_index)
                            m_super_it.m_node = NULL;
                    }
                }

                self_type& operator++() {
                    ++m_super_it;
                    _fix();
                    return *this;
                }
                self_type operator++(int) {
                    self_type temp(*this);
                    ++m_super_it;
                    _fix();
                    return temp;
                }

                bool operator==(const self_type& other) const {
                    return m_super_it == other.m_super_it;
                }
                bool operator!=(const self_type& other) const {
                    return m_super_it != other.m_super_it;
                }
            }; // local_const_iterator

            struct bucket_type {
                super_iterator  m_super_it;
                size_type       m_count;

                bucket_type() : m_super_it(), m_count(0) { }

                void _fix(size_type i, size_type count) {
                    size_type hash_value = m_super_it->m_hash_value;
                    if (hash_value % count != i) {
                        super_iterator super_it;
                        m_super_it = super_it;
                    }
                }
            }; // bucket_type

            unordered_set() : m_element_count(0), m_max_load_factor(1) {
                _init_buckets(5);
            }

            unordered_set(size_type n, const hasher& hash_fn = hasher(),
                          const key_equal& ke = key_equal())
                : m_element_count(0), m_max_load_factor(1),
                  m_hasher(hash_fn), m_key_eq(ke)
            {
                _init_buckets(n);
            }

            template <typename InputIterator>
            unordered_set(InputIterator first, InputIterator last,
                          size_type n = 5, const hasher& hash_fn = hasher(),
                          const key_equal& ke = key_equal())
                : m_element_count(0), m_max_load_factor(1),
                  m_hasher(hash_fn), m_key_eq(ke)
            {
                _init_buckets(n);
                insert(first, last);
            }

            unordered_set(const self_type& other)
                : m_element_count(0), m_max_load_factor(1)
            {
                _init_buckets(5);
                insert(other.begin(), other.end());
            }

                  iterator  begin()       { return m_list.begin(); }
            const_iterator  begin() const { return cbegin(); }
            const_iterator cbegin() const { return m_list.cbegin(); }
                  iterator  end()         { return m_list.end(); }
            const_iterator  end() const   { return cend(); }
            const_iterator cend() const   { return const_iterator(m_list.cend()); }

            local_iterator begin(size_type n) {
                if (_is_bucket_empty(n)) {
                    local_iterator lit;
                    return lit;
                } else {
                    iterator it = m_buckets[n].m_super_it;
                    const size_type hash_value = it._get_hash_value();
                    const size_type count = bucket_count();
                    local_iterator lit(it, hash_value % count, count);
                    return lit;
                }
            }
            local_const_iterator begin(size_type n) const {
                return cbegin(n);
            }
            local_const_iterator cbegin(size_type n) const {
                if (_is_bucket_empty(n)) {
                    local_const_iterator lit;
                    return lit;
                } else {
                    const_iterator it = m_buckets[n].m_super_it;
                    const size_type hash_value = it._get_hash_value();
                    const size_type count = bucket_count();
                    local_const_iterator lit(it, hash_value % count, count);
                    return lit;
                }
            }

            local_iterator end(size_type n) {
                local_iterator it;
                return it;
            }
            local_const_iterator end(size_type n) const {
                return cend();
            }
            local_const_iterator cend(size_type n) const {
                local_const_iterator it;
                return it;
            }

            size_type bucket(const Key& key) const {
                return hash_function()(key) % bucket_count();
            }
            size_type bucket_count() const {
                return m_buckets.size();
            }
            size_type bucket_size(size_type i) const {
                assert(i < bucket_count());
                return m_buckets[i].m_count;
            }

            void clear() {
                m_list.clear();
                _init_buckets(5);
                m_element_count = 0;
            }

            size_type size() const {
                return m_element_count;
            }
            bool empty() const {
                return size() == 0;
            }

            iterator emplace_hint(const_iterator it) {
                return emplace().first;
            }
            template <typename ARG1>
            iterator emplace_hint(const_iterator it, const ARG1& arg1) {
                return emplace(arg1).first;
            }
            template <typename ARG1, typename ARG2>
            iterator emplace_hint(const_iterator it, const ARG1& arg1, const ARG2& arg2) {
                return emplace(arg1, arg2).first;
            }
            template <typename ARG1, typename ARG2, typename ARG3>
            iterator emplace_hint(const_iterator it, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3) {
                return emplace(arg1, arg2, arg3).first;
            }
            template <typename ARG1, typename ARG2, typename ARG3, typename ARG4>
            iterator emplace_hint(const_iterator it, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4) {
                return emplace(arg1, arg2, arg3, arg4).first;
            }
            template <typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
            iterator emplace_hint(const_iterator it, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4, const ARG5& arg5) {
                return emplace(arg1, arg2, arg3, arg4, arg5).first;
            }

            hasher hash_function() const {
                return m_hasher;
            }

            key_equal key_eq() const {
                return m_key_eq;
            }

            float load_factor() const {
                return float(m_element_count) / m_buckets.size();
            }

            size_type max_bucket_count() const {
                return (size_type(-1) - sizeof(*this)) / sizeof(bucket_type);
            }

            float max_load_factor() const {
                return m_max_load_factor;
            }

            void max_load_factor(float ml) const {
                m_max_load_factor = ml;
            }

            size_type max_size() {
                return (size_type(-1) - sizeof(*this)) / sizeof(node_type);
            }

            void rehash(size_type count) {
                assert(count);
                _init_buckets(count);
                super_iterator it = m_list.begin(), iend = m_list.end();
                for (; it != iend; ++it) {
                    _add(it, it.m_node);
                }
            }

            void reserve(size_type count) {
                size_type c = size_type(std::ceil(count / max_load_factor()));
                rehash(c);
            }

            void swap(self_type& other) {
                swap(m_element_count, other.m_element_count);
                swap(m_max_load_factor, other.m_max_load_factor);
                swap(m_hasher, other.m_hasher);
                swap(m_key_eq, other.m_list);
                swap(m_list, other.m_list);
                swap(m_buckets, other.m_buckets);
            }

            iterator find(const Key& key) {
                const size_type i = bucket(key);
                super_iterator it = m_buckets[i].m_super_it, iend;
                while (it != iend) {
                    const size_type hash_value = it->m_hash_value;
                    if (hash_value % bucket_count() != i) {
                        return iend;
                    }
                    if (key_eq()(it->m_key, key)) {
                        return it;
                    }
                    ++it;
                }
                return iend;
            }
            const_iterator find(const Key& key) const {
                const size_type i = bucket(key);
                super_const_iterator it = m_buckets[i].m_super_it, iend;
                while (it != iend) {
                    const size_type hash_value = it->m_hash_value;
                    if (hash_value % bucket_count() != i) {
                        return iend;
                    }
                    if (key_eq()(it->m_key, key)) {
                        return it;
                    }
                    ++it;
                }
                return iend;
            }

            //
            //
            //
            size_type count(const Key& key) const {
                return find(key) != end();
            }

            std::pair<iterator, bool>
            emplace() {
                node_type *node = m_list._create_node();
                const Key& key = node->get()->m_key;
                return _emplace_key_node(key, node);
            }
            template <typename ARG1>
            std::pair<iterator, bool>
            emplace(const ARG1& arg1) {
                node_type *node = m_list._create_node(arg1);
                const Key& key = node->get()->m_key;
                return _emplace_key_node(key, node);
            }
            template <typename ARG1, typename ARG2>
            std::pair<iterator, bool>
            emplace(const ARG1& arg1, const ARG2& arg2) {
                node_type *node = m_list._create_node(arg1, arg2);
                const Key& key = node->get()->m_key;
                return _emplace_key_node(key, node);
            }
            template <typename ARG1, typename ARG2, typename ARG3>
            std::pair<iterator, bool>
            emplace(const ARG1& arg1, const ARG2& arg2, const ARG3& arg3) {
                node_type *node = m_list._create_node(arg1, arg2, arg3);
                const Key& key = node->get()->m_key;
                return _emplace_key_node(key, node);
            }
            template <typename ARG1, typename ARG2, typename ARG3, typename ARG4>
            std::pair<iterator, bool>
            emplace(const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4) {
                node_type *node = m_list._create_node(arg1, arg2, arg3, arg4);
                const Key& key = node->get()->m_key;
                return _emplace_key_node(key, node);
            }
            template <typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
            std::pair<iterator, bool>
            emplace(const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4, const ARG5& arg5) {
                node_type *node = m_list._create_node(arg1, arg2, arg3, arg4, arg5);
                const Key& key = node->get()->m_key;
                return _emplace_key_node(key, node);
            }

            std::pair<iterator, iterator> equal_range(const Key& key) {
                iterator first = find(key);
                return std::make_pair(first, first);
            }
            std::pair<const_iterator, const_iterator>
            equal_range(const Key& key) const {
                const_iterator first = find(key);
                return std::make_pair(first, first);
            }

            iterator erase(const_iterator pos) {
                assert(pos != cend());
                const Key& key = pos.m_super_it->m_key;
                size_type i = bucket(key);
                super_const_iterator prev_it;
                if (key_eq()(key, m_buckets[i].m_super_it->m_key)) {
                    prev_it = m_list.before_cbegin();
                } else {
                    prev_it = m_buckets[i].m_super_it;
                }
                super_const_iterator iend = m_list.cend();
                super_const_iterator it = prev_it;
                ++it;
                while (it != iend) {
                    if (it == pos.m_super_it) {
                        _remove(it, i);
                        --m_element_count;
                        return m_list.erase_after(prev_it);
                    }
                    ++it;
                    ++prev_it;
                }
                return end();
            }
            size_type erase(const Key& key) {
                iterator it = find(key);
                return erase(it) != end();
            }
            iterator erase(const_iterator first, const_iterator last) {
                while (first != last) {
                    erase(first);
                    ++first;
                }
                return iterator(const_cast<node_type *>(last.m_node));
            }

            std::pair<iterator, bool> insert(const Key& key) {
                return emplace(key);
            }

            self_type& operator=(const self_type& other) {
                clear();
                m_max_load_factor = other.m_max_load_factor;
                m_hasher = other.m_hasher;
                m_key_eq = other.m_key_eq;
                insert(other.begin(), other.end());
                return *this;
            }

        #if 0
            unordered_set(self_type&& other) {
                ...
            }
            self_type& operator=(self_type&& other) {
                ...
                return *this;
            }
        #endif

        protected:
            size_type                   m_element_count;
            float                       m_max_load_factor;
            Hash                        m_hasher;
            KeyEq                       m_key_eq;
            list_type                   m_list;
            std::vector<bucket_type>    m_buckets;

            void _init_buckets(size_type count) {
                m_buckets.clear();
                m_buckets.resize(count);
            }
            bool _is_bucket_empty(size_type i) const {
                assert(i < bucket_count());
                return m_buckets[i].m_count == 0;
            }
            void _rehash_if_case() {
                if (load_factor() > max_load_factor()) {
                    rehash(bucket_count() * 2);
                }
            }
            void _add(super_iterator super_it, node_type *node) {
                node_data *data = node->get();
                assert(data);
                size_type i = bucket(data->m_key);
                if (m_buckets[i].m_super_it == super_iterator()) {
                    m_buckets[i].m_super_it = super_it;
                }
                ++(m_buckets[i].m_count);
                _rehash_if_case();
            }
            void _add_2(super_iterator super_it, size_type i) {
                assert(i < bucket_count());
                if (m_buckets[i].m_super_it == super_iterator()) {
                    m_buckets[i].m_super_it = super_it;
                }
                ++(m_buckets[i].m_count);
                ++m_element_count;
                _rehash_if_case();
            }
            void _add_2(node_type *node, size_type i) {
                super_iterator it(node);
                _add_2(it, i);
            }
            void _remove(super_const_iterator super_it, size_type i) {
                assert(i < bucket_count());
                assert(!_is_bucket_empty(i));
                --(m_buckets[i].m_count);
                if (m_buckets[i].m_count == 0) {
                    super_iterator sit;
                    m_buckets[i].m_super_it = sit;
                    return;
                }
                super_const_iterator bucket_it = m_buckets[i].m_super_it;
                if (bucket_it == super_it) {
                    const Key& key = bucket_it->m_key;
                    const size_type hash_value = hash_function()(key);
                    const size_type count = bucket_count();
                    ++(m_buckets[i].m_super_it);
                    m_buckets[i]._fix(hash_value % count, count);
                }
            }

            std::pair<iterator, bool>
            _emplace_key_node(const Key& key, node_type *node) {
                iterator it = find(key);
                if (it != end()) {
                    delete node;
                    return std::make_pair(it, false);
                }
                node->get()->m_hash_value = hash_function()(key);
                const size_type i = bucket(node->get()->m_hash_value);
                super_iterator sit;
                if (_is_bucket_empty(i))
                    sit = m_list.before_begin();
                else
                    sit = m_buckets[i].m_super_it;
                m_list._add_node_after(sit, node);
                _add_2(node, i);
                return std::make_pair(node, true);
            }
        }; // unordered_set<Key, Hash, KeyEq>
    } // namespace unboost
#else
    #error Your compiler is not supported yet. You lose.
#endif

#endif  // ndef UNBOOST_UNORDERED_SET_HPP_
