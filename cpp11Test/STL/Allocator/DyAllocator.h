// file: 2jjalloc.h

#ifndef __JJALLOC__
#define __JJALLOC_

#include <new>      // for placement new
#include <cstddef>  // for ptrdiff_t, size_t
#include <cstdlib>  // for exit()
#include <climits>  // for UINT_MAX
#include <iostream> // for cerr
using namespace std;

// ��ȫ�������ռ�����һ���Դ��ġ����ص�operator newר�����������ڴ档
// Ĭ������±������Ὣnew����ؼ��ַ�������operator new����Ӧ�Ĺ��캯����
// �����е�����£��û��Լ�������������operator new����������£�������Ĭ�ϻ�ʹ���������ص�operator new
// ����������Ϊ��������������ռ����ڶ�������Լ���Ҫ�ĺ�����ѡ�õ�һ������
// ���������Ҫ����ʹ��Ĭ�ϵ�operator new����Ӧ��д��::new ������˼���ǵ�������������ռ��е�operator new
// ֵ��һ����������ģ�Ҳ��Ĭ�ϵģ�operator newҲ�ǿ��Ա����صġ�ͨ�����ַ�ʽ���ǿ��Ըı�����new�Ĳ�����Ϊ��

namespace dy {
    // ���ÿռ䣬���Դ��� n�� T���󡣵ڶ��Ա����Ǹ���ʾ��
    // ���ܻ������������������ԣ�locality��������ȫ����֮��
    template <class T>
    inline T* _allocate(ptrdiff_t size, T*) {
        set_new_handler(0);
        T* tmp = (T*)(::operator new((size_t)(size * sizeof(T))));
        if (tmp == 0) {
            cerr << "out of memory" << endl;
            exit(1);
        }
        return tmp;
    }

    // �黹��ǰ���õĿռ�
    template <class T>
    inline void _deallocate(T* buffer) {
        ::operator delete(buffer);
    }

    // ��ͬ�� new(const void*) p) T(x)
    template <class T1, class T2>
    inline void _construct(T1* p, const T2& value) {
        new (p) T1(value);   // placement new. invoke ctor of T1
    }

    // ��ͬ�� p->~T()��
    template <class T>
    inline void _destroy(T* ptr) {
        ptr->~T();
    }

    template <class T>
    class allocator {
    public:
        typedef T          value_type;
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef T& reference;
        typedef const T& const_reference;
        typedef size_t     size_type;
        typedef ptrdiff_t  difference_type;

        // rebind allocator of type U
        template <class U>
        struct rebind {
            typedef allocator<U> other;
        };

        // hint used for locality. ref. [Austern], p189
        pointer allocate(size_type n, const void* hint = 0) {
            return _allocate((difference_type)n, (pointer)0);
        }

        void deallocate(pointer p, size_type n) {
            _deallocate(p);
        }

        void construct(pointer p, const T& value) {
            _construct(p, value);
        }

        void destroy(pointer p) {
            _destroy(p);
        }

        // ����ĳ������ĵ�ַ��a.address(x)��ͬ�� &x
        pointer address(reference x) {
            return (pointer)&x;
        }

        // ����ĳ�� const����ĵ�ַ��a.address(x)��ͬ�� &x
        const_pointer const_address(const_reference x) {
            return (const_pointer)&x;
        }

        // ���ؿɳɹ����õ������
        size_type max_size() const {
            return size_type(UINT_MAX / sizeof(T));
        }
    };
}
#endif