#include "stdafx.h" //este include hay que ponerle el primero, sino por alguna razón ignora los otros includes
#include "Fraction.h"

//CONSTRUCTOR
fraction::fraction(int n, int d)
{
	num = n;
	den = d;
}

fraction convertToFraction(System::String^ s){
	int num, den;
	for (int i = 0; i < s->Length; i++){
		if (s[i] == '/'){
			num = System::Convert::ToInt32(s->Substring(0, i));
			den = System::Convert::ToInt32(s->Substring(i + 1, s->Length - i - 1));
			return ~fraction(num, den);
		}
	}
	num = System::Convert::ToInt32(s);
	den = 1;
	return ~fraction(num, den);
}

System::String^ fraction::print(void) {
	if (den > 1){
		return System::String::Concat(num, "/", den);
	} else
		return System::String::Concat(num);
}

int MCD(int x, int y)
{
	if (y == 0)
		return x;
	else
		return MCD(y, x%y);
}

fraction& fraction::operator~(void) {
	int mcd;
	bool neg = false;
	//primero vemos si el num. es 0
	if (num == 0){
		den = 1;
		return *this;
	}
	if (num < 0){
		num = -num;
		neg = !neg;
	}
	if (den < 0){
		den = -den;
		neg = !neg;
	}
	mcd = MCD(num, den);
	num /= mcd;
	den /= mcd;
	if (neg)
		num = -num;
	return *this;
}

fraction fraction::operator-(void) const {
	return ~fraction(-num, den);
}

fraction fraction::operator*(void) const {
	return ~fraction(den, num);
}

fraction& fraction::operator+=(const fraction& f) {
	num = num*f.den + den*f.num;
	den = den*f.den;
	return ~(*this);
}

fraction& fraction::operator-=(const fraction& f) {
	*this += (-f);
	return ~(*this);
}

fraction& fraction::operator*=(const fraction& f) {
	num = num*f.num;
	den = den*f.den;
	return ~(*this);
}

fraction& fraction::operator/=(const fraction& f) {
	*this *= (*f);
	return ~(*this);
}

bool fraction::operator>(const fraction& f) const {
	return (float)num / den > (float)f.num / f.den;
}

bool fraction::operator<(const fraction& f) const {
	return f>*this;
}

bool fraction::operator==(const fraction& f) const {
	return num*f.den == den*f.num;
}

bool fraction::operator!=(const fraction& f) const {
	return !(*this == f);
}

bool fraction::operator<=(const fraction& f) const {
	return !(*this > f);
}

bool fraction::operator>=(const fraction& f) const {
	return !(*this<f);
}

fraction fraction::operator+(const fraction& f) const {
	return ~fraction(num*f.den + den*f.num, den*f.den);
}

fraction fraction::operator-(const fraction& f) const {
	return ~fraction(num*f.den - den*f.num, den*f.den);
}

fraction fraction::operator*(const fraction& f) const {
	return ~fraction(num*f.num, den*f.den);
}

fraction fraction::operator/(const fraction& f) const {
	return ~((*this) * (*f));
}

fraction fraction::operator+(int i) const {
	return ~fraction(num + i*den, den);
}

fraction fraction::operator-(int i) const {
	return ~((*this) + -i);
}

fraction fraction::operator*(int i) const {
	return ~fraction(num*i, den);
}

fraction fraction::operator/(int i) const {
	return ~fraction(num, i*den);
}

// prefix increment operator
fraction& fraction::operator++() {
	num += den;
	return ~(*this);
}

// postfix increment operator
fraction fraction::operator++(int) {		// Note dummy int argument
	fraction temp(*this);
	++*this;							// call the prefix operator
	return ~(temp);
}

int fraction::numerator(void){
	return this->num;
}
int fraction::denominator(void){
	return this->den;
}