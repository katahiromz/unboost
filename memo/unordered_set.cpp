#include <vector>   // for std::vector
#include <limits>   // for std::numeric_limits

template <typename Key,
          class Hash = hash<Key>,
          class KeyEqual = std::equal_to<Key> >
class unordered_set {
public:
    typedef Key                 key_type;
    typedef Key                 value_type;
    typedef size_t              size_type;
    typedef ptrdiff_t           difference_type;
    typedef Hash                hasher;
    typedef KeyEqual            key_equal;
    typedef value_type&         reference;
    typedef const value_type&   const_reference;
    typedef value_type *        pointer;
    typedef const value_type *  const_pointer;

    struct bucket_type : public std::vector<pointer> {
        bucket_type() { }
        ~bucket_type() {
            size_t count = size();
            for (size_t i = 0; i < count; ++i) {
                pointer ptr = at(i);
                if (ptr != NULL)
                    delete ptr;
            }
        }
    };

    typedef std::vector<bucket_type>            bucket_list;
    typedef bucket_type::iterator               local_iterator;
    typedef bucket_type::const_iterator   const_local_iterator;
    typedef std::pair<bucket_list::iterator, local_iterator>  iterator;
    typedef std::pair<bucket_list::const_iterator, const_local_iterator>  const_iterator;

    typedef unordered_set<Key, Hash, KeyEqual> self_type;

    unordered_set() {
        m_item_count = 0;
        m_bucket_count = 0;
        m_hasher = Hash()
        m_key_eq = KeyEqual();
        m_max_load_factor = 0;
        ...
    }

    explicit unordered_set(size_type bucket_count,
                           const Hash& hash = Hash(),
                           const KeyEqual& equal = KeyEqual())
    {
        m_item_count = 0;
        m_bucket_count = bucket_count;
        m_hasher = hash;
        m_key_eq = equal;
        m_max_load_factor = 0;
        ...
    }
    template <class InputIt>
    unordered_set(InputIt first, InputIt last,
                  size_type bucket_count = ...,
                  const Hash& hash = Hash(),
                  const KeyEqual& equal = KeyEqual())
    {
        m_item_count = 0;
        m_bucket_count = bucket_count;
        m_hasher = hash;
        m_key_eq = equal;
        m_max_load_factor = 0;
        while (first != last) {
            insert(*first);
            ++first;
        }
    }
    unordered_set(const self_type& other) {
        m_item_count = 0;
        m_bucket_count = 0;
        m_hasher = other.m_hasher;
        m_key_eq = other.m_key_eq;
        m_max_load_factor = other.m_max_load_factor;
        insert(other.begin(), other.end());
    }
    unordered_set(self_type&& other) {
        m_item_count = 0;
        m_bucket_count = 0;
        m_hasher = other.m_hasher;
        m_key_eq = other.m_key_eq;
        m_max_load_factor = other.m_max_load_factor;
        m_buckets = std::move(other.m_buckets);
    }

    ~unordered_set() { }

    self_type& operator=(const self_type& other) {
        m_item_count = other.m_item_count;
        m_bucket_count = other.m_bucket_count;
        m_hasher = other.m_hasher;
        m_key_eq = other.m_key_eq;
        m_max_load_factor = other.m_max_load_factor;
        m_buckets = other.m_buckets;
        return *this;
    }
    self_type& operator=(self_type&& other) {
        m_item_count = other.m_item_count;
        m_bucket_count = other.m_bucket_count;
        m_hasher = other.m_hasher;
        m_key_eq = other.m_key_eq;
        m_max_load_factor = other.m_max_load_factor;
        m_buckets = std::move(other.m_buckets);
        return *this;
    }

    iterator begin() {
        ...
    }
    const_iterator  begin() const { return cbegin(); }
    const_iterator cbegin() const {
        ...
    }

    iterator end() {
        ...
    }
    const_iterator  end() const { return cend(); }
    const_iterator cend() const {
        ...
    }

    bool empty() const      { return size() == 0; }
    size_type size() const  { return m_item_count; }

    size_type max_size() const {
        return std::numeric_limits<size_type>::max() / sizeof(value_type);
    }

    void clear() {
        m_buckets.clear();
        m_bucket_count = 0;
        ...
    }

    std::pair<iterator, bool> insert(const value_type& value) {
        ...
    }
    std::pair<iterator, bool> insert(value_type&& value) {
        ...
    }
    iterator insert(const_iterator hint, const value_type& value) {
        return insert(value).first;
    }
    iterator insert(const_iterator hint, value_type&& value) {
        return insert(value).first;
    }
    template <class InputIt>
    void insert(InputIt first, InputIt last) {
        while (first != last) {
            insert(*first);
            ++first;
        }
    }

    std::pair<iterator, bool> emplace() {
        ...
    }
    template <typename ARG1>
    std::pair<iterator, bool> emplace(const ARG1& arg1) {
        ...
    }
    template <typename ARG1, typename ARG2>
    std::pair<iterator, bool> emplace(const ARG1& arg1, const ARG2& arg2) {
        ...
    }
    template <typename ARG1, typename ARG2, typename ARG3>
    std::pair<iterator, bool> emplace(const ARG1& arg1, const ARG2& arg2, const ARG3& arg3) {
        ...
    }
    template <typename ARG1, typename ARG2, typename ARG3, typename ARG4>
    std::pair<iterator, bool> emplace(const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4) {
        ...
    }
    template <typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
    std::pair<iterator, bool> emplace(const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4, const ARG5& arg5) {
        ...
    }

    iterator emplace_hint(const_iterator hint) {
        emplace();
    }
    template <typename ARG1>
    iterator emplace_hint(const_iterator hint, const ARG1& arg1) {
        emplace(arg1);
    }
    template <typename ARG1, typename ARG2>
    iterator emplace_hint(const_iterator hint, const ARG1& arg1, const ARG2& arg2) {
        emplace(arg1, arg2);
    }
    template <typename ARG1, typename ARG2, typename ARG3>
    iterator emplace_hint(const_iterator hint, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3) {
        emplace(arg1, arg2, arg3);
    }
    template <typename ARG1, typename ARG2, typename ARG3, typename ARG4>
    iterator emplace_hint(const_iterator hint, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4) {
        emplace(arg1, arg2, arg3, arg4);
    }
    template <typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
    iterator emplace_hint(const_iterator hint, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4, const ARG5& arg5) {
        emplace(arg1, arg2, arg3, arg4, arg5);
    }

    iterator erase(const_iterator pos) {
        ...
    }
    iterator erase(const_iterator first, const_iterator last) {
        while (first != last) {
            erase(first);
            ++first;
        }
        return first;
    }
    size_type erase(const Key& key) {
        iterator it = find(key);
        if (it != end()) {
            erase(it);
            return 1;
        }
        return 0;
    }

    void swap(self_type& other) {
        swap(m_item_count, other.m_item_count);
        swap(m_bucket_count, other.m_bucket_count);
        swap(m_hasher, other.m_hasher);
        swap(m_key_eq, other.m_key_eq);
        swap(m_max_load_factor, other.m_max_load_factor);
        swap(m_buckets, other.m_buckets);
    }

    size_type count(const Key& key) const {
        size_type number = 0, iBucket = bucket(key);
        const_local_iterator it = cbegin(iBucket), end = cend(iBucket);
        for (; it != end; ++it) {
            if (*it == key) {
                ++number;
            }
        }
        return number;
    }
    iterator find(const Key& key) {
        ...
    }
    const_iterator find(const Key& key) const {
        ...
    }
    std::pair<iterator, iterator> equal_range(const Key& key) {
        iterator it = find(key);
        return std::make_pair<iterator, iterator>(it, it);
    }
    std::pair<const_iterator, const_iterator> equal_range(const Key& key) const {
        const_iterator it = find(key);
        return std::make_pair<const_iterator, const_iterator>(it, it);
    }

    local_iterator begin(size_type n) {
        ...
    }
    const_local_iterator  begin(size_type n) const { return cbegin(n); }
    const_local_iterator cbegin(size_type n) const {
        ...
    }

    local_iterator end(size_type n) {
        ...
    }
    const_local_iterator  end(size_type n) const { return cend(n); }
    const_local_iterator cend(size_type n) const {
        ...
    }

    size_type bucket_count() const {
        return m_bucket_count;
    }
    size_type max_bucket_count() const {
        return std::numeric_limits<size_type>() / sizeof(bucket_type);
    }
    size_type bucket_size(size_type n) const {
        return m_buckets[n].size();
    }
    size_type bucket(const Key& key) const {
        assert(bucket_count() > 0);
        ...
    }

    float load_factor() const {
        return float(size()) / bucket_count();
    }
    float max_load_factor() const {
        return m_max_load_factor;
    }
    void max_load_factor(float ml) {
        m_max_load_factor = ml;
    }
    void rehash(size_type n) {
        ...
        assert(bucket_count() * max_load_factor() >= size() && bucket_count() >= n);
    }
    void reserve(size_type n) {
        ...
        assert(bucket_count() * max_load_factor() > size() && bucket_count() >= ceil(n / max_load_factor()));
    }

    hasher hash_function() const    { return m_hasher; }
    key_equal key_eq() const        { return m_key_eq; }

protected:
    size_type                   m_item_count;
    size_type                   m_bucket_count;
    hasher                      m_hasher;
    key_equal                   m_key_eq;
    float                       m_max_load_factor;
    std::vector<bucket_type>    m_buckets;
};

template <typename Key, typename Hash, class KeyEqual>
inline void
operator==(const unordered_set<Key, Hash, KeyEqual>& lhs,
           const unordered_set<Key, Hash, KeyEqual>& rhs)
{
    if (lhs.size() != rhs.size())
        return false;

    unordered_set<Key, Hash, KeyEqual>::const_iterator it, end = lhs.end();
    for (it = lhs.begin(); it != end; ++it) {
        if (rhs.count(*it) == 0)
            return false;
    }
    return true;
}
template <typename Key, typename Hash, class KeyEqual>
inline void
operator!=(const unordered_set<Key, Hash, KeyEqual>& lhs,
           const unordered_set<Key, Hash, KeyEqual>& rhs)
{
    return !(lhs == rhs);
}

template <typename Key, typename Hash, class KeyEqual>
inline void
swap(unordered_set<Key, Hash, KeyEqual>& lhs,
     unordered_set<Key, Hash, KeyEqual>& rhs)
{
    lhs.swap(rhs);
}
