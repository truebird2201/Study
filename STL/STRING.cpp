//-----------------------------------------------------------------------------
// STRING - STL 내부 동작을 관찰하려고 만든 자원을 관리하는 클래스
//        - std::string 동작 대부분을 직접 구현하며 STL 동작방식을 이해
// 
// 2022.3.30
//-----------------------------------------------------------------------------

#include <iostream>
#include "STRING.h"


bool 관찰{ false }; // 관찰하려면 true로
int STRING::gid{}; // class static

STRING::STRING() : num{}, p{}, id{ ++gid } {
	if (관찰)
		print("디폴트");
};
STRING::STRING(const char* s) : num{ strlen(s) }, id{ ++gid } {
	// 기존에 num { strlen(s) }는 4바이트에 8바이트를 넣으려함 (축소변환)
	// , 연산자는 순서를 알 수 없음

	p = new char[num];
	memcpy(p, s, num);

	if (관찰)
		print("생성자(*)");
};

STRING::~STRING() {
	if (관찰)
		print("소멸자");
	if (num)
		delete[] p;
}

STRING::STRING(const STRING& other) : id{ ++gid }, num{ other.num } {
	p = new char[num];
	memcpy(p, other.p, num);
	if (관찰)
		print("복사생성");
}

STRING& STRING::operator=(const STRING& other) {
	if (this == &other)
		return *this;
	if (num)
		delete[] p;

	num = other.num;
	p = new char[num];
	memcpy(p, other.p, num);

	if (관찰)
		print("복사할당");
}
//2022.4.7 이동생성자/이동할당연산자
STRING::STRING(STRING&& other) noexcept : id{ ++gid }, num{other.num} {
	p = other.p;

	other.num = 0;
	other.p = nullptr;
	
	if (관찰)
		print("이동생성");
}

STRING& STRING::operator=(STRING&& other) noexcept {
	if (this != &other) {
		if (num)
			delete[] p;
		num = other.num;
		p = other.p;

		other.num = 0;
		other.p = nullptr;
	}
	if (관찰)
		print("이동할당");
	return *this;
}


STRING STRING::operator+(const STRING& rhs) const {
	STRING temp; // 임시객체 만들어 더한 후 리턴
	temp.num = num + rhs.num;
	temp.p = new char[temp.num];
	memcpy(temp.p, p, num);
	memcpy(temp.p + num, rhs.p, rhs.num);
	return temp;
}

void STRING::print(const char* s) const {
	std::cout << s << " [" << id << "] 객체:" << this;
	if (num)
		std::cout << " - 자원:" << num << " 주소" << (void*)p;
	else
		std::cout << " - 자원없음";
	std::cout << std::endl;
}

size_t STRING::getNum() const {
	return num;
}

std::ostream& operator<<(std::ostream& os, const STRING& s)
{
	for (int i{}; i < s.num; ++i)
		os << s.p[i];
	return os;
}

std::istream& operator>>(std::istream& is, STRING& s) {
	std::string str;
	is >> str;
	s = STRING(str.c_str());
	return is;
}