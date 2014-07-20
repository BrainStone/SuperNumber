#include <iostream>
#include "SuperNumber.h"

using namespace std;

int main() {
	SuperNumber<long long> test1;
	SuperNumber<long long> test2(5445656LL);
	SuperNumber<long long> test3(544);
	SuperNumber<long long> test4(54.569);
	SuperNumber<long long> test5(54.569F);
	SuperNumber<long long> test6("54.569", 16);
	SuperNumber<long long> test7(L"54.569", 36);

	SuperNumber<long long> test8 = test2 + test3;
	cout << test8.to_String() << endl;

	test8 = test2 + test2;
	cout << test8.to_String() << endl;

	test8 = test2 + test1;
	cout << test8.to_String() << endl;

	test8 = test2 - test2;
	cout << test8.to_String() << endl;

	test8 = (test2 + SuperNumber<long long>(1)) - test2;
	cout << test8.to_String() << endl;

	test8 = SuperNumber<long long>(10000);
	cout << test8.to_String() << endl;

	test8 = (SuperNumber<long long>(100) * SuperNumber<long long>(100));
	cout << test8.to_String() << endl;

	test8 = SuperNumber<long long>(123*321);
	cout << test8.to_String() << endl;

	test8 = (SuperNumber<long long>(123) * SuperNumber<long long>(321));
	cout << test8.to_String() << endl;
}