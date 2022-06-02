//------------------------------------------------------------------
// 2022년 1학기 STL	3.2	 수910	수910목56			(1주 2일)
// SAVE.CPP
// 
// 함수 save에 파일이름을 알려주면 강의를 저장하는
// 
// "2022년 1학기 STL 수910목56 강의저장.txt"에 덧붙여 기록한다.
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
	// 읽을 파일을 연다
	std::ifstream in{ fname.data() };

	// 쓸 파일도 연다
	std::ofstream out{ "2022년 1학기 STL 수910목56 강의저장.txt", std::ios::app };

	out << std::endl << std::endl;

	// 저장할 파일의 이름을 파일에 출력한다
	out << "파일이름: " << fname << std::endl;

	// 저장할 파일의 크기를 출력한다(c++17)
	out << "파일크기: " << std::filesystem::file_size(fname) << std::endl;

	// 현재 날짜와 시간을 출력한다(c++20)
	auto time = floor<std::chrono::seconds>(std::chrono::system_clock::now());
	//out << std::chrono::zoned_time("Asia/Seoul", time) << std::endl;
	out << std::endl;


	// 읽을 파일의 정보를 읽어 쓸 파일에 덧붙여 쓴다
	// 1. 파일의 내용을 벡터로 읽어온다
	std::vector<char> v{ std::istreambuf_iterator<char>{in}, {} };

	// 2. 벡터에 있는 내용을 파일에 복사한다
	copy(v.begin(), v.end(), std::ostream_iterator<char>{out});

}