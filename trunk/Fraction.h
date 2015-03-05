#ifndef _FRACTION
#define _FRACTION

#include <iostream>
using namespace std;

class fraction{
	private:
		int num;
		int den;

	public:
		fraction(int = 0, int = 1); //constructor con numerador y denominador

		System::String^ print(void);		// print the fraction

		fraction& operator~(void);			// reduce the fraction
		fraction operator-(void) const;	// negative of fraction
		fraction operator*(void) const;	// reciprocal of fraction
		fraction& operator+=(const fraction&);
		fraction& operator-=(const fraction&);
		fraction& operator*=(const fraction&);
		fraction& operator/=(const fraction&);
		fraction operator+(int) const;
		fraction operator-(int) const;
		fraction operator*(int) const;
		fraction operator/(int) const;
		bool operator>(const fraction&) const;
		bool operator<(const fraction&) const;
		bool operator>=(const fraction&) const;
		bool operator<=(const fraction&) const;
		bool operator==(const fraction&) const;
		bool operator!=(const fraction&) const;
		fraction operator+(const fraction&) const;
		fraction operator-(const fraction&) const;
		fraction operator*(const fraction&) const;
		fraction operator/(const fraction&) const;
		fraction& operator++();			// prefix operator returns by reference
		fraction operator++(int);			// postix operator returns by value
		int numerator(void);
		int denominator(void);
};

fraction convertToFraction(System::String^ s);

#endif