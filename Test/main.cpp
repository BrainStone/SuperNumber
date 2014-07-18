#include <iostream>
#include "SuperNumber.h"

using namespace std;

int main() {
	SuperNumber<long long> test1;
	SuperNumber<long long> test2(5445656LL);
	SuperNumber<long> test3(544);
	SuperNumber<long long> test4(54.569);
	SuperNumber<long long> test5(54.569F);
	SuperNumber<long long> test6("54.569", 16);
	SuperNumber<long long> test7(L"54.569", 36);

	test2 = 1;
	test3 = -1;
}