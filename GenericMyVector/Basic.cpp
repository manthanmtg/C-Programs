/*
 * 	Author: Manthan B Y
 * 	Language: C++
 *  Date: 11-02-2020
 *  Last Modified: 12-02-2020
 * 	Problem Statement: Custom Generic MyVector Class
*/
#include <iostream>
using namespace std;
using ll = long long;
template <typename DT>
class GenericMyVector
{
private:
    DT *arr;
    ll capacity; // current capacity of the vector
    ll length;   // current length of the vector

public:
    explicit GenericMyVector(ll = 100);
    ll push_back(DT); // returns the number of elements in array after pushing the data
    DT pop_back();    // returns the popped element :)
    ll size() const;
    DT &operator[](ll);
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
        iterator &operator++() // pre
        {
            ++ptr;
            return *this;
        }
        iterator operator++(int) // post
        {
            iterator temp(*this);
            ++*this;
            return temp;
        }
    };
    iterator begin() const;
    iterator end() const;
};
template <typename DT>
GenericMyVector<DT>::GenericMyVector(ll n) : capacity(n), arr(new DT[n]), length(0) {}

template <typename DT>
ll GenericMyVector<DT>::push_back(DT data)
{
    if (length == capacity)
    {
        DT *old = arr;
        arr = new DT[capacity = capacity * 2];
        copy(old, old + length, arr);
        delete[] old;
    }
    arr[length++] = data;
    return length;
}

template <typename DT>
DT GenericMyVector<DT>::pop_back()
{
    return arr[length-- - 1];
}

template <typename DT>
ll GenericMyVector<DT>::size() const
{
    return length;
}

template <typename DT>
DT &GenericMyVector<DT>::operator[](ll index)
{
    if (index >= length)
    {
        cout << "\n--- Error: Array index out of bound --------\n";
        exit(0);
    }
    return *(arr + index); // or return arr[index]
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
    typename V::iterator ptr; // doubt remove typename program doesn't compile Why ?????
    for (ptr = v.begin(); ptr != v.end(); ptr++)
    {
        cout << *ptr << ' ';
    }
    cout << '\n';
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
    v.push_back(10);
    v.push_back(11);
    v.push_back(12);
    GenericMyVector<int>::iterator it;
    // for(it=v.begin(); it!=v.end(); it++)
    //     cout << *it << " ";
    display_vector(v);
    cout << "size: " << v.size() << '\n';
    // cout << "out of bound: " << v[v.size()] << '\n';
    cout << "v[2]: " << v[2] << '\n';
    cout << "pop: " << v.pop_back() << '\n';
    display_vector(v);

    cout << "\n\n------- char ------\n";
    GenericMyVector<char> c;
    c.push_back('a');
    c.push_back('b');
    c.push_back('c');
    c.push_back('d');
    c.push_back('e');
    c.push_back('f');
    c.push_back('g');
    c.push_back('h');
    GenericMyVector<char>::iterator it1;
    // for(it1=c.begin(); it1!=c.end(); it++)
    //     cout << *it << " ";              // this can also be done to print elements
    display_vector(c);
    cout << "size: " << c.size() << '\n';
    // cout << "out of bound: " << v[v.size()] << '\n'; // uncomment to check out of bound
    cout << "c[2]: " << c[2] << '\n';
    cout << "pop: " << c.pop_back() << '\n';
    display_vector(c);
    return 0;
}
