//------------------------------------------------------------------
// 2022�� 1�б� STL	3.2	 ��910	��910��56			(13�� 1��)
//
// �и��� ���� - Complexity(���⵵) ����
// 
// C++ 20�� �ٽ�
// concepts
// range / view
//		coroutine
//		module - ixx
// 
// type traits
//------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <ranges>
#include <format>
#include <concepts>
#include <algorithm>
#include "save.h"
#include "STRING.h"
using namespace std;		// ���������� �� �� (���� �ȵ�)
extern bool ����;

int main()
{

	list<int>l{ 1,2,3,4,5 };
	ranges::sort(l);
	save("�ҽ�.cpp");
	
}