//-----------------------------------------------------------------------------
// STRING - STL ���� ������ �����Ϸ��� ���� �ڿ��� �����ϴ� Ŭ����
//        - std::string ���� ��κ��� ���� �����ϸ� STL ���۹���� ����
// 
// 2022.3.30
//-----------------------------------------------------------------------------


#pragma once

#include <iostream>
#include <algorithm>

class STRING_iterator {
public:
	// ǥ�� �ݺ��ڰ� �����ؾ� �� Ÿ��
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
	// 2022.4.28 sort �����ϵ��� ������ �߰�

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

//2022.4.27 STRING�� ������ ������ �ݺ���
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

	// <, >, <=, >=, ==, != (���迬���� 6�� , relation operator)
	// ���迬���ڴ� ���ּ������ڷ� �ѹ��� �ذ� - C++ 20
	// spaceship operator(three-way comparison operator)
	auto operator<=>(const STRING_reverse_iterator& ) const = default;

	bool operator!=(const STRING_reverse_iterator& rhs) const {
		// ������ �Լ� �켱
		return p != rhs.p;
	}
};

class STRING {
public:
	using reverse_iterator = STRING_reverse_iterator;
	using iterator = STRING_iterator;

private:
	size_t num;	// �����ϴ� �ڿ� ��
	char* p;	// �ڿ��� �ּ�
	int id;		// ���� �� �ο��� ������
	static int gid; // id ������
public:
	STRING();
	STRING(const char* s);
	~STRING();

	STRING(const STRING& other);
	STRING& operator=(const STRING& other);

	//2022.4.7 �̵�������/�̵��Ҵ翬����
	STRING(STRING&& other) noexcept;
	STRING& operator=(STRING&& other) noexcept;

	STRING operator+(const STRING& rhs) const;

	//2022.4.28 sort�� ���� default < ������ ����
	/*
	bool operator<(const STRING& rhs) const {
		//������ ��
		return std::lexicographical_compare(begin(), end(),
			rhs.begin(), rhs.end());
	}
	*/

	//auto operator<=>(const STRING&) const = default;
	
	//2022.5.18. unordered_set�� �䱸�ϴ� == �ڵ�
	bool operator==(const STRING& rhs) const {
		return std::string({ begin(), end() }) == std::string({ rhs.begin(), rhs.end() });
	}


	//2022.4.21 begin(), end() ����
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
	// 2022.4.28 �߰� 
	friend std::istream& operator>>(std::istream&, STRING&);
};
