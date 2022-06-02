//-----------------------------------------------------------------------------
// STRING - STL 내부 동작을 관찰하려고 만든 자원을 관리하는 클래스
//        - std::string 동작 대부분을 직접 구현하며 STL 동작방식을 이해
// 
// 2022.3.30
//-----------------------------------------------------------------------------


#pragma once

#include <iostream>
#include <algorithm>

class STRING_iterator {
public:
	// 표준 반복자가 응답해야 할 타입
	using iterator_category = std::random_access_iterator_tag;
	using value_type = char;
	using difference_type = std::ptrdiff_t;
	using pointer = char*;
	using reference = char&;

private:
	char* p;

public:
	STRING_iterator(char* p) : p{ p } {}

	difference_type operator-(const STRING_iterator rhs) const {
		return p - rhs.p;
	}
	// 2022.4.28 sort 가능하도록 연산자 추가

	auto operator<=>(const STRING_iterator& ) const = default;

	STRING_iterator& operator++() {
		++p;
		return *this;
	}

	char& operator*() const{
		return *p;
	}

	STRING_iterator& operator--() {
		--p;
		return *this;
	}

	STRING_iterator operator+(difference_type d) const {
		return STRING_iterator{ p + d };
	}

	STRING_iterator operator-(difference_type d) const {
		return STRING_iterator{ p - d };
	}
	
};

//2022.4.27 STRING이 제공할 역방향 반복자
class STRING_reverse_iterator {
	char* p;

public:
	STRING_reverse_iterator(char* p) : p{ p } {}

	STRING_reverse_iterator& operator++() {
		--p;
		return *this;
	}

	char& operator*() const {
		return *(p - 1);
	}

	// <, >, <=, >=, ==, != (관계연산자 6개 , relation operator)
	// 관계연산자는 우주선연산자로 한번에 해결 - C++ 20
	// spaceship operator(three-way comparison operator)
	auto operator<=>(const STRING_reverse_iterator& ) const = default;

	bool operator!=(const STRING_reverse_iterator& rhs) const {
		// 정의한 함수 우선
		return p != rhs.p;
	}
};

class STRING {
public:
	using reverse_iterator = STRING_reverse_iterator;
	using iterator = STRING_iterator;

private:
	size_t num;	// 관리하는 자원 수
	char* p;	// 자원의 주소
	int id;		// 생성 시 부여한 고유값
	static int gid; // id 생성용
public:
	STRING();
	STRING(const char* s);
	~STRING();

	STRING(const STRING& other);
	STRING& operator=(const STRING& other);

	//2022.4.7 이동생성자/이동할당연산자
	STRING(STRING&& other) noexcept;
	STRING& operator=(STRING&& other) noexcept;

	STRING operator+(const STRING& rhs) const;

	//2022.4.28 sort를 위해 default < 연산자 제공
	/*
	bool operator<(const STRING& rhs) const {
		//사전식 비교
		return std::lexicographical_compare(begin(), end(),
			rhs.begin(), rhs.end());
	}
	*/

	//auto operator<=>(const STRING&) const = default;
	
	//2022.5.18. unordered_set이 요구하는 == 코딩
	bool operator==(const STRING& rhs) const {
		return std::string({ begin(), end() }) == std::string({ rhs.begin(), rhs.end() });
	}


	//2022.4.21 begin(), end() 제공
	iterator begin() const {
		return iterator{ p };
	}

	iterator end() const {
		return iterator{ p + num };
	}

	reverse_iterator rbegin() {
		return reverse_iterator{ p + num };
	}

	reverse_iterator rend() {
		return reverse_iterator{ p };
	}
	


	size_t getNum() const ;

	void print(const char* s) const;

	friend std::ostream& operator<<(std::ostream&, const STRING&);
	// 2022.4.28 추가 
	friend std::istream& operator>>(std::istream&, STRING&);
};
