#include <iostream>
#include "complexsort.cpp"


int main(){
	complex a(5,5), b(2,3),c(1,5), d(4, 1), e;
	std::vector<complex> v;
	v.push_back(a);
	v.push_back(b);
	v.push_back(c);
	v.push_back(d);
	v.push_back(e);
	bubble(v);
	for(int i = 0; i < 5;++i)
		std::cout << v[i].absalute() << ' ';
	return 0;
}
