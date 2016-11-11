// unordered_map.hpp --- Unboost unordered_map and unordered_multimap
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_UNORDERED_MAP_HPP_
#define UNBOOST_UNORDERED_MAP_HPP_

#include "unboost.hpp"
#include "rv_ref.hpp"   // for unboost::move, UNBOOST_RV_REF, ...

// If not choosed, choose one
#if ((defined(UNBOOST_USE_CXX11_UNORDERED_MAP) + defined(UNBOOST_USE_TR1_UNORDERED_MAP) + defined(UNBOOST_USE_BOOST_UNORDERED_MAP) + defined(UNBOOST_USE_UNBOOST_UNORDERED_MAP)) == 0)
    #ifdef UNBOOST_USE_CXX11
        #define UNBOOST_USE_CXX11_UNORDERED_MAP
    #elif defined(UNBOOST_USE_TR1)
        #define UNBOOST_USE_TR1_UNORDERED_MAP
    #else
        #if defined(_MSC_VER)
            #if (_MSC_VER >= 1600)
                // Visual C++ 2010 and later
                #ifndef UNBOOST_NO_CXX11
                    #define UNBOOST_USE_CXX11_UNORDERED_MAP
                #else
                    #ifndef UNBOOST_NO_TR1
                        #define UNBOOST_USE_TR1_UNORDERED_MAP
                    #else
                        #define UNBOOST_USE_UNBOOST_UNORDERED_MAP
                    #endif
                #endif
            #elif (_MSC_VER >= 1500)
                // Visual C++ 2008
                #ifndef UNBOOST_NO_TR1
                    #define UNBOOST_USE_TR1_UNORDERED_MAP
                #else
                    #define UNBOOST_USE_UNBOOST_UNORDERED_MAP
                #endif
            #else
                #define UNBOOST_USE_UNBOOST_UNORDERED_MAP
            #endif
        #elif defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3))
            // GCC 4.3 and later
            #ifndef UNBOOST_NO_TR1
                #define UNBOOST_USE_TR1_UNORDERED_MAP
            #else
                #define UNBOOST_USE_UNBOOST_UNORDERED_MAP
            #endif
        #else
            #define UNBOOST_USE_UNBOOST_UNORDERED_MAP
        #endif
    #endif
#endif

// Adapt choosed one
#ifdef UNBOOST_USE_CXX11_UNORDERED_MAP
    #include <unordered_map>            // for std::unordered_map, ...
    namespace unboost {
        using std::pair;
        using std::unordered_map;
        using std::unordered_multimap;
    }
#elif defined(UNBOOST_USE_TR1_UNORDERED_MAP)
    #ifdef _MSC_VER
        #include <unordered_map>        // for std::tr1::unordered_map, ...
    #else
        #include <tr1/unordered_map>    // for std::tr1::unordered_map, ...
    #endif
    namespace unboost {
        using std::pair;
        using std::tr1::unordered_map;
        using std::tr1::unordered_multimap;
    }
#elif defined(UNBOOST_USE_BOOST_UNORDERED_MAP)
    #include <boost/unordered_map.hpp>  // for boost::unordered_map, ...
    namespace unboost {
        using std::pair;
        using boost::unordered_map;
        using boost::unordered_multimap;
    }
#elif defined(UNBOOST_USE_UNBOOST_UNORDERED_MAP)
    #include <vector>               // for std::vector
    #include <cmath>                // for std::ceil
    #include <iterator>             // for std::forward_iterator_tag
    #include <functional>           // for std::equal_to
    #include <algorithm>            // for std::is_permutation
    #include "exception.hpp"        // for unboost::out_of_range
    #include "forward_list.hpp"     // for unboost::forward_list
    #include "functional/hash.hpp"  // for unboost::hash

    namespace unboost {
        using std::pair;

        template <typename Key,
                  typename Mapped,
                  typename Hash = unboost::hash<Key>,
                  typename KeyEq = std::equal_to<Key> >
        class unordered_map {
        public:
            typedef unordered_map<Key, Mapped, Hash, KeyEq>   self_type;
            typedef Key                             key_type;
            typedef Mapped                          mapped_type;
            typedef std::pair<const Key, Mapped>    value_type;
            typedef size_t                          size_type;
            typedef ptrdiff_t                       difference_type;
            typedef Hash                            hasher;
            typedef KeyEq                           key_equal;
            typedef       value_type&               reference;
            typedef const value_type&               const_reference;
            typedef       value_type *              pointer;
            typedef const value_type *              const_pointer;

            struct node_data {
                value_type  m_value;
                size_t      m_hash_value;

                node_data() : m_value() { }
                template <typename ARG1>
                node_data(ARG1 arg1) : m_value(arg1) { }
                template <typename ARG1, typename ARG2>
                node_data(ARG1 arg1, ARG2 arg2) : m_value(arg1, arg2) { }
            };
            typedef forward_list<node_data>                 list_type;
            typedef typename list_type::node_type           node_type;

            typedef typename list_type::iterator            super_iterator;
            typedef typename list_type::const_iterator      super_const_iterator;

            struct iterator {
                typedef iterator                        self_type;
                typedef std::pair<const Key, Mapped>    value_type;
                typedef       value_type&               reference;
                typedef const value_type&               const_reference;
                typedef       value_type *              pointer;
                typedef const value_type *              const_pointer;
                typedef size_t                          size_type;
                typedef ptrdiff_t                       difference_type;
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

                reference operator*() const { return m_super_it->m_value; }
                pointer operator->() const { return &m_super_it->m_value; }

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
                typedef const_iterator                  self_type;
                typedef std::pair<const Key, Mapped>    value_type;
                typedef const value_type&               reference;
                typedef const value_type *              pointer;
                typedef size_t                          size_type;
                typedef ptrdiff_t                       difference_type;
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

                self_type& operator++() {
                    ++m_super_it;
                    return *this;
                }
                self_type operator++(int) {
                    self_type temp(*this);
                    ++m_super_it;
                    return temp;
                }

                reference operator*() const { return m_super_it->m_value; }
                pointer operator->() const { return &m_super_it->m_value; }

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
                typedef local_iterator                  self_type;
                typedef std::pair<const Key, Mapped>    value_type;
                typedef       value_type&               reference;
                typedef const value_type&               const_reference;
                typedef       value_type *              pointer;
                typedef const value_type *              const_pointer;
                typedef size_t                          size_type;
                typedef ptrdiff_t                       difference_type;
                typedef std::forward_iterator_tag       iterator_category;

                super_iterator          m_super_it;
                size_type               m_b_index;
                size_type               m_b_count;

                local_iterator() : m_super_it(), m_b_index(0), m_b_count(0) { }

                local_iterator(super_iterator si, size_type index, size_type count)
                    : m_super_it(si), m_b_index(index), m_b_count(count) { }

                reference _get_value() {
                    return m_super_it.m_node->get()->m_value;
                }
                const_reference _get_value() const {
                    return m_super_it.m_node->get()->m_value;
                }
                size_type& _get_hash_value() {
                    return m_super_it.m_node->get()->m_hash_value;
                }
                const size_type& _get_hash_value() const {
                    return m_super_it.m_node->get()->m_hash_value;
                }

                      reference operator*()       { return _get_value(); }
                const_reference operator*() const { return _get_value(); }
                const_pointer operator->() const  { return &_get_value(); }

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
                typedef local_const_iterator            self_type;
                typedef std::pair<const Key, Mapped>    value_type;
                typedef const value_type&               reference;
                typedef const value_type *              pointer;
                typedef size_t                          size_type;
                typedef ptrdiff_t                       difference_type;

                super_const_iterator                    m_super_it;
                size_type                               m_b_index;
                size_type                               m_b_count;

                local_const_iterator() : m_super_it(), m_b_index(0), m_b_count(0) { }

                local_const_iterator(local_iterator it) : m_super_it(it.m_super_it),
                    m_b_index(it.m_b_index), m_b_count(it.m_b_count) { }

                local_const_iterator(super_const_iterator si, size_type index, size_type count)
                    : m_super_it(si), m_b_index(index), m_b_count(count) { }

                const Key& _get_key() const {
                    return m_super_it.m_node->get()->key;
                }
                const size_type& _get_hash_value() const {
                    return m_super_it.m_node->get()->hash_value;
                }

                Key&operator*() const { return _get_key(); }
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

            unordered_map() : m_element_count(0), m_max_load_factor(1) {
                _init_buckets(5);
            }

            unordered_map(size_type n, const hasher& hash_fn = hasher(),
                          const key_equal& ke = key_equal())
                : m_element_count(0), m_max_load_factor(1),
                  m_hasher(hash_fn), m_key_eq(ke)
            {
                _init_buckets(n);
            }

            template <typename InputIterator>
            unordered_map(InputIterator first, InputIterator last,
                          size_type n = 20, const hasher& hash_fn = hasher(),
                          const key_equal& ke = key_equal())
                : m_element_count(0), m_max_load_factor(1),
                  m_hasher(hash_fn), m_key_eq(ke)
            {
                _init_buckets(n);
                insert(first, last);
            }

            unordered_map(const self_type& other)
                : m_element_count(0), m_max_load_factor(1)
            {
                _init_buckets(other.bucket_count());
                insert(other.begin(), other.end());
            }

            ~unordered_map() {
                clear();
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
                    super_iterator it = m_buckets[n].m_super_it;
                    const size_type hash_value = it->m_hash_value;
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
                    super_const_iterator it = m_buckets[n].m_super_it;
                    const size_type hash_value = it->m_hash_value;
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
            iterator emplace_hint(const_iterator it, ARG1 arg1) {
                return emplace(arg1).first;
            }
            template <typename ARG1, typename ARG2>
            iterator emplace_hint(const_iterator it, ARG1 arg1, ARG2 arg2) {
                return emplace(arg1, arg2).first;
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

            void max_load_factor(float ml) {
                m_max_load_factor = ml;
            }

            size_type max_size() {
                return (size_type(-1) - sizeof(*this)) / sizeof(node_type);
            }

            void rehash(size_type count) {
                assert(count);
                size_type proposal = size_type(size() / max_load_factor());
                ++proposal;
                if (count < proposal)
                    count = proposal;
                if (count == bucket_count())
                    return;
                _init_buckets(count);
                node_type *node = m_list.m_head.m_next;
                node_type *next;
                m_list.m_head.m_next = NULL;
                while (node) {
                    next = node->m_next;
                    _emplace_node_0(node);
                    node = next;
                }
                assert(float(bucket_count()) > size() / max_load_factor());
                assert(bucket_count() >= count);
            }

            void reserve(size_type count) {
                size_type c = size_type(std::ceil(count / max_load_factor()));
                rehash(c);
            }

            void swap(self_type& other) {
                unboost::swap(m_element_count, other.m_element_count);
                unboost::swap(m_max_load_factor, other.m_max_load_factor);
                unboost::swap(m_hasher, other.m_hasher);
                unboost::swap(m_key_eq, other.m_key_eq);
                unboost::swap(m_list, other.m_list);
                unboost::swap(m_buckets, other.m_buckets);
            }

            iterator find(const Key& key) {
                const size_type i = bucket(key);
                super_iterator it = m_buckets[i].m_super_it, iend;
                while (it != iend) {
                    const size_type hash_value = it->m_hash_value;
                    if (hash_value % bucket_count() != i) {
                        return iend;
                    }
                    if (key_eq()(it->m_value.first, key)) {
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
                    if (key_eq()(it->m_value.first, key)) {
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
                value_type value();
                iterator it = find(value.first);
                if (it != end()) {
                    return std::make_pair(it, false);
                }
                node_type *node = m_list._create_node();
                return _emplace_value_node(value, node);
            }
            template <typename ARG1>
            std::pair<iterator, bool>
            emplace(ARG1 arg1) {
                value_type value(arg1);
                iterator it = find(value.first);
                if (it != end()) {
                    return std::make_pair(it, false);
                }
                node_type *node = m_list._create_node(arg1);
                return _emplace_value_node(value, node);
            }
            template <typename ARG1, typename ARG2>
            std::pair<iterator, bool>
            emplace(ARG1 arg1, ARG2 arg2) {
                value_type value(arg1, arg2);
                iterator it = find(value.first);
                if (it != end()) {
                    return std::make_pair(it, false);
                }
                node_type *node = m_list._create_node(arg1, arg2);
                return _emplace_value_node(value, node);
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
                const Key& key = pos.m_super_it->m_value.first;
                size_type i = bucket(key);
                super_const_iterator prev_it;
                if (key_eq()(key, m_buckets[i].m_super_it->m_value.first)) {
                    prev_it = m_list.cbefore_begin();
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
                    first = erase(first);
                }
                return iterator(const_cast<node_type *>(last.m_node));
            }

            std::pair<iterator, bool> insert(const value_type& value) {
                return emplace(value);
            }
            iterator insert(const_iterator hint, const value_type& value) {
                return insert(value).first;
            }
            template <typename InputIterator>
            void insert(InputIterator first, InputIterator last) {
                while (first != last) {
                    insert(*first);
                    ++first;
                }
            }

            self_type& operator=(const self_type& other) {
                clear();
                m_max_load_factor = other.m_max_load_factor;
                m_hasher = other.m_hasher;
                m_key_eq = other.m_key_eq;
                insert(other.begin(), other.end());
                return *this;
            }

#ifdef UNBOOST_RV_REF
            unordered_map(UNBOOST_RV_REF(self_type) other) {
                m_element_count = UNBOOST_RV(other).m_element_count;
                m_max_load_factor = UNBOOST_RV(other).m_max_load_factor;
                m_hasher = UNBOOST_RV(other).m_hasher;
                m_key_eq = UNBOOST_RV(other).m_key_eq;
                m_list.swap(UNBOOST_RV(other).m_list);
                m_buckets.swap(UNBOOST_RV(other).m_buckets);
            }

            self_type& operator=(UNBOOST_RV_REF(self_type) other) {
                m_element_count = UNBOOST_RV(other).m_element_count;
                m_max_load_factor = UNBOOST_RV(other).m_max_load_factor;
                m_hasher = UNBOOST_RV(other).m_hasher;
                m_key_eq = UNBOOST_RV(other).m_key_eq;
                m_list.swap(UNBOOST_RV(other).m_list);
                m_buckets.swap(UNBOOST_RV(other).m_buckets);
                return *this;
            }

            // NOTE: we don't support the following two methods:
            //   std::pair<iterator, bool> insert(UNBOOST_RV_REF(Key) key) { ... }
            //   iterator insert(const_iterator hint, UNBOOST_RV_REF(Key) key) { ... }
#endif  // def UNBOOST_RV_REF

            Mapped& operator[](const Key& key) {
                iterator it = find(key);
                if (it == end()) {
                    Mapped mapped;
                    it = emplace(key, mapped).first;
                }
                return it->second;
            }
            const Mapped& operator[](const Key& key) const {
                const_iterator it = find(key);
                return it->second;
            }

            Mapped& at(const Key& key) {
                iterator it = find(key);
                if (it == end()) {
                    throw out_of_range("unordered_map::at");
                }
                return it->second;
            }
            const Mapped& at(const Key& key) const {
                const_iterator it = find(key);
                if (it == end()) {
                    throw out_of_range("unordered_map::at");
                }
                return it->second;
            }

        protected:
            size_type                   m_element_count;
            float                       m_max_load_factor;
            Hash                        m_hasher;
            KeyEq                    m_key_eq;
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
                    const Key& key = bucket_it->m_value.first;
                    const size_type hash_value = hash_function()(key);
                    const size_type count = bucket_count();
                    ++(m_buckets[i].m_super_it);
                    m_buckets[i]._fix(hash_value % count, count);
                }
            }

            std::pair<iterator, bool>
            _emplace_node_0(node_type *node) {
                const size_type i = node->get()->m_hash_value % bucket_count();
                if (_is_bucket_empty(i)) {
                    m_list._add_node_after(m_list.before_begin(), node);
                    m_buckets[i].m_super_it = node;
                } else {
                    m_list._add_node_after(m_buckets[i].m_super_it, node);
                }
                ++(m_buckets[i].m_count);
                ++m_element_count;
                return std::make_pair(node, true);
            }

            std::pair<iterator, bool>
            _emplace_value_node(const value_type& value, node_type *node) {
                node->get()->m_hash_value = hash_function()(value.first);
                std::pair<iterator, bool> ret = _emplace_node_0(node);
                _rehash_if_case();
                return ret;
            }
        }; // unordered_map<Key, Mapped, Hash, KeyEq>

        template <typename Key, typename Mapped, typename Hash, typename KeyEq>
        inline void
        swap(unordered_map<Key, Mapped, Hash, KeyEq>& lhs,
             unordered_map<Key, Mapped, Hash, KeyEq>& rhs)
        {
            lhs.swap(rhs);
        }

        template <typename Key, typename Mapped, typename Hash, typename KeyEq>
        inline bool operator==(
            const unordered_map<Key, Mapped, Hash, KeyEq>& lhs,
            const unordered_map<Key, Mapped, Hash, KeyEq>& rhs)
        {
            typedef typename
                unordered_map<Key, Mapped, Hash, KeyEq>::const_iterator const_iterator;
            if (&lhs == &rhs)
                return true;
            if (lhs.size() != rhs.size())
                return false;
            const_iterator lhs_eq1 = lhs.begin(), lhs_end = lhs.end();
            while (lhs_eq1 != lhs_end) {
                std::pair<const_iterator, const_iterator> lhs_range, rhs_range;
                lhs_range = lhs.equal_range(lhs_eq1->m_value.first);
                const_iterator lhs_eq1 = lhs_range.first;
                const_iterator lhs_eq2 = lhs_range.second;
                rhs_range = rhs.equal_range(lhs_eq1->m_value.first);
                const_iterator rhs_eq1 = rhs_range.first;
                const_iterator rhs_eq2 = rhs_range.second;
                if (std::distance(lhs_eq1, lhs_eq2) != std::distance(rhs_eq1, rhs_eq2))
                    return false;
                if (!std::is_permutation(lhs_eq1, lhs_eq2, rhs_eq1))
                    return false;
                lhs_eq1 = lhs_range.second;
            }
            return true;
        }
        template <typename Key, typename Mapped, typename Hash, typename KeyEq>
        inline bool operator!=(
            const unordered_map<Key, Mapped, Hash, KeyEq>& lhs,
            const unordered_map<Key, Mapped, Hash, KeyEq>& rhs)
        {
            return !(lhs == rhs);
        }

        template <typename Key,
                  typename Mapped,
                  typename Hash = unboost::hash<Key>,
                  typename KeyEq = std::equal_to<Key> >
        class unordered_multimap {
        public:
            typedef unordered_multimap<Key, Mapped, Hash, KeyEq>   self_type;
            typedef Key                             key_type;
            typedef Mapped                          mapped_type;
            typedef std::pair<const Key, Mapped>    value_type;
            typedef size_t                          size_type;
            typedef ptrdiff_t                       difference_type;
            typedef Hash                            hasher;
            typedef KeyEq                           key_equal;
            typedef       value_type&               reference;
            typedef const value_type&               const_reference;
            typedef       value_type *              pointer;
            typedef const value_type *              const_pointer;

            struct node_data {
                value_type  m_value;
                size_t      m_hash_value;

                node_data() : m_value() { }
                template <typename ARG1>
                node_data(ARG1 arg1) : m_value(arg1) { }
                template <typename ARG1, typename ARG2>
                node_data(ARG1 arg1, ARG2 arg2) : m_value(arg1, arg2) { }
            };
            typedef forward_list<node_data>                 list_type;
            typedef typename list_type::node_type           node_type;

            typedef typename list_type::iterator            super_iterator;
            typedef typename list_type::const_iterator      super_const_iterator;

            struct iterator {
                typedef iterator                        self_type;
                typedef std::pair<const Key, Mapped>    value_type;
                typedef       value_type&               reference;
                typedef const value_type&               const_reference;
                typedef       value_type *              pointer;
                typedef const value_type *              const_pointer;
                typedef size_t                          size_type;
                typedef ptrdiff_t                       difference_type;
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

                reference operator*() const { return m_super_it->m_value; }
                pointer operator->() const { return &m_super_it->m_value; }

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
                typedef const_iterator                  self_type;
                typedef std::pair<const Key, Mapped>    value_type;
                typedef const value_type&               reference;
                typedef const value_type *              pointer;
                typedef size_t                          size_type;
                typedef ptrdiff_t                       difference_type;
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

                self_type& operator++() {
                    ++m_super_it;
                    return *this;
                }
                self_type operator++(int) {
                    self_type temp(*this);
                    ++m_super_it;
                    return temp;
                }

                reference operator*() const { return m_super_it->m_value; }
                pointer operator->() const { return &m_super_it->m_value; }

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
                typedef local_iterator                  self_type;
                typedef std::pair<const Key, Mapped>    value_type;
                typedef       value_type&               reference;
                typedef const value_type&               const_reference;
                typedef       value_type *              pointer;
                typedef const value_type *              const_pointer;
                typedef size_t                          size_type;
                typedef ptrdiff_t                       difference_type;
                typedef std::forward_iterator_tag       iterator_category;

                super_iterator          m_super_it;
                size_type               m_b_index;
                size_type               m_b_count;

                local_iterator() : m_super_it(), m_b_index(0), m_b_count(0) { }

                local_iterator(super_iterator si, size_type index, size_type count)
                    : m_super_it(si), m_b_index(index), m_b_count(count) { }

                reference _get_value() {
                    return m_super_it.m_node->get()->m_value;
                }
                const_reference _get_value() const {
                    return m_super_it.m_node->get()->m_value;
                }
                size_type& _get_hash_value() {
                    return m_super_it.m_node->get()->m_hash_value;
                }
                const size_type& _get_hash_value() const {
                    return m_super_it.m_node->get()->m_hash_value;
                }

                      reference operator*()       { return _get_value(); }
                const_reference operator*() const { return _get_value(); }
                      pointer operator->()        { return &_get_value(); }
                const_pointer operator->() const  { return &_get_value(); }

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
                typedef local_const_iterator            self_type;
                typedef std::pair<const Key, Mapped>    value_type;
                typedef const value_type&               reference;
                typedef const value_type *              pointer;
                typedef size_t                          size_type;
                typedef ptrdiff_t                       difference_type;

                super_const_iterator                    m_super_it;
                size_type                               m_b_index;
                size_type                               m_b_count;

                local_const_iterator() : m_super_it(), m_b_index(0), m_b_count(0) { }

                local_const_iterator(local_iterator it) : m_super_it(it.m_super_it),
                    m_b_index(it.m_b_index), m_b_count(it.m_b_count) { }

                local_const_iterator(super_const_iterator si, size_type index, size_type count)
                    : m_super_it(si), m_b_index(index), m_b_count(count) { }

                const_reference _get_key() const {
                    return m_super_it.m_node->get()->key;
                }
                const size_type& _get_hash_value() const {
                    return m_super_it.m_node->get()->hash_value;
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

            unordered_multimap() : m_element_count(0), m_max_load_factor(1) {
                _init_buckets(5);
            }

            unordered_multimap(size_type n, const hasher& hash_fn = hasher(),
                               const key_equal& ke = key_equal())
                : m_element_count(0), m_max_load_factor(1),
                  m_hasher(hash_fn), m_key_eq(ke)
            {
                _init_buckets(n);
            }

            template <typename InputIterator>
            unordered_multimap(InputIterator first, InputIterator last,
                               size_type n = 20,
                               const hasher& hash_fn = hasher(),
                               const key_equal& ke = key_equal())
                : m_element_count(0), m_max_load_factor(1),
                  m_hasher(hash_fn), m_key_eq(ke)
            {
                _init_buckets(n);
                insert(first, last);
            }

            unordered_multimap(const self_type& other)
                : m_element_count(0), m_max_load_factor(1)
            {
                _init_buckets(other.bucket_count());
                insert(other.begin(), other.end());
            }

            ~unordered_multimap() {
                clear();
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
                    super_iterator it = m_buckets[n].m_super_it;
                    const size_type hash_value = it->m_hash_value;
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
                    super_const_iterator it = m_buckets[n].m_super_it;
                    const size_type hash_value = it->m_hash_value;
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
            iterator emplace_hint(const_iterator it, ARG1 arg1) {
                return emplace(arg1).first;
            }
            template <typename ARG1, typename ARG2>
            iterator emplace_hint(const_iterator it, ARG1 arg1, ARG2 arg2) {
                return emplace(arg1, arg2).first;
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

            void max_load_factor(float ml) {
                m_max_load_factor = ml;
            }

            size_type max_size() {
                return (size_type(-1) - sizeof(*this)) / sizeof(node_type);
            }

            void rehash(size_type count) {
                assert(count);
                size_type proposal = size_type(size() / max_load_factor());
                ++proposal;
                if (count < proposal)
                    count = proposal;
                if (count == bucket_count())
                    return;
                _init_buckets(count);
                node_type *node = m_list.m_head.m_next;
                node_type *next;
                m_list.m_head.m_next = NULL;
                while (node) {
                    next = node->m_next;
                    _emplace_node_0(node->get()->m_value, node);
                    node = next;
                }
                assert(float(bucket_count()) > size() / max_load_factor());
                assert(bucket_count() >= count);
            }

            void reserve(size_type count) {
                size_type c = size_type(std::ceil(count / max_load_factor()));
                rehash(c);
            }

            void swap(self_type& other) {
                unboost::swap(m_element_count, other.m_element_count);
                unboost::swap(m_max_load_factor, other.m_max_load_factor);
                unboost::swap(m_hasher, other.m_hasher);
                unboost::swap(m_key_eq, other.m_key_eq);
                unboost::swap(m_list, other.m_list);
                unboost::swap(m_buckets, other.m_buckets);
            }

            iterator find(const Key& key) {
                const size_type i = bucket(key);
                super_iterator it = m_buckets[i].m_super_it, iend;
                while (it != iend) {
                    const size_type hash_value = it->m_hash_value;
                    if (hash_value % bucket_count() != i) {
                        return iend;
                    }
                    if (key_eq()(it->m_value.first, key)) {
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
                    if (key_eq()(it->m_value.first, key)) {
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
                const_iterator it = find(key);
                if (it == end())
                    return 0;

                size_type count = 0;
                super_const_iterator si = it.m_super_it, send;
                while (si != send) {
                    if (!key_eq()(si->m_value.first, key))
                        break;
                    ++si;
                    ++count;
                }
                return count;
            }

            iterator
            emplace() {
                node_type *node = m_list._create_node();
                const value_type& value = node->get()->m_value;
                return _emplace_value_node(value, node);
            }
            template <typename ARG1>
            iterator
            emplace(ARG1 arg1) {
                node_type *node = m_list._create_node(arg1);
                const value_type& value = node->get()->m_value;
                return _emplace_value_node(value, node);
            }
            template <typename ARG1, typename ARG2>
            iterator
            emplace(ARG1 arg1, ARG2 arg2) {
                node_type *node = m_list._create_node(arg1, arg2);
                const value_type& value = node->get()->m_value;
                return _emplace_value_node(value, node);
            }

            std::pair<iterator, iterator> equal_range(const Key& key) {
                iterator first = find(key);
                if (first == end())
                    return std::make_pair(first, first);

                super_iterator si = first.m_super_it, send;
                while (si != send) {
                    if (!key_eq()(si->m_value.first, key))
                        break;
                    ++si;
                }
                iterator last(si);
                return std::make_pair(first, last);
            }
            std::pair<const_iterator, const_iterator>
            equal_range(const Key& key) const {
                const_iterator first = find(key);
                if (first == end())
                    return std::make_pair(first, first);

                super_const_iterator si = first.m_super_it, send;
                while (si != send) {
                    if (!key_eq()(si->m_value.first, key))
                        break;
                    ++si;
                }
                const_iterator last(si);
                return std::make_pair(first, last);
            }

            iterator erase(const_iterator pos) {
                assert(pos != cend());
                const Key& key = pos.m_super_it->m_value.first;
                size_type i = bucket(key);
                super_const_iterator prev_it;
                if (key_eq()(key, m_buckets[i].m_super_it->m_value.first)) {
                    prev_it = m_list.cbefore_begin();
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
                size_type count = 0;
                std::pair<iterator, iterator> p = equal_range(key);
                while (p.first != end() && p.first != p.second) {
                    p.first = erase(p.first);
                    ++count;
                }
                return count;
            }
            iterator erase(const_iterator first, const_iterator last) {
                while (first != last) {
                    first = erase(first);
                }
                return iterator(const_cast<node_type *>(last.m_node));
            }

            iterator insert(const value_type& value) {
                return emplace(value);
            }
            iterator insert(const_iterator hint, const value_type& value) {
                return insert(value);
            }
            template <typename InputIterator>
            void insert(InputIterator first, InputIterator last) {
                while (first != last) {
                    insert(*first);
                    ++first;
                }
            }

            self_type& operator=(const self_type& other) {
                clear();
                m_max_load_factor = other.m_max_load_factor;
                m_hasher = other.m_hasher;
                m_key_eq = other.m_key_eq;
                insert(other.begin(), other.end());
                return *this;
            }

#ifdef UNBOOST_RV_REF
            unordered_multimap(UNBOOST_RV_REF(self_type) other) {
                m_element_count = UNBOOST_RV(other).m_element_count;
                m_max_load_factor = UNBOOST_RV(other).m_max_load_factor;
                m_hasher = UNBOOST_RV(other).m_hasher;
                m_key_eq = UNBOOST_RV(other).m_key_eq;
                m_list.swap(UNBOOST_RV(other).m_list);
                m_buckets.swap(UNBOOST_RV(other).m_buckets);
            }

            self_type& operator=(UNBOOST_RV_REF(self_type) other) {
                m_element_count = UNBOOST_RV(other).m_element_count;
                m_max_load_factor = UNBOOST_RV(other).m_max_load_factor;
                m_hasher = UNBOOST_RV(other).m_hasher;
                m_key_eq = UNBOOST_RV(other).m_key_eq;
                m_list.swap(UNBOOST_RV(other).m_list);
                m_buckets.swap(UNBOOST_RV(other).m_buckets);
                return *this;
            }

            // NOTE: we don't support the following two methods:
            //   iterator insert(const_iterator hint, UNBOOST_RV_REF(Key) key) { ... }
            //   std::pair<iterator, bool> insert(UNBOOST_RV_REF(Key) key) { ... }
#endif  // def UNBOOST_RV_REF

        protected:
            size_type                   m_element_count;
            float                       m_max_load_factor;
            Hash                        m_hasher;
            KeyEq                    m_key_eq;
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
                    const Key& key = bucket_it->m_value.first;
                    const size_type hash_value = hash_function()(key);
                    const size_type count = bucket_count();
                    ++(m_buckets[i].m_super_it);
                    m_buckets[i]._fix(hash_value % count, count);
                }
            }

            iterator
            _emplace_node_0(const value_type& value, node_type *node) {
                const size_type i = node->get()->m_hash_value % bucket_count();
                if (_is_bucket_empty(i)) {
                    m_list._add_node_after(m_list.before_begin(), node);
                    m_buckets[i].m_super_it = node;
                } else {
                    super_iterator prev_sit = m_buckets[i].m_super_it;
                    super_iterator sit = prev_sit, send;
                    ++sit;
                    while (sit != send) {
                        if ((sit->m_hash_value % bucket_count()) != i)
                            break;
                        if (key_eq()(value.first, prev_sit->m_value.first))
                            break;
                        ++sit;
                        ++prev_sit;
                    }
                    m_list._add_node_after(prev_sit, node);
                }
                ++(m_buckets[i].m_count);
                ++m_element_count;
                return node;
            }

            iterator
            _emplace_value_node(const value_type& value, node_type *node) {
                node->get()->m_hash_value = hash_function()(value.first);
                iterator ret = _emplace_node_0(value, node);
                _rehash_if_case();
                return ret;
            }
        }; // unordered_map<Key, Mapped, Hash, KeyEq>

        template <typename Key, typename Mapped, typename Hash, typename KeyEq>
        inline void
        swap(unordered_multimap<Key, Mapped, Hash, KeyEq>& lhs,
             unordered_multimap<Key, Mapped, Hash, KeyEq>& rhs)
        {
            lhs.swap(rhs);
        }

        template <typename Key, typename Mapped, typename Hash, typename KeyEq>
        inline bool operator==(
            const unordered_multimap<Key, Mapped, Hash, KeyEq>& lhs,
            const unordered_multimap<Key, Mapped, Hash, KeyEq>& rhs)
        {
            typedef typename
                unordered_multimap<Key, Mapped, Hash, KeyEq>::const_iterator const_iterator;
            if (&lhs == &rhs)
                return true;
            if (lhs.size() != rhs.size())
                return false;
            const_iterator lhs_eq1 = lhs.begin(), lhs_end = lhs.end();
            while (lhs_eq1 != lhs_end) {
                std::pair<const_iterator, const_iterator> lhs_range, rhs_range;
                lhs_range = lhs.equal_range(lhs_eq1->m_value.first);
                const_iterator lhs_eq1 = lhs_range.first;
                const_iterator lhs_eq2 = lhs_range.second;
                rhs_range = rhs.equal_range(lhs_eq1->m_value.first);
                const_iterator rhs_eq1 = rhs_range.first;
                const_iterator rhs_eq2 = rhs_range.second;
                if (std::distance(lhs_eq1, lhs_eq2) != std::distance(rhs_eq1, rhs_eq2))
                    return false;
                if (!std::is_permutation(lhs_eq1, lhs_eq2, rhs_eq1))
                    return false;
                lhs_eq1 = lhs_range.second;
            }
            return true;
        }
        template <typename Key, typename Mapped, typename Hash, typename KeyEq>
        inline bool operator!=(
            const unordered_multimap<Key, Mapped, Hash, KeyEq>& lhs,
            const unordered_multimap<Key, Mapped, Hash, KeyEq>& rhs)
        {
            return !(lhs == rhs);
        }
    } // namespace unboost
#else
    #error Your compiler is not supported yet. You lose.
#endif

#endif  // ndef UNBOOST_UNORDERED_MAP_HPP_
