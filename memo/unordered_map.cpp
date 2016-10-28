#include "hash.hpp"
#include "functional.hpp"
#include <utility>          // for std::pair

template <typename Key, typename T,
          class Hash = unboost::hash<Key>,
          class KeyEqual = std::equal_to<Key> >
class unordered_map {
public:
    typedef Key key_type;
    typedef T mapped_type;
    typedef std::pair<const Key, T> value_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef Hash hasher;
    typedef KeyEqual key_equal;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    // FIXME: pointer, const_pointer, iterator, const_iterator
    // FIXME: local_iterator, const_local_iterator
    typedef unordered_map<Key, T, Hash, KeyEqual> self_type;

    explicit unordered_map(
        size_type bucket_count,
        const Hash& hash = Hash(),
        const KeyEqual& equal = KeyEqual());

    template <typename InputIt>
    unordered_map(InputIt first, InputIt last, 
        size_type bucket_count,
        const Hash& hash = Hash(),
        const KeyEqual& equal = KeyEqual());

    unordered_map(const self_type& other);
    //unordered_map(self_type&& other);

    ~unordered_map() { }

    self_type& operator=(const self_type& other);
    //self_type& operator=(self_type&& other);

          iterator  begin();
    const_iterator  begin() const;
    const_iterator cbegin() const;
          iterator  end();
    const_iterator  end() const;
    const_iterator cend() const;

    bool empty() const;
    size_type size() const;
    size_type max_size() const;

    void clear();
    std::pair<iterator, bool> insert(const value_type& value);

    template <typename P>
    std::pair<iterator, bool> insert(value_type&& value);
    iterator insert(const_iterator hint, const value_type& value);
    template <typename P>
    iterator insert(const_iterator hint, P&& value);
    template <class InputIt>
    void insert(InputIt first, InputItlast);

    std::pair<iterator, bool> emplace();
    template <typename ARG1>
    std::pair<iterator, bool> emplace(const ARG1& arg1);
    template <typename ARG1, typename ARG2>
    std::pair<iterator, bool> emplace(const ARG1& arg1, const ARG2& arg2);
    template <typename ARG1, typename ARG2, typename ARG3>
    std::pair<iterator, bool> emplace(const ARG1& arg1, const ARG2& arg2, const ARG3& arg3);
    template <typename ARG1, typename ARG2, typename ARG3, typename ARG4>
    std::pair<iterator, bool> emplace(const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4);
    template <typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
    std::pair<iterator, bool> emplace(const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4, const ARG5& arg5);

    iterator emplace_hint(const_iterator hint);
    template <typename ARG1>
    iterator emplace_hint(const_iterator hint, const ARG1& arg1);
    template <typename ARG1, typename ARG2>
    iterator emplace_hint(const_iterator hint, const ARG1& arg1, const ARG2& arg2);
    template <typename ARG1, typename ARG2, typename ARG3>
    iterator emplace_hint(const_iterator hint, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3);
    template <typename ARG1, typename ARG2, typename ARG3, typename ARG4>
    iterator emplace_hint(const_iterator hint, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4);
    template <typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
    iterator emplace_hint(const_iterator hint, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4, const ARG5& arg5);

    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);
    size_type erase(const key_type& key);

    void swap(self_type& other);

          T& at(const Key& key);
    const T& at(const Key& key) const;
          T& operator[](const Key& key);
    const T& operator[](const Key& key) const;

    size_type count(const Key& key) const;

          iterator find(const Key& key);
    const_iterator find(const Key& key) const;

    std::pair<      iterator,       iterator> equal_range(const Key& key);
    std::pair<const_iterator, const_iterator> equal_range(const Key& key) const;

          local_iterator  begin(size_type n);
    const_local_iterator  begin(size_type n) const;
    const_local_iterator cbegin(size_type n) const;
          local_iterator  end(size_type n);
    const_local_iterator  end(size_type n) const;
    const_local_iterator cend(size_type n) const;

    size_type bucket_count() const;
    size_type max_bucket_count() const;
    size_type bucket_size(size_type n) const;
    size_type bucket(const Key& key) const;

    float load_factor() const;
    float max_load_factor() const;
    void max_load_factor(float ml);
    void rehash(size_type count);
    void reserve(size_type count);

    hasher hash_function() const;
    key_equal key_eq() const;

protected:
};

template <typename Key, typename T, class Hash, class KeyEqual>
inline void
operator==(const unordered_map<Key, T, Hash, KeyEqual>& lhs, 
           const unordered_map<Key, T, Hash, KeyEqual>& rhs)
{
}

template <typename Key, typename T, class Hash, class KeyEqual>
inline void
operator!=(const unordered_map<Key, T, Hash, KeyEqual>& lhs, 
           const unordered_map<Key, T, Hash, KeyEqual>& rhs)
{
}

template <typename Key, typename T, class Hash, class KeyEqual>
inline void
swap(unordered_map<Key, T, Hash, KeyEqual>& lhs,
     unordered_map<Key, T, Hash, KeyEqual>& rhs)
{
    lhs.swap(rhs);
}
