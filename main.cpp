//Amose Ho

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <iterator>

using namespace std;

template <typename T> class SA;
template <typename T> ostream& operator<< (ostream& os, const SA<T>& s);

template <typename T>
class SA {
  private:
    int low, high, size;
    T* p;

    public:
        class const_iterator;

    class iterator: public std::iterator<std::random_access_iterator_tag, T>
    {
        private:
            T* ptr;
            friend class const_iterator;

        public:
            iterator()
            {
                ptr = NULL;
            }

            iterator(T* ptr)
            {
                this->ptr = ptr;
            }

            iterator(const iterator& pointer)
            {
                this->ptr = pointer.ptr;
            }

            const iterator& operator=(const iterator& right)
            {
                ptr = right.ptr;
                return right;
            }

            iterator& operator++()
            {
                ptr++;
                return *this;
            }

            iterator operator++(int)
            {
                iterator temp(*this);
                ++(*this);
                return temp;
            }

            iterator& operator--()
            {
                ptr--;
                return *this;
            }

            iterator operator--(int)
            {
                iterator temp(*this);
                --(*this);
                return temp;
            }

            void operator+=(const int& index)
            {
                ptr += index;
            }

            void operator+=(const iterator& rhs)
            {
                ptr += rhs.p;
            }

            iterator operator+(const int& index)
            {
                iterator temp(*this);
                temp += index;
                return temp;
            }

            iterator operator+(const iterator& right)
            {
                iterator temp(*this);
                temp += right;

                return temp;
            }

            void operator-=(const int& index)
            {
                ptr -= index;
            }

            void operator-=(const iterator& right)
            {
                ptr -= right.p;
            }

            iterator operator-(const int& index)
            {
                iterator temp(*this);
                temp -= index;
                return temp;
            }

            int operator-(const iterator& right)
            {
                return ptr - right.ptr;
            }

            bool operator<(const iterator& right)
            {
                return (ptr - right.ptr) < 0;
            }

            bool operator<=(const iterator& right)
            {
                return (ptr - right.ptr) <= 0;
            }

            bool operator>(const iterator& right)
            {
                return (ptr - right.ptr) > 0;
            }

            bool operator>=(const iterator& right)
            {
                return (ptr - right.ptr) >= 0;
            }

            bool operator==(const iterator& right)
            {
                return (ptr == right.ptr);
            }

            bool operator!=(const iterator& pointer)
            {
                return (ptr != pointer.ptr);
            }

            T& operator[](const int& index)
            {
                return *(ptr+index);
            }

            T& operator*()
            {
                return *ptr;
            }

            T* operator->()
            {
                return ptr;
            }
    };

    class const_iterator: public std::iterator<std::random_access_iterator_tag, T>
    {
        private:
            const T* ptr;

        public:
            const_iterator()
            {
                ptr = NULL;
            }

            const_iterator(const T* ptr)
            {
                this->ptr = ptr;
            }

            const_iterator(const iterator& pointer)
            {
                this->ptr = pointer.ptr;
            }

            const_iterator(const const_iterator& pointer)
            {
                this->ptr = pointer.ptr;
            }

            const const_iterator& operator=(const const_iterator& pointer)
            {
                ptr = pointer.ptr;
                return pointer;
            }

            const const_iterator& operator=(const iterator& pointer)
            {
                ptr = pointer.ptr;
                return pointer;
            }

            const_iterator& operator++()
            {
                ptr++;
                return *this;
            }

            const_iterator operator++(int)
            {
                const_iterator temp(*this);
                ++(*this);
                return temp;
            }

            const_iterator& operator--()
            {
                ptr--;
                return *this;
            }

            const_iterator operator--(int)
            {
                const_iterator temp(*this);
                --(*this);
                return temp;
            }

            void operator+=(const int& index)
            {
                ptr += index;
            }

            void operator+=(const const_iterator& pointer)
            {
                ptr += pointer.ptr;
            }

            const_iterator operator+(const int& index) const
            {
                const_iterator temp(*this);
                temp += index;
                return temp;
            }

            const_iterator operator+(const const_iterator& pointer) const
            {
                const_iterator temp(*this);
                temp += pointer;
                return temp;
            }

            void operator-=(const int& index)
            {
                ptr -= index;
            }

            void operator-=(const const_iterator& pointer)
            {
                ptr -= pointer.ptr;
            }

            const_iterator operator-(const int& index) const
            {
                const_iterator temp(*this);
                temp -= index;
                return temp;
            }

            int operator-(const const_iterator& pointer) const
            {
                return ptr - pointer.ptr;
            }

            bool operator<(const const_iterator& pointer) const
            {
                return (ptr - pointer.ptr) < 0;
            }

            bool operator<=(const const_iterator& pointer) const
            {
                return (ptr - pointer.ptr) <= 0;
            }

            bool operator>(const const_iterator& pointer) const
            {
                return (ptr - pointer.ptr) > 0;
            }

            bool operator>=(const const_iterator& pointer) const
            {
                return (ptr - pointer.ptr) >= 0;
            }

            bool operator==(const const_iterator& pointer) const
            {
                return (ptr == pointer.ptr);
            }

            bool operator!=(const const_iterator& pointer) const
            {
                return (ptr != pointer.ptr);
            }

            const T& operator[](const int& index) const
            {
                return *(ptr + index);
            }

            const T& operator*() const
            {
                return *ptr;
            }

            const T* operator->() const
            {
                return ptr;
            }
    };

    iterator begin()
    {
        return iterator(p);
    }

    const_iterator begin() const
    {
        return const_iterator(p);
    }

    iterator end()
    {
        return iterator(p + size);
    }

    const_iterator end() const
    {
        return const_iterator(p + size);
    }

    SA(const const_iterator& first, const const_iterator& last)
    {
        size = last - first;
        p = new T[size];

        for(int i = 0; i < size; i++)
        {
            p[i] = first[i];
        }
    }


 // default constructor
 // allows for writing things like SA a;

    SA()
    {
        low = 0;
        high = -1;
        size = 0;
        p = NULL;
    }

 // 2 parameter constructor lets us write
 // SA x(10,20);

    SA(int l, int h)
    {
        if((h-l+1) <= 0)
        {
            cout<< "constructor error in bounds definition" << endl;
            exit(1);
        }

        this->low = l;
        this->high = h;
        size = high-low+1;
        p = new T[size];
    }

 // single parameter constructor lets us
 // create a SA almost like a "standard" one by writing
 // SA x(10); and getting an array x indexed from 0 to 9

    SA(int i)
    {
        low = 0;
        high = i-1;
        size = i;
        p = new T[size];
    }

 // copy constructor for pass by value and
 // initialization

    SA(const SA& s)
    {
        size = s.high - s.low + 1;
        p = new T[size];

        for(int i = 0; i < size; i++)
        {
            p[i] = s.p[i];
        }
        low = s.low;
        high = s.high;
    }
 // destructor

    ~SA()
    {
        delete [] p;
    }
 //overloaded [] lets us write
 //SA x(10,20); x[15]= 100;

    T& operator[](int i)
    {
        if(i < low || i > high)
        {
            cout << "index "<< i <<" out of range" << endl;
            exit(1);
        }
        return p[i - low];
    }

 // overloaded assignment lets us assign
 // one SA to another

    SA & operator=(const SA & s)
    {
        if(this == &s)
        {
            return *this;
        }

        delete [] p;
        int size = s.high - s.low + 1;
        p = new T[size];

        for(int i = 0; i < size; i++)
        {
            p[i] = s.p[i];
        }

        low = s.low;
        high = s.high;

        return *this;
    }

    operator T*()
    { // conversion function
        return p;
    }

    friend ostream& operator<< <T>(ostream& os, const SA<T>& s);
};

template <typename T>
ostream& operator<<(ostream& os, const SA<T>& s)
{
    for(int i = 0; i < s.size; i++)
    {
        os << s.p[i] << " ";
    }
    return os;
};

int main()
{

    SA<int> a(10), b(3,5);
    b[3]=4; b[4]=5; b[5]=3;
    int i;
    for( i=0;i<10;i++)
        a[i]=10-i;

    cout << "print a" << endl;
    for(SA<int>::const_iterator yellow_submarine = a.begin(); yellow_submarine != a.end(); ++yellow_submarine)
    {
        cout << *yellow_submarine << " ";
    }
    cout << endl;

    cout << "print b" << endl;
    for(SA<int>::const_iterator yellow_submarine = b.begin(); yellow_submarine != b.end(); ++yellow_submarine)
    {
        cout << *yellow_submarine << " ";
    }
    cout << endl;

    sort(a.begin(), a.end());
    cout << "sorted a" << endl << a << endl;

    sort(b.begin(), b.end());
    cout << "sorted b" << endl << b << endl;

    cout << "find" << endl;
    int x = 4;
    cout << "element is " << x << endl;
    SA<int>::iterator yellow_submarine = find(b.begin(), b.end(), x);

    if(yellow_submarine != b.end())
    {
        cout << "Element " << x << " found at index " << yellow_submarine - b.begin() << endl << endl;
    }
    else
    {
        cout << "Element " << x << " not found! " << endl << endl;
    }

    return 0;
}
