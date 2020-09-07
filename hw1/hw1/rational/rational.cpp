#include "rational.h"
#include <stdexcept>
// Libraries may be included as necessary

using namespace std;

int euclid(int a, int b);
Rational::Rational() : n(0), d(1) {}

Rational::Rational(int n, int d) {
    // Since the denominator cannot be zero an exception is thrown
    if (d == 0) {
        throw std::invalid_argument("division by zero");
    }
    this ->n = n;
    this ->d = d;

    // TODO: continue your implementation below.
    // You should likely set the member variables ad then call this->reduce()
    // and this->normalize().
    this ->reduce();
    this ->normalize();
}

void Rational::normalize() {

    if (n == 0 && d != 1) 
    {
        d = 1;
    }
	 if(this -> d < 0)
	 {
	 	this ->d *= -1;
	 	this ->n *= -1;
	 }
}
void Rational::reduce()
{
 int GCD = euclid(this->n,this->d);
 this -> n = n/GCD;
 this -> d = d/GCD;
}
int euclid(int a, int b)
{
	if(a == 0)
	{
		return b;
	}
	return euclid(b%a, a);
}

Rational Rational::operator+(const Rational& rhs) const {
    // TODO
    Rational sum;
    if(this->d == rhs.d)
    {
    	sum.d = this->d;
    	sum.n = this->n + rhs.n;
    }
    else
    {
    int LHD = this ->d;
    int RHD = rhs.d;
   	int LCM = (this->d )* rhs.d / (euclid(LHD,RHD));
   	sum.d = LCM;
   	sum.n = this->n *(LCM/this->d) + rhs.n *(LCM/rhs.d);
    }
    sum.reduce();
    sum.normalize();
    return sum;
}
Rational Rational::operator+(const int& rhs)const
{
	Rational sum;
	sum.d = this->d;
	sum.n = this->n + rhs*this->d;
	sum.reduce();
	sum.normalize();
	return sum;
}

Rational& Rational::operator+=(const Rational& rhs) {
    // TODO
    if(this->d == rhs.d)
    {
    	this -> n = this->n + rhs.n;
    }
    else
    {
	 int LCM = this->d * rhs.d / (euclid(this->d,rhs.d));
	 this -> d = LCM;
	 this-> n = this->n *(LCM/this->d) + rhs.n *(LCM/rhs.d);
    }
    this ->reduce();
    this ->normalize();
    return *this;
}
Rational& Rational::operator+=(const int& rhs)
{
	this->n += (rhs*this->d);
	return *this;
}
Rational& Rational::operator*=(const Rational& rhs)
{
	this->n *=rhs.n;
	this->d *= rhs.d;
	this->reduce();
	this->normalize();
	return *this;
}
Rational& Rational::operator*=(const int& rhs)
{
	this->n *= rhs;
	this->reduce();
	this->normalize();
	return *this;
}
Rational Rational::operator*(int rhs) const {
    // TODO
    Rational product;
    product.n = this -> n * rhs;
    product.d = this ->d;
    product.reduce();
    product.normalize();
    return product;
}
Rational Rational::operator*(const Rational rhs) const {
    // TODO
    Rational product;
    product.n = this -> n * rhs.n;
    product.d = this ->d * rhs.d;
    product.reduce();
    product.normalize();
    return product;
}
// This operator isn't prefixed by Rational:: because it's not actually a
// member of Rational. It just tells the compiler what to do when it sees
// multiplication between an int on the left and a Rational on the right. Our
// friend declaration simply enabled us to access private members on the const
// Rational& rhs in the function body.
//
// Note that we could implement any of the other operators above this same way
// using the corresponding global operator and passing a const Rational& lhs as
// the first argument, it's just a matter of convenience.
Rational operator*(int lhs, const Rational& rhs) {
    // TODO
	Rational product;
	product.n = lhs * rhs.n;
	product.d = rhs.d;
	product.reduce();
	product.normalize();
	return product;
}

bool Rational::operator==(const Rational& other) const{
    // TODO
    //assume that the other functions automatically normaliza and rationalize both objects
    if((this->n == other.n )&&(this->d == other.d))
    	return true;
    else
    	return false;
}
bool Rational::operator<(const Rational& other) const
{
	int LCM = this->d * other.d / (euclid(this->d,other.d));
	int LHN = this->n * LCM/this->d;
	int RHN = other.n *LCM/other.d;
	if(LHN < RHN)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Rational::operator>(const Rational& other) const
{
	int LCM = this->d * other.d / (euclid(this->d,other.d));
	int LHN = this->n * LCM/this->d;
	int RHN = other.n *LCM/other.d;
	if(LHN > RHN)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Rational::operator!=(const Rational& other) const
{
	//assume both Rational objects are rationalized and reduced when initialized
    if((this->n == other.n )&&(this->d == other.d))
    	return false;
    else
    	return true;
}
Rational Rational::operator^(const int Exponent) const
{
	Rational Product(1,1);
	if(Exponent == 0)
	{
		return Product;
	}
	if(Exponent < 0)
	{
		for(int i = 0; i < (-1 * Exponent); i++)
		{
			Product.n *= this->d;
			Product.d *= this->n;
		}
	}
	else{
		for(int i = 0; i < Exponent; i++)
		{
			Product.n *= this->n;
			Product.d *= this->d;
		}
	}
	Product.reduce();
	Product.normalize();
	return Product;

}
// TODO: implement the rest of your prototyped methods


ostream& operator<<(ostream& ostr, const Rational& rhs)
{
	ostr << rhs.n<<"/"<< rhs.d;
	return ostr;
}
istream& operator>>(istream& istr, Rational& rhs)
{
	
	int n;
	int d;
	istr >> n;
	while(istr.get()!= '/')
	{}
	istr >> d;
	Rational newRat(n,d);
	rhs = newRat;
	return istr;
}
Rational operator+(int lhs, const Rational& rhs)
{
	Rational sum;
	sum.d = rhs.d;
	sum.n = rhs.n + lhs*rhs.d;
	sum.reduce();
	sum.normalize();
	return sum;
}
