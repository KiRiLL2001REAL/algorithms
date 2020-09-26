#ifndef _FRACT_HPP
#define _FRACT_HPP

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Дробные числа
class fraction {
private:
	int numerator, denominator;
	
	int nod(int a, int b) {
		if (a != 0 && b != 0) {
			if (a > b) {
				return nod(a%b, b);
			}
			return nod(a, b%a);
		}
		return a+b;
	}
	
	void parse(const string& s) {
		string buffer = "";
		string str = s;
		vector<int> numbers = {};
		str += ' ';
		for (unsigned int i = 0; i < str.length(); i++) {
			if (str[i] != ' ' && str[i] != '/') {
				buffer += str[i];
				continue;
			}
			numbers.push_back(stoi(buffer));
			buffer = "";
		}
		str.pop_back();

		switch (numbers.size()) {
		case 1: {
			numerator = numbers[0];
			denominator = 1;
			break;
		}
		case 2: {
			numerator = numbers[0];
			denominator = numbers[1];
			simplify();
			break;
		}
		case 3: {
			numerator = numbers[0] * numbers[2];
			numbers[0] > 0 ? numerator += numbers[1] : numerator -= numbers[1];
			denominator = numbers[2];
			simplify();
			break;
		}
		}
	}

public:
	fraction() :
		fraction(0)
	{
	}

	fraction(int num, int denom = 1) :
		numerator(num),
		denominator(denom)
	{
		simplify();
	}
	
	fraction(const fraction& f) :
		numerator(f.numerator),
		denominator(f.denominator)
	{
	}

	void simplify() {
		int _nod = nod(abs(numerator), abs(denominator));
		numerator /= _nod;
		denominator /= _nod;
		if (denominator < 0) { // а вдруг?
			numerator *= -1;
			denominator *= -1;
		}
	}
	
	friend ostream& operator<< (ostream& out, const fraction& n) {
		fraction nn = n;
		out << nn.getString();
		return out;
	}
	
	friend fraction operator+(const fraction& a, const fraction& b) {
		fraction c;
		c.numerator = a.numerator * b.denominator + b.numerator * a.denominator;
		c.denominator = a.denominator * b.denominator;
		return c;
	}
	
	friend fraction operator-(const fraction& a, const fraction& b) {
		fraction c;
		c.numerator = a.numerator * b.denominator - b.numerator * a.denominator;
		c.denominator = a.denominator * b.denominator;
		return c;
	}
	
	friend fraction operator*(const fraction& a, const fraction& b) {
		fraction c;
		c.numerator = a.numerator * b.numerator;
		c.denominator = a.denominator * b.denominator;
		return c;
	}
	
	friend fraction operator/(const fraction& a, const fraction& b) {
		fraction c;
		c.numerator = a.numerator * b.denominator;
		c.denominator = a.denominator * b.numerator;
		return c;
	}
	
	fraction& operator+=(const fraction& a) {
		*this = *this + a;
		return *this;
	}
	
	fraction& operator-=(const fraction& a) {
		*this = *this - a;
		return *this;
	}

	fraction& operator*=(const fraction& a) {
		*this = *this * a;
		return *this;
	}

	fraction& operator/=(const fraction& a) {
		*this = *this / a;
		return *this;
	}

	fraction& operator=(const int& a) {
		numerator = a;
		denominator = 1;
		return *this;
	}

	fraction& operator=(const string& s) {
		parse(s);
		return *this;
	}

	string getString() {
		string res = "";
		int num = numerator;
		int denom = denominator;
		int full = num / denom;
		num %= denom;
		if (full != 0) {
			res += to_string(full);
			if (num != 0) {
				res += ' ';
			}
		}
		if (full < 0) {
			num *= -1;
		}
		if (num != 0 || full == 0) { // !(num == 0 && full != 0)
			res += to_string(num);
		}
		if (denom != 1) {
			res += "/";
			res += to_string(denom);
		}
		return res;
	}
	
	int getNumerator() {
		return numerator;
	}
	
	int getDenominator() {
		return denominator;
	}
};

#endif