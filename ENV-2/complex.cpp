#include "complex.h"

complex::complex(double a= 0, double b= 0):a(a),b(b){}

complex::complex(const complex& other) {
        this->a = other.a,this->b =  other.b;
}


complex complex::operator+(const complex& other) const {
	return complex(this->a + other.a, this->b + other.b);
}

complex complex::operator-(const complex& other) const { 
        return complex(this->a - other.a, this->b - other.b);
}

complex complex::operator*(const double k) const { 
        return complex(this->a*k, this->b*k);
}

complex complex::operator=(const complex& other) {
	this->a = other.a;
	this->b = other.b; 
        return *this;
}


double complex::absalute(){
	return sqrt(a*a + b*b);
}

