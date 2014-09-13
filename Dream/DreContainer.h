#ifndef __DRECONTAINER_H__
#define __DRECONTAINER_H__

// ���ھɰ汾��stlport��microsoft���ͻ̫�󣬸���ԭ����
#undef _STLP_DEBUG

// ����������
#include <map>
#include <hash_map>
#include <list>
#include <vector>
#include <set>
#include <deque>
#include <algorithm>
// ����������
#include <stack>
#include <queue>
#include <string>

namespace dream
{
	//�򵥵�ʹ��stlport������
	using std::vector;
	using std::list;
	using std::map;
	using std::make_pair;
	using std::multimap;
	using std::set;
	using std::multiset;
	using std::deque;

	//�򵥵�ʹ��stlport������������
	using std::queue;
	using std::priority_queue;
	using std::list;

	using std::string;
	using std::wstring;

//	using namespace stlport;
//
//////������///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	template< class _data >
//	class vector : public stlport::vector< _data >
//	{
//	public:
//		typedef stlport::vector< _data > BaseClass;
//
//        typedef typename BaseClass::allocator_type allocator_type;
//        typedef _data value_type;
//        typedef value_type* pointer;
//        typedef const value_type* const_pointer;
//        typedef value_type* iterator;
//        typedef const value_type* const_iterator;
//
//        typedef value_type& reference;
//        typedef const value_type& const_reference;
//        typedef size_t size_type;
//		typedef ptrdiff_t difference_type;
//
//		//����stlport::vector�Ĺ��캯��
//		vector() : BaseClass() {}
//        explicit vector( size_type _Count ) : BaseClass(_Count) {}
//        vector( size_type _Count, const _data& _Val ) : BaseClass( _Count, _Val ) {}
//        vector( const vector& _Right ) : BaseClass(_Right) {}
//        vector( const BaseClass& _Right ) : BaseClass(_Right) {}
//        template<class InputIterator> vector( InputIterator _First, InputIterator _Last ) 
//            : BaseClass( _First, _Last ) {}
//
//	};	// class vector
//
//	template< class _data >
//	class list : public stlport::list< _data, efd::CustomAllocator<_data> >
//    {
//    public:
//		//baseclass
//		typedef stlport::list< _data, efd::CustomAllocator<_data> > BaseClass;
//        
//		typedef _data value_type;
//        typedef value_type* pointer;
//        typedef const value_type* const_pointer;
//		typedef value_type& reference;
//        typedef const value_type& const_reference;
//        typedef size_t size_type;
//        typedef ptrdiff_t difference_type;
//        typedef typename BaseClass::allocator_type allocator_type;
//        
//		//������
//        typedef typename BaseClass::iterator iterator;
//        typedef typename BaseClass::const_iterator const_iterator;
//
//        //����stlport::list�Ĺ��캯��
//        list() : BaseClass() {}
//        explicit list( size_type _Count ) : BaseClass(_Count) {}
//        list( size_type _Count, const _data& _Val ) : BaseClass(_Count, _Val) {}
//        list( const list& _Right ) : BaseClass(_Right) {}
//        list( const BaseClass& _Right ) : BaseClass(_Right) {}
//        template<class InputIterator> list(InputIterator _First, InputIterator _Last) 
//            : BaseClass( _First, _Last ) {}
//    };	// class list
//
//	template< class _key, class _data, class _compare = stlport::less<_key> >
//	class map : public stlport::map< _key, _data, _cmp >
//	{
//		typedef stlport::map< _key, _data, _cmp > BaseClass;
//        typedef typename BaseClass::iterator iterator;
//        typedef typename BaseClass::const_iterator const_iterator;
//
//        //����stlport::map�Ĺ��캯��
//        map() : BaseClass() {}
//        explicit map(const _compare& _Comp) : BaseClass(_Comp) {}
//        map(const map& _Right) : BaseClass(_Right) {}
//        map(const BaseClass& _Right) : BaseClass(_Right) {}
//        template<class InputIterator> map( InputIterator _First, InputIterator _Last ) 
//            : BaseClass(_First, _Last) {}
//        template<class InputIterator> map( 
//            InputIterator _First, 
//            InputIterator _Last, 
//            const _compare& _Comp )
//            : BaseClass(_First, _Last, _Comp) {}
//	};	// class map
//
//	//set
//	template < class _data, class _compare = stlport::less<_data> >
//    class set : public stlport::set< _data, _compare >
//    {
//    public:
//        typedef stlport::set< _data, _compare, efd::CustomAllocator<_data> > BaseClass;
//
//        //����stlport::set�Ĺ��캯��
//        set() : BaseClass() {}
//        explicit set( const _compare& _Comp ) : BaseClass( _Comp ) {}
//        set( const set& _Right ) : BaseClass(_Right) {}
//        set( const BaseClass& _Right ) : BaseClass(_Right) {}
//        template<class InputIterator> set( InputIterator _First, InputIterator _Last ) 
//            : BaseClass(_First, _Last) {}
//        template<class InputIterator> set( 
//            InputIterator _First, 
//            InputIterator _Last, 
//            const _compare& _Comp )
//            : BaseClass(_First, _Last, _Comp) {}
//    };	// class set
//
//	//deque
//    template< class _data >
//    class deque : public stlport::deque< _data >
//    {
//    public:
//        typedef stlport::deque< _data > BaseClass;
//        typedef size_t size_type;
//
//        //����stlport::deque�Ĺ��캯��
//        deque() : BaseClass() {}
//        explicit deque( size_type _Count ) : BaseClass(_Count) {}
//        deque( size_type _Count, const _data& _Val ) : BaseClass( _Count, _Val ) {}
//        deque( const deque& _Right ) : BaseClass(_Right) {}
//        deque( const BaseClass& _Right ) : BaseClass(_Right) {}
//        template<class InputIterator> deque( InputIterator _First, InputIterator _Last ) 
//            : BaseClass( _First, _Last ) {}
//    };	// class deque
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//////�ַ����������ַ�����///////////////////////////////////////////////////////////////////////////////////
//    
//	typedef stlport::basic_string< char > string;
//    
//	typedef stlport::basic_string< wchar_t > wstring;
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//////����������/////////////////////////////////////////////////////////////////////////////////////////////
//
//	//stack
//	template< class _data, class _container = deque<_data> >
//    class stack : public stlport::stack< _data, _container >
//    {
//    public:
//        typedef stlport::stack< _data, _container > BaseClass;
//
//        stack() : BaseClass() {}
//        explicit stack(const _container& _Right) : BaseClass(_Right) {}
//    };	// class stack
//
//	//queue
//    template< class _data, class _container = deque<_data> >
//    class queue : public stlport::queue< _data, _container >
//    {
//    public:
//        typedef stlport::queue< _data, _container > BaseClass;
//
//        queue() : BaseClass() {}
//        explicit queue(const _container& _Right) : BaseClass(_Right) {}
//    };	// class queue
//
//	//priority_queue
//    template < class _data,  class _container = vector<_data>, class _compare = 
//        stlport::less<typename _container::value_type> >
//    class priority_queue : public stlport::priority_queue< _data, _container, _compare >
//    {
//    public:
//        typedef stlport::priority_queue< _data, _container, _compare > BaseClass;
//        typedef priority_queue<_data, _container, _compare> _Self;
//        typedef typename _container::value_type      value_type;
//        typedef typename _container::size_type       size_type;
//        typedef          _container                  container_type;
//
//        typedef typename _container::reference       reference;
//        typedef typename _container::const_reference const_reference;
//
//        //����stlport::priority_queue���캯��
//        priority_queue() : BaseClass() {}
//        explicit priority_queue(const _compare& _Comp) : BaseClass( _Comp ) {}
//        priority_queue(const _compare& _Comp, const _container& _Cont) 
//            : BaseClass( _Comp, _Cont ) {}
//        priority_queue(const priority_queue& _Right) : BaseClass( _Right ) {}
//        priority_queue(const BaseClass& _Right) : BaseClass( _Right ) {}
//        template<class InputIterator>
//        priority_queue(InputIterator _First, InputIterator _Last )
//            : BaseClass( _First, _Last ) {}
//        template<class InputIterator>
//        priority_queue(InputIterator _First, InputIterator _Last, const _compare& _Comp)
//            : BaseClass( _First, _Last, _Comp ) {}
//        template<class InputIterator>
//        priority_queue(
//            InputIterator _First, 
//            InputIterator _Last, 
//            const _compare& _Comp, 
//            const container_type& _Cont )
//            : BaseClass( _First, _Last, _Comp, _Cont ) {}
//    };	// class priority_queue

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}	// namespace dream

#endif	// __DRECONTAINER_H__
