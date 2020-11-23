#pragma once
#include <functional>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <type_traits>
#include <iostream>
namespace zungleif {
	template <typename T> class Blob;
	template <typename T> class BlobPtr;
	template <typename T> class vector;
	template <typename T> class shared_ptr;


	// template type parameter
	template <typename T> int compare(const T& a, const T& b) {
		if (std::less<T>()(a, b)) return -1;
		if (std::less<T>()(b, a)) return 1;
	}

	// template type parameter /w inline
	template <typename T> inline T _min(const T& a, const T& b) {
		if (a < b)	return a;
		else		return b;
	}

	// non-type template parameter
	template <unsigned N, unsigned M>
	int compare(const char(&a)[N], const char(&b)[M]) {
		return strcmp(a, b);
	}


	// 16.4
	template<typename Iter, typename Val>
	Iter find(Iter begin, Iter end, const Val _val) {
		Iter it;
		for (it = begin; it != end; it++) {
			if (*it == _val) {
				return it;
			}
		}
		return it;
	}

	// 16.5
	template <typename T, unsigned N>
	void print(const T(&arr)[N]) {
		for (auto temp : arr) {
			std::cout << temp;
		}
	}

	// 16.7
	template <typename T, unsigned N>
	constexpr unsigned getArrSize(const T(&arr)[N]) {
		return N;
	}

	// 16.11
	template <typename elemeType> class ListItem;
	template <typename elemType> class List {
	public:
		List();
		List(const List&);
		List& operator=(const List&);
		~List();
		void insert(ListItem<elemType> *ptr, elemType value);
	private:
		ListItem<elemType> *front, *end;
	};

	
	// 16.12
	template <typename> class BlobPtr;
	template <typename T> class Blob {
		friend class BlobPtr<T>;
	public:
		using value_type = T;
		using size_type = typename std::vector<T>::size_type;

		Blob()										: blob_ptr(std::make_shared<std::vector<T>>()) {}
		Blob(const std::initializer_list<T>& il)	: blob_ptr(std::make_shared<std::vector<T>>(il)) {}
		template<typename Iter> Blob(Iter _begin, Iter _end);
		size_type size() const				{ return blob_ptr->size(); }
		bool empty() const					{ return blob_ptr->empty(); }

		void push_back(const T& val)		{ blob_ptr->push_back(val); }
		void push_back(const T&& val)		{ blob_ptr->push_back(std::move(val)); }
		void pop_back()						{ blob_ptr->pop_back(); }
		
		constexpr BlobPtr<T> begin()		{ return BlobPtr<T>(*this); }
		constexpr BlobPtr<T> begin() const	{ return BlobPtr<T>(*this); }
		constexpr BlobPtr<T> end()			{ return BlobPtr<T>(*this, blob_ptr->size()); }
		constexpr BlobPtr<T> end() const	{ return BlobPtr<T>(*this, blob_ptr->size()); }

		constexpr T& front() const;
		constexpr T& back() const;
		constexpr T& operator[](size_type sz);

	private:
		std::shared_ptr<std::vector<T>> blob_ptr;
		void check(const size_type sz, const std::string& msg) const;
	};

	template <typename T>
	class BlobPtr {
	public:
		using value_type = T;
		using size_type = typename Blob<T>::size_type;
		BlobPtr()										: curr(0), wptr(nullptr) {}
		BlobPtr(Blob<T> _blob, size_type _curr = 0)		: wptr(_blob.blob_ptr), curr(_curr) {}

		BlobPtr& operator++();
		BlobPtr operator++(int);

		T& operator*() const;
	private:
		std::weak_ptr<std::vector<T>> wptr;
		size_type curr;
		std::shared_ptr<std::vector<T>> check(const size_type sz, const std::string& msg) const;
	};

	template <typename T> constexpr T& Blob<T>::front() const{
		check(0, "Front on empty Blob");
		return blob_ptr->front();
	}

	template <typename T> constexpr T& Blob<T>::back() const {
		check(size(), "Back on empty Blob");
		return blob_ptr->back();
	}

	template <typename T> constexpr T& Blob<T>::operator[](const size_type sz) {
		check(sz, "Accessing data out of range");
		return (*blob_ptr)[sz];
	}

	template <typename T> void Blob<T>::check(const size_type sz, const std::string& msg) const {
		if (size() <= sz)
			throw std::out_of_range(msg);
	}



	template <typename T> BlobPtr<T>& BlobPtr<T>::operator++() {
		check(curr++, "Incrementing past the end");
		return *this;
	}

	template <typename T> BlobPtr<T> BlobPtr<T>::operator++(int) {
		auto temp = *this;
		operator++();
		return temp;
	}

	template <typename T> T& BlobPtr<T>::operator*() const {
		auto p = check(curr, "Dereferencing unbound index");
		return (*p)[curr];
	}

	template <typename T> std::shared_ptr<std::vector<T>> 
	BlobPtr<T>::check(const size_type sz, const std::string& msg) const {
		auto data = wptr.lock();
		if (!data)
			throw "Unbound pointer";
		if (data->size() <= curr)
			throw std::out_of_range(msg);
		return data;
	}

	// 16.14, 16.15
	template <unsigned height, unsigned width>
	class Screen;

	// TODO: 
	template <unsigned height, unsigned width>
	std::istream& operator>>(std::istream& is, Screen<height, width>& scr) {
		return is;
	}

	template <unsigned height, unsigned width>
	std::ostream& operator<<(std::ostream& os, const Screen<height, width>& scr) {
		os << height << " " << width;
		return os;
	}

	template <unsigned height, unsigned width>
	class Screen {
	friend std::istream& operator>><height, width>(std::istream&, Screen<height, width>&);
	friend std::ostream& operator<<<height, width>(std::ostream&, const Screen<height, width>&);
	public:
	};


	// 16.16
	template <typename T> class base_iter;
	template <typename T> class iterator;
	template <typename T> class const_iterator;
	template <typename T>
	class vector {
		friend class iterator<T>;
		friend class const_iterator<T>;
	public:
		using size_type			= std::size_t;
		using value_type		= T;
		using reference_type	= T&;
		using iterator			= T*;
		using const_iterator	= const T*;
		using size_diff			= std::ptrdiff_t;

		vector() = default;
		vector(std::initializer_list<T> il);
		explicit vector(size_type);
		/*vector(const vector&);
		vector(vector&&) noexcept;
		vector& operator=(const vector&);
		vector& operator=(vector&&) noexcept;*/
		~vector();

		value_type& operator[](size_type);
		value_type& at(size_type);

		constexpr iterator begin()				{ return _begin; }
		constexpr const_iterator begin() const	{ return _begin; }
		constexpr iterator end()				{ return _end; }
		constexpr const_iterator end() const	{ return _end; }

		constexpr size_diff size() const		{ return _end - _begin; }
		constexpr size_diff capacity() const	{ return _cap - _begin; }

		void push_back(const T&);
		void resize(size_type);
	private:
		static std::allocator<T> alloc;
		iterator _begin = nullptr;
		iterator _end = nullptr;
		iterator _cap = nullptr;

		void check_n_alloc();
		std::pair<iterator, iterator> alloc_n_copy(const iterator&, const iterator&);
		void reallocate();
		void free();
	};

	template <typename T>
	std::allocator<T> vector<T>::alloc;

	template <typename T>
	vector<T>::vector(std::initializer_list<T> il) {
		std::for_each(il.begin(), il.end(),
			[this](auto val) {
			check_n_alloc();
			alloc.construct(_end++, std::move(val));
			}
		);
	}

	template <typename T>
	vector<T>::vector(size_type sz) {
		_begin = _end = alloc.allocate(sz);
		_cap = _begin + sz;
	}
	
	template <typename T>
	vector<T>::~vector() {
		free();
	}
	template <typename T>
	void vector<T>::push_back(const T& val) {
		check_n_alloc();
		alloc.construct(_end++, std::move(val));
	}

	template <typename T>
	void vector<T>::check_n_alloc(){
		if (size() == capacity())
			reallocate();
	}

	template <typename T>
	std::pair<T*, T*> vector<T>::alloc_n_copy
	(const iterator& begin, const iterator& end) {
		auto newbegin = alloc.allocate(end - begin);
		return {newbegin, std::uninitialized_copy(begin, end, newbegin)};
	}

	template <typename T>
	void vector<T>::reallocate() {
		auto newcap =  !static_cast<bool>(_begin) ? 1 : capacity() * 2;
		auto newbegin = alloc.allocate(newcap);
		auto newend = std::uninitialized_copy(std::make_move_iterator(begin()),
											  std::make_move_iterator(end()),
											  newbegin);
		/*auto oldbegin = _begin;
		while (oldbegin != _end) {
			alloc.construct(newend++, std::move(*oldbegin++));
		}*/
		free();
		_begin = newbegin;
		_end = newend;
		_cap = _begin + newcap;
	}

	template <typename T>
	void vector<T>::free() {
		if (capacity() > 0) {
			while (_begin != _end) {
				alloc.destroy(--_end);
			}
			alloc.deallocate(_begin, capacity());
		}
	}

	/*template <typename T>
	class base_iter {
	public:
		base_iter&  operator++()	{ ++curr; return *this; }
		base_iter  operator++(int)	{ auto temp = *this; ++*this; return temp; }
		base_iter&	operator--()	{ --curr; return *this; }
		base_iter	operator--(int) { auto temp = *this; --*this; return temp; }
		virtual T& operator*() = 0;
		virtual T* operator->() = 0;
		virtual ~base_iter() = 0;
		std::size_t curr;
	};

	template <typename T>
	class iterator : public base_iter<T> {
	public:
		using size_type = typename vector<T>::size_type;
		iterator(T*);
		iterator(vector<T>&, size_type);
		T& operator*() override { return *(ptr + base_iter<T>::curr); }
		T* operator->() override { return &(*this); }
	private:
		T* ptr;
	};

	template <typename T>
	class const_iterator : public base_iter<T> {
		using size_type = typename vector<T>::size_type;
		const_iterator(T*);
		const_iterator(const vector<T>&, size_type);
		T& operator*() const override { return *(ptr + base_iter<T>::curr); }
	private:
		const T* ptr;
	};*/

	// 16.17
	// 범위지정 연산자를 통해 클래스의 멤버에 접근 할 수 있는데 컴파일러는 이를 통해 접근한 것이 일반적으로
	// 멤버함수라고 추정한다. 따라서 템플릿 매개변수가 타입임을 알리려면 typename 키워드를 앞에 붙어야한다. 
	// class 키워드는 template parameter 를 지정할 때 같은 역활은 하지만 위에 나온 명시적으로 타입임을
	// 알리진 않는다

	// 16.19
	template <typename T>
	void printContainer(const T& cont) {
		for (typename T::size_type it = 0; it != cont.size(); it++) {
			std::cout << cont.at(it);
		}
	}

	// 16.20
	template <typename Iter>
	void printContainer(Iter _begin, Iter _end) {
		for (; _begin != _end; _begin++)
			std::cout << *_begin;
	}

	// 16.21
	class DebugDelete {
	public:
		DebugDelete(std::ostream& _os = std::cerr) : os(_os) {}
		// unique_ptr 에 이 객체를 통해 삭제자를 넘겨주고 관리하고 있는 동적 메모리를 삭제할 때,
		// 아래의 템플릿 멤버함수에서 넘겨준 인자를 통해 포인터의 타입을 추론하고 해당 타입을 delete 한다.
		template<typename T> void operator()(T* p)
		{os << "Deleter called in unique_ptr" << std::endl; delete p; }
	private:
		std::ostream& os;
	};

	// 16.24
	template<typename T>
	template<typename Iter>
	Blob<T>::Blob(Iter _begin, Iter _end) : Blob() {
		std::copy(_begin, _end, std::back_inserter(*blob_ptr));
	}

	// 16.28
	template<typename T>
	class shared_ptr {
		template <typename T, typename U> friend bool operator==(const shared_ptr<T>&, const shared_ptr<U>&) noexcept;
		template <typename T> friend void swap(shared_ptr<T>&, shared_ptr<T>&) noexcept;
		template <typename T> friend shared_ptr<T> make_shared(T&& val);
	public:
		using element_type		= typename std::remove_extent<T>::type;
		using count_size_type	= std::size_t;
		using deleter_type		= void (*)(T*);
		shared_ptr()								: ref_count(new count_size_type(1)) {}
		shared_ptr(T* p)							: mem(p), ref_count(new count_size_type(1)) {}
		shared_ptr(T* p, deleter_type d)			: shared_ptr(p), deleter(d) {}
		shared_ptr(const shared_ptr&);
		shared_ptr(shared_ptr&&) noexcept;
		shared_ptr& operator=(shared_ptr);
		shared_ptr& operator=(shared_ptr&&) noexcept;
		~shared_ptr();

		T& operator*() const						{ return mem ? *mem : throw std::logic_error("nullptr"); }
		T* operator->() const						{ return &this->operator*(); }

		explicit operator bool() const noexcept		{ return get() != nullptr; }

		count_size_type use_count() const			{ if(ref_count)	return *ref_count; }
		T* get() const								{ return operator*(); }
		shared_ptr& reset(T*);
		shared_ptr& reset(T*, deleter_type);
	private:
		T* mem = nullptr;
		std::size_t *ref_count = nullptr;
		deleter_type deleter = nullptr;
		void check_n_destroy();
	};

	template <typename T, typename U> bool operator==(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs) noexcept;
	template <typename T> void swap(shared_ptr<T>& lhs, shared_ptr<T>& rhs) noexcept;
	template <typename T> shared_ptr<T> make_shared(T&&); // -> non-const rvalue

	template <typename T>
	shared_ptr<T>::shared_ptr(const shared_ptr& org)
		: mem(org.mem), ref_count(org.ref_count), deleter(org.deleter)
	{
		if(ref_count)	(*ref_count)++;
	}

	template <typename T>
	shared_ptr<T>::shared_ptr(shared_ptr&& org) noexcept
		: mem(org.mem), ref_count(org.ref_count), deleter(org.deleter)
	{
		org.mem = nullptr;
		org.ref_count = nullptr;
		org.deleter = nullptr;
	}
	
	// copy & move substitute
	template <typename T>
	shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr rhs) {
		zungleif::swap(*this, rhs);
		return *this;
	}

	template <typename T>
	shared_ptr<T>::~shared_ptr() {
		check_n_destroy();
	}

	template <typename T>
	void shared_ptr<T>::check_n_destroy() {
		if(!ref_count) return;
		if(*ref_count < 0)	
			throw std::runtime_error("reference counter lower than 0 before decrementing");
		if (--(*ref_count) == 0) {
			deleter ? deleter(mem) : delete mem;
			delete ref_count;
			mem = nullptr;
			ref_count = nullptr;
		}
	}

	template <typename T>
	shared_ptr<T>& shared_ptr<T>::reset(T* ptr) {
		check_n_destroy();
		mem = ptr;
		ref_count = new count_size_type(1);
		deleter = nullptr;
		return *this;
	}

	template <typename T>
	shared_ptr<T>& shared_ptr<T>::reset(T* ptr, deleter_type d) {
		check_n_destroy();
		mem = ptr;
		ref_count = new count_size_type(1);
		deleter = d;
		return *this;
	}

	template <typename T, typename U>
	bool operator==(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs) noexcept {
		return lhs.get() == rhs.get();
	}
	
	template <typename T>
	void swap(shared_ptr<T>& lhs, shared_ptr<T>& rhs) noexcept {
		using std::swap;
		swap(lhs.mem, rhs.mem);
		swap(lhs.ref_count, rhs.ref_count);
		swap(lhs.deleter, rhs.deleter);
	}

	// TODO:
	// move constructor called when returning temp? why?
	// => temp is a r-value, therefore, returns using move constructor, not copy constructor
	template <typename T>
	shared_ptr<T> make_shared(T&& val) {
		shared_ptr<T> temp;
		temp.mem = new T(val);
		return temp;
	}
	


	template <typename T, typename D = DebugDelete>
	class unique_ptr {
	private:

	};

	// 16.29 & 16.30
	/*template <typename> class BlobPtr;
	template <typename T> class Blob {
		friend class BlobPtr<T>;
	public:
		using value_type = T;
		using size_type = typename std::vector<T>::size_type;

		Blob() : blob_ptr(std::make_shared<std::vector<T>>()) {}
		Blob(const std::initializer_list<T>& il) : blob_ptr(std::make_shared<std::vector<T>>(il)) {}
		template<typename Iter> Blob(Iter _begin, Iter _end);
		size_type size() const { return blob_ptr->size(); }
		bool empty() const { return blob_ptr->empty(); }

		void push_back(const T& val) { blob_ptr->push_back(val); }
		void push_back(const T&& val) { blob_ptr->push_back(std::move(val)); }
		void pop_back() { blob_ptr->pop_back(); }

		constexpr BlobPtr<T> begin() { return BlobPtr<T>(*this); }
		constexpr BlobPtr<T> begin() const { return BlobPtr<T>(*this); }
		constexpr BlobPtr<T> end() { return BlobPtr<T>(*this, blob_ptr->size()); }
		constexpr BlobPtr<T> end() const { return BlobPtr<T>(*this, blob_ptr->size()); }

		constexpr T& front() const;
		constexpr T& back() const;
		constexpr T& operator[](size_type sz);

	private:
		std::shared_ptr<std::vector<T>> blob_ptr;
		void check(const size_type sz, const std::string& msg) const;
	};*/
}