//------------------------------------------------------------------
// 2022년 1학기 STL	3.2	 수910	수910목56			(13주 1일)
//
// 분리와 정렬 - Complexity(복잡도) 순서
// 
// C++ 20의 핵심
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
using namespace std;		// 가독성으로 만 씀 (쓰면 안됨)
extern bool 관찰;

int main()
{

	list<int>l{ 1,2,3,4,5 };
	ranges::sort(l);
	save("소스.cpp");
	
}