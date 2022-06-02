//------------------------------------------------------------------
// 2022�� 1�б� STL	3.2	 ��910	��910��56			(1�� 2��)
// SAVE.CPP
// 
// �Լ� save�� �����̸��� �˷��ָ� ���Ǹ� �����ϴ�
// 
// "2022�� 1�б� STL ��910��56 ��������.txt"�� ���ٿ� ����Ѵ�.
// 
// 2022.3.3							programed by robbi
//------------------------------------------------------------------




#include "save.h"
#include <fstream>
#include <filesystem>
#include <chrono>
#include <vector>
#include <algorithm>

void save( std::string_view fname)
{
	// ���� ������ ����
	std::ifstream in{ fname.data() };

	// �� ���ϵ� ����
	std::ofstream out{ "2022�� 1�б� STL ��910��56 ��������.txt", std::ios::app };

	out << std::endl << std::endl;

	// ������ ������ �̸��� ���Ͽ� ����Ѵ�
	out << "�����̸�: " << fname << std::endl;

	// ������ ������ ũ�⸦ ����Ѵ�(c++17)
	out << "����ũ��: " << std::filesystem::file_size(fname) << std::endl;

	// ���� ��¥�� �ð��� ����Ѵ�(c++20)
	auto time = floor<std::chrono::seconds>(std::chrono::system_clock::now());
	//out << std::chrono::zoned_time("Asia/Seoul", time) << std::endl;
	out << std::endl;


	// ���� ������ ������ �о� �� ���Ͽ� ���ٿ� ����
	// 1. ������ ������ ���ͷ� �о�´�
	std::vector<char> v{ std::istreambuf_iterator<char>{in}, {} };

	// 2. ���Ϳ� �ִ� ������ ���Ͽ� �����Ѵ�
	copy(v.begin(), v.end(), std::ostream_iterator<char>{out});

}