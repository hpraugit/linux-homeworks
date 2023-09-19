#pragma once
#include <iostream>
#include <cmath>
#include <vector>


class complex{
private:
	double a;
	double b;
public:
	complex(double a, double b);
	complex(const complex& other);
	complex operator=(const complex& other);
	complex operator+(const complex& other) const;
	double absalute();
	complex operator-(const complex& other) const;
	complex operator*(const double k) const;
};

