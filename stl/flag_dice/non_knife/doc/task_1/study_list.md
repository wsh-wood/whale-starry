### 类结构
```C++
template<typename _Tp, typename _Alloc = std::allocator<_Tp> >
    class list : protected _List_base<_Tp, _Alloc>
    {

    }
```
`list` 继承 `_List_base`

### 构造函数
```C++
//不带任何元素的list
explicit
list(const allocator_type& __a) _GLIBCXX_NOEXCEPT
: _Base(_Node_alloc_type(__a)) { }

//带n个元素且赋值的list
explicit
list(size_type __n, const value_type& __value = value_type(),
const allocator_type& __a = allocator_type())
: _Base(_Node_alloc_type(__a))
{ _M_fill_initialize(__n, __value); }

//从一个范围内初始化list
template<typename _InputIterator>
list(_InputIterator __first, _InputIterator __last,
    const allocator_type& __a = allocator_type())
: _Base(_Node_alloc_type(__a))
{
// Check whether it's an integral type.  If so, it's not an iterator.
typedef typename std::__is_integer<_InputIterator>::__type _Integral;
_M_initialize_dispatch(__first, __last, _Integral());
}

```

### 操作符重载
```C++
template<typename _Tp, typename _Alloc>
inline bool
operator==(const list<_Tp, _Alloc>& __x, const list<_Tp, _Alloc>& __y)
{
#if _GLIBCXX_USE_CXX11_ABI
    if (__x.size() != __y.size())
return false;
#endif

    typedef typename list<_Tp, _Alloc>::const_iterator const_iterator;
    const_iterator __end1 = __x.end();
    const_iterator __end2 = __y.end();

    const_iterator __i1 = __x.begin();
    const_iterator __i2 = __y.begin();
    while (__i1 != __end1 && __i2 != __end2 && *__i1 == *__i2)
{
    ++__i1;
    ++__i2;
}
    return __i1 == __end1 && __i2 == __end2;
}
```
>实现思路是，迭代判断两个迭代器是否都抵达末尾。



### list的iterator定义
```C++
template<typename _Tp>
struct _List_iterator
{
    typedef _List_iterator<_Tp>		_Self;
    typedef _List_node<_Tp>			_Node;

    typedef ptrdiff_t				difference_type;
    typedef std::bidirectional_iterator_tag	iterator_category;
    typedef _Tp				value_type;
    typedef _Tp*				pointer;
    typedef _Tp&				reference;

    _List_iterator() _GLIBCXX_NOEXCEPT
    : _M_node() { }

    explicit
    _List_iterator(__detail::_List_node_base* __x) _GLIBCXX_NOEXCEPT
    : _M_node(__x) { }

    _Self
    _M_const_cast() const _GLIBCXX_NOEXCEPT
    { return *this; }

    // Must downcast from _List_node_base to _List_node to get to value.
    reference
    operator*() const _GLIBCXX_NOEXCEPT
    { return *static_cast<_Node*>(_M_node)->_M_valptr(); }

    pointer
    operator->() const _GLIBCXX_NOEXCEPT
    { return static_cast<_Node*>(_M_node)->_M_valptr(); }

    _Self&
    operator++() _GLIBCXX_NOEXCEPT
    {
_M_node = _M_node->_M_next;
return *this;
    }

    _Self
    operator++(int) _GLIBCXX_NOEXCEPT
    {
_Self __tmp = *this;
_M_node = _M_node->_M_next;
return __tmp;
    }

    _Self&
    operator--() _GLIBCXX_NOEXCEPT
    {
_M_node = _M_node->_M_prev;
return *this;
    }

    _Self
    operator--(int) _GLIBCXX_NOEXCEPT
    {
_Self __tmp = *this;
_M_node = _M_node->_M_prev;
return __tmp;
    }

    friend bool
    operator==(const _Self& __x, const _Self& __y) _GLIBCXX_NOEXCEPT
    { return __x._M_node == __y._M_node; }

    friend bool
    operator!=(const _Self& __x, const _Self& __y) _GLIBCXX_NOEXCEPT
    { return __x._M_node != __y._M_node; }

    // The only member points to the %list element.
    __detail::_List_node_base* _M_node;
};
```