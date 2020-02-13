/*
 * 	Author: Manthan B Y
 * 	Language: C++
 *  Date: 11-02-2020
 *  Last Modified: 12-02-2020
 * 	Problem Statement: Custom Generic MyVector Class
*/
#include <iostream>
#include <cstdarg>
#include <cstring>
using namespace std;
using ll = long long;

/*
    operator<< overloaded so: cout << v; will print the vector elements
*/
template <typename DT>
class GenericMyVector
{
private:
    DT *arr;
    ll cap;    // current capacity of the vector
    ll length; // current length of the vector
public:
    explicit GenericMyVector(ll = 100);     // by deafult capacity is 100, or else argument can be passed to use your own
    GenericMyVector(const std::initializer_list<DT>& l);    // cosntructor for initializer list
    ll push_back(const DT &data);           // returns the size of the array after pushing the data
    auto pop_back();                        // returns the popped element
    ll push_front(const DT &data);          // returns the size of array after pushing the data
    auto pop_front();                       // returns the popped element
    auto insert(ll pos, DT val);            // returns an iterator pointing to the current inserted element
    ll push_back_more(int num, ...);        // pushes 'num' # of followed argumments to vector returns the length after insertion
    const DT &front() const;                // returns the reference of first element
    const DT &back() const;                 // returns the reference of last element
    const DT &at(ll pos) const;             // returns the element at specified pos
    ll size() const;                        // returns the size of the array
    ll capacity() const;                    // returns the size of the storage space currently allocated to vector as number of elements
    ll capacity_bytes() const;              // returns the size of the storage space currently allocated to vector as number of elements in bytes
    bool empty() const;                     // check if the array is empty
    DT &operator[](ll index) const;         // overloading array reference(index) operator
    DT *data() const;                       // returns the direct pointer to the array
    void reserve(ll new_cap);               // increase the capacity of vector
    void resize(ll count, const DT &value); // resize the vector to count, set other values to value
    void shrink_to_fit();                   // shrinks the capacity of the vector to fit the current size
    GenericMyVector(const GenericMyVector<DT> &) = delete;
    template <typename F> // freind function should also have typename ( not the same ) Ref: https://en.cppreference.com/w/cpp/language/friend
    friend ostream &operator<<(ostream &output, const GenericMyVector<F> &v);   // for using vector with cout
    class iterator
    {
    private:
        DT *ptr;

    public:
        explicit iterator() : ptr(nullptr) {}
        explicit iterator(DT *p) : ptr(p) {}
        bool operator==(const iterator &rhs) const
        {
            return ptr == rhs.ptr;
        }
        bool operator!=(const iterator &rhs) const
        {
            return !(*this == rhs);
        }
        DT operator*() const
        {
            return *ptr;
        }
        iterator &operator++() // pre inc
        {
            ++ptr;
            return *this;
        }
        iterator operator++(int) // post inc
        {
            iterator temp(*this);
            ++*this;
            return temp;
        }
        iterator &operator--() // pre dec
        {
            --ptr;
            return *this;
        }
        iterator operator--(int) // post dec
        {
            iterator temp(*this);
            --*this;
            return temp;
        }
    };
    iterator begin() const;
    iterator end() const;
};
template <typename DT>
GenericMyVector<DT>::GenericMyVector(ll n) : cap(n), arr(new DT[n]), length(0) {}

template <typename DT>
GenericMyVector<DT>::GenericMyVector(const std::initializer_list<DT>& l): arr(new DT[100]), length(l.size())
{
    copy(l.begin(), l.end(), arr);
}

template <typename DT>
ll GenericMyVector<DT>::push_back(const DT &data)
{
    if (length == cap)
    {
        DT *old = arr;
        arr = new DT[cap = cap * 2];
        copy(old, old + length, arr);
        delete[] old;
    }
    arr[length++] = data;
    return length;
}

template <typename DT>
auto GenericMyVector<DT>::pop_back()
{
    if (empty())
    {
        cout << "\n--- Error: Trying to pop_back from empty array --------\n";
        exit(0);
    }
    return arr[length-- - 1];
}

template <typename DT>
ll GenericMyVector<DT>::push_front(const DT &data)
{
    if (length == cap)
    {
        DT *old = arr;
        arr = new DT[cap = cap * 2];
        copy(old, old + length, arr);
        delete[] old;
    }
    copy(arr, arr + length, arr + 1);
    arr[0] = data;
    return ++length;
}

template <typename DT>
auto GenericMyVector<DT>::pop_front()
{
    if (empty())
    {
        cout << "\n--- Error: Trying to pop_front from empty array --------\n";
        exit(0);
    }
    DT temp = arr[0]; // to return the popped element
    copy(arr + 1, arr + length, arr);
    --length;
    return temp;
}

template <typename DT>
auto GenericMyVector<DT>::insert(ll pos, DT val)
{
    if (length == cap)
    {
        DT *old = arr;
        arr = new DT[cap = cap * 2];
        copy(old, old + length, arr);
        delete[] old;
    }
    copy(arr + pos, arr + length, arr + pos + 1);
    arr[pos] = val;
    return iterator(arr + pos);
}

template <typename DT>
ll GenericMyVector<DT>::push_back_more(int num, ...)
{                      // var # of args, Ref: https://www.cprogramming.com/tutorial/lesson17.html
    va_list arguments; // A place to store the list of arguments

    va_start(arguments, num);     // Initializing arguments to store all values after num
    for (int x = 0; x < num; x++) // Loop until all numbers are added
        push_back(va_arg(arguments, DT));
    va_end(arguments); // Cleans up the list

    return length;
}

template <typename DT>
const DT &GenericMyVector<DT>::front() const
{
    if (empty())
    {
        cout << "\n--- Error: Trying to look front in empty array --------\n";
        exit(0);
    }
    return *(arr + 0);
}

template <typename DT>
const DT &GenericMyVector<DT>::back() const
{
    if (empty())
    {
        cout << "\n--- Error: Trying to look back in empty array --------\n";
        exit(0);
    }
    return *(arr + length - 1);
}

template <typename DT>
const DT &GenericMyVector<DT>::at(ll pos) const
{
    if (pos >= length || pos < 0)
    {
        cout << "\n--- Error: Array index out of bound --------\n";
        exit(0);
    }
    return *(arr + pos); // or return arr[pos]
}

template <typename DT>
ll GenericMyVector<DT>::size() const
{
    return length;
}

template <typename DT>
ll GenericMyVector<DT>::capacity() const
{
    return cap;
}

template <typename DT>
ll GenericMyVector<DT>::capacity_bytes() const
{
    return cap * sizeof(DT);
}

template <typename DT>
bool GenericMyVector<DT>::empty() const
{
    return !(length);
}

template <typename DT>
DT &GenericMyVector<DT>::operator[](ll index) const
{
    if (index >= length || index < 0)
    {
        cout << "\n--- Error: Array index out of bound --------\n";
        exit(0);
    }
    return *(arr + index); // or return arr[index]
}

template <typename DT>
DT *GenericMyVector<DT>::data() const
{
    return arr;
}

template <typename DT>
void GenericMyVector<DT>::reserve(ll new_cap)
{
    if (cap >= new_cap)
        return;
    DT *old = arr;
    arr = new DT[cap = new_cap];
    copy(old, old + length, arr);
    delete[] old;
}

template <typename DT>
void GenericMyVector<DT>::resize(ll count, const DT &value)
{
    if (cap < count)
    {
        DT *old = arr;
        arr = new DT[cap = count * 2]; // increase the capacity by double the required
        copy(old, old + length, arr);
        delete[] old;
    }
    for (ll i = count; i < length; i++)
        memset(arr + i, 0, sizeof(DT)); // destroy all the further elements
    for (ll i = length; i < count; i++)
        arr[i] = value; // set the values if count > current length
    length = count;
}

template <typename DT>
void GenericMyVector<DT>::shrink_to_fit()
{
    if (cap == length)
        return; // if fn called multiple times, reallocation is waste
    DT *old = arr;
    arr = new DT[cap = length]; // set new capacity to the current length
    copy(old, old + length, arr);
    delete[] old;
}

template <typename DT>
typename GenericMyVector<DT>::iterator GenericMyVector<DT>::begin() const
{
    return iterator(arr);
}

template <typename DT>
typename GenericMyVector<DT>::iterator GenericMyVector<DT>::end() const
{
    return iterator(arr + length);
}

template <typename V>
void display_vector(V &v)
{
    typename V::iterator ptr; // dependent types: compiler must be able to deduce the type during compilation
    for (ptr = v.begin(); ptr != v.end(); ptr++)
    {
        cout << *ptr << ' ';
    }
    cout << '\n';
}

template <typename F>
ostream &operator<<(ostream &output, const GenericMyVector<F> &v)
{
    for (ll i = 0; i < v.size(); i++)
        output << v[i] << " "; // the function here(operator[]) should be constant () const, during << overloading
                               // as the compiler can't guarentee the function does not change the state of object
    cout << '\n';
    return output;
}

int main()
{
    cout << "---- int ----" << '\n';
    GenericMyVector<int> v;
    v.push_back(5);
    v.push_back(6);
    v.push_back(7);
    v.push_back(8);
    v.push_back(9);
    v.push_front(10);
    v.push_front(11);
    v.push_front(12);
    v.insert(1, 50);
    v.insert(1, 60);
    GenericMyVector<int>::iterator it;
    cout << "Print using iterator: ";
    for (it = v.begin(); it != v.end(); it++)
        cout << *it << " ";
    cout << endl;
    cout << "Print using generic function: ";
    display_vector(v);
    cout << "size: " << v.size() << '\n';
    // cout << "out of bound: " << v[v.size()] << '\n';
    cout << "v[2]: " << v[2] << '\n';
    cout << "pop_back: " << v.pop_back() << '\n';
    cout << "pop_front: " << v.pop_front() << '\n';
    cout << "After pop: ";
    display_vector(v);
    cout << "Print using foreach: ";
    for (auto i : v)
        cout << i << " ";
    cout << endl;
    // v.front() = 21;  // can't be done because front() returns const reference
    cout << "Front: " << v.front() << endl;
    cout << "Back: " << v.back() << endl;
    cout << "Capacity: " << v.capacity() << endl;
    cout << "Capacity(bytes): " << v.capacity_bytes() << endl;
    display_vector(v);
    cout << "First element(using data): " << *v.data() << endl;
    cout << "Second element(using data): " << *(v.data() + 2) << endl;
    // GenericMyVector<int> k(v);   // copy constructor deleted as aliasing problem may occur
    // reserving 1000 elements
    v.reserve(1000);
    cout << "Capacity after reserving: " << v.capacity() << endl;
    cout << "Print Vector(<<): ";
    cout << v;
    v.resize(9, 33);
    cout << v;
    cout << "Capacity(before shrink to fit): " << v.capacity() << endl;
    v.shrink_to_fit();
    cout << "Capacity(after shrink to fit): " << v.capacity() << endl;
    v.push_back(8);
    cout << v;
    cout << "Capacity: " << v.capacity() << endl; // observe how the capacity increases
    v.push_back_more(5, 12, 13, 14, 15, 16);
    cout << v;
    GenericMyVector<int> vv{1, 2, 3, 4, 5, 6};  // or vv = {1, 2, 3, 4, 5, 6}
    cout << "vv: " << vv;
    cout << "\n------ char ------\n";
    GenericMyVector<char> c;
    c.push_back('a');
    c.push_back('b');
    c.push_back('c');
    c.push_back('d');
    c.push_back('e');
    c.push_front('f');
    c.push_front('g');
    c.push_front('h');
    GenericMyVector<char>::iterator it1;
    cout << "Print using iterator: ";
    for (it1 = c.begin(); it1 != c.end(); it1++)
        cout << *it1 << " "; // this can also be done to print elements
    cout << endl;
    cout << "Print using generic function: ";
    display_vector(c);
    cout << "size: " << c.size() << '\n';
    // cout << "out of bound: " << v[v.size()] << '\n'; // uncomment to check out of bound
    cout << "c[2]: " << c[2] << '\n';
    cout << "pop_back: " << c.pop_back() << '\n';
    cout << "pop_front: " << c.pop_front() << '\n';
    cout << "After pop: ";
    display_vector(c);
    cout << "Print using index: ";
    for (int i = 0; i < c.size(); i++)
        cout << c[i] << " ";
    cout << '\n';
    cout << "Capacity: " << c.capacity() << endl;
    cout << "Capacity(bytes): " << c.capacity_bytes() << endl;
    while (!c.empty())
        cout << c.pop_back() << " ";
    cout << boolalpha;
    cout << endl;
    cout << c.empty();
    // getchar();
    return 0;
}