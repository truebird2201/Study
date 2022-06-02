//-----------------------------------------------------------------------------
// STRING - STL ���� ������ �����Ϸ��� ���� �ڿ��� �����ϴ� Ŭ����
//        - std::string ���� ��κ��� ���� �����ϸ� STL ���۹���� ����
// 
// 2022.3.30
//-----------------------------------------------------------------------------

#include <iostream>
#include "STRING.h"


bool ����{ false }; // �����Ϸ��� true��
int STRING::gid{}; // class static

STRING::STRING() : num{}, p{}, id{ ++gid } {
	if (����)
		print("����Ʈ");
};
STRING::STRING(const char* s) : num{ strlen(s) }, id{ ++gid } {
	// ������ num { strlen(s) }�� 4����Ʈ�� 8����Ʈ�� �������� (��Һ�ȯ)
	// , �����ڴ� ������ �� �� ����

	p = new char[num];
	memcpy(p, s, num);

	if (����)
		print("������(*)");
};

STRING::~STRING() {
	if (����)
		print("�Ҹ���");
	if (num)
		delete[] p;
}

STRING::STRING(const STRING& other) : id{ ++gid }, num{ other.num } {
	p = new char[num];
	memcpy(p, other.p, num);
	if (����)
		print("�������");
}

STRING& STRING::operator=(const STRING& other) {
	if (this == &other)
		return *this;
	if (num)
		delete[] p;

	num = other.num;
	p = new char[num];
	memcpy(p, other.p, num);

	if (����)
		print("�����Ҵ�");
}
//2022.4.7 �̵�������/�̵��Ҵ翬����
STRING::STRING(STRING&& other) noexcept : id{ ++gid }, num{other.num} {
	p = other.p;

	other.num = 0;
	other.p = nullptr;
	
	if (����)
		print("�̵�����");
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
	if (����)
		print("�̵��Ҵ�");
	return *this;
}


STRING STRING::operator+(const STRING& rhs) const {
	STRING temp; // �ӽð�ü ����� ���� �� ����
	temp.num = num + rhs.num;
	temp.p = new char[temp.num];
	memcpy(temp.p, p, num);
	memcpy(temp.p + num, rhs.p, rhs.num);
	return temp;
}

void STRING::print(const char* s) const {
	std::cout << s << " [" << id << "] ��ü:" << this;
	if (num)
		std::cout << " - �ڿ�:" << num << " �ּ�" << (void*)p;
	else
		std::cout << " - �ڿ�����";
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