#include <iostream>
#include <string>
#include <cstdint>

struct Inner {

};

struct Class {
	int64_t asd;
	Inner inner;
};

//template <auto t>
//void mytemplate() {
//	std::cout << t << "\n";
//}

// https://stackoverflow.com/questions/670734/pointer-to-class-data-member

int main() {
	Class cls;
	std::cout << &cls.inner << "\n";

	std::cout << &Class::asd << "\n";
	std::cout << &Class::inner << "\n";
	//mytemplate<&Class::inner>();
}