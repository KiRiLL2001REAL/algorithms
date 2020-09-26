#ifndef _matrix_HPP
#define _matrix_HPP

#include <iostream>
#include <vector>
#include <string>
#include "fraction.hpp"

using namespace std;

// линейные матрицы
class matrix {
private:
	vector<vector<fraction>> table;
	
	void parse(const vector<string>& vec) {
		unsigned int size_i = table.size();
		unsigned int size_j = table[0].size();
		for (unsigned int i = 0; i < size_i; i++) {
			for (unsigned int j = 0; j < size_j; j++) {
				fraction f;
				f = vec[i * size_j + j];
				table[i][j] = f;
			}
		}
	}

	string getString() {
		string res = "";
		vector<vector<unsigned int>> cells_size = {}; // заполняем вектор длинами строковых эквивалентов чисел
		for (unsigned int i = 0; i < table.size(); i++) { // строка
			vector<unsigned int> temp = {};
			for (unsigned int j = 0; j < table[0].size(); j++) { // столбец
				unsigned int length = table[i][j].getString().length();
				temp.push_back(length);
			}
			cells_size.push_back(temp);
		}
		vector<unsigned int> column_size = {}; // нахождим максимальную длину элемента в столбце
		for (unsigned int j = 0; j < table[0].size(); j++) { // строка
			unsigned int max = 0;
			for (unsigned int i = 0; i < table.size(); i++) { // столбец
				if (cells_size[i][j] > max) {
					max = cells_size[i][j];
				}
			}
			column_size.push_back(max);
		}
		unsigned int table_length = 0; // длина таблицы (в символах)
		for (unsigned int i = 0; i < column_size.size(); i++) { // находим суммарную длину колонок
			table_length += column_size[i];
		}
		table_length += column_size.size() - 1;	// прибавляем количество перегородок-1 (углы таблицы оформлены знаком @)
		res += '@';
		for (unsigned int i = 0; i < table_length; i++) { // печатаем шапку таблицы
			res += '=';
		}
		res += "@\n";
		for (unsigned int i = 0; i < table.size(); i++) { // печатаем столбцы таблицы
			res += '|';
			for (unsigned int j = 0; j < table[0].size(); j++) { // печатаем строки
				res += table[i][j].getString();
				for (unsigned int k = 0; k < column_size[j] - cells_size[i][j]; k++) { // допечатываем пробелы если длина строкового эквивалента элемента таблицы меньше "длины" текущего столбца
					res += ' ';
				}
				res += '|';
			}
			res += '\n';
		}
		res += '@';
		for (unsigned int i = 0; i < table_length; i++) { // печатаем низ таблицы
			res += '=';
		}
		res += '@';
		return res;
	}

public:
	matrix() : 
		matrix(1, 1)
	{
	}

	matrix(unsigned int m, unsigned int n) {
		// m - strings, n - rows
		for (unsigned int i = 0; i < m; i++) {
			vector<fraction> temp = {};
			for (unsigned int j = 0; j < n; j++) {
				temp.push_back(fraction(0));
			}
			table.push_back(temp);
		}
	}
	
	matrix(const matrix& t) :
		table(t.table)
	{
	}
	
	friend ostream& operator<<(ostream& out, matrix& m) {
		out << m.getString();
		return out;
	}

	friend matrix operator+(const matrix& a, const matrix& b) {
		vector<unsigned int> size_a = {}, size_b = {};
			size_a.push_back(a.table.size());
			size_a.push_back(a.table[0].size());
			size_b.push_back(b.table.size());
			size_b.push_back(b.table[0].size());
			
		if (size_a[0] == size_b[0] && size_a[1] == size_b[1]) {
			matrix c(size_a[0], size_a[1]);
			for (unsigned int i = 0; i < size_a[0]; i++) {
				for (unsigned int j = 0; j < size_a[1]; j++) {
					c[i][j] = a.table[i][j] + b.table[i][j];
					c[i][j].simplify();
				}
			}
			return c;
		}

		cout << "Tables can't be added due to incompatible sizes (" << size_a[0] << "x" << size_a[1] << " " << size_b[0] << "x" << size_b[1] << ").\n";
		return matrix(1, 1);
	}

	friend matrix operator+(const matrix& a, const fraction& f) {
		unsigned int size = a.table.size();
		matrix b(size, size);
		b = f;
		return a + b;
	}

	friend matrix operator+(const fraction& f, const matrix& a) {
		return a + f;
	}

	friend matrix operator-(const matrix& a, const matrix& b) {
		return a + b * -1;
	}

	friend matrix operator-(const matrix& a, const fraction& f) {
		return a + f * -1;
	}

	friend matrix operator-(const fraction& f, const matrix& a) {
		return a * -1 + f;
	}

	friend matrix operator*(const matrix& a, const fraction& f) {
		return f * a;
	}

	friend matrix operator*(const fraction& f, const matrix& a) {
		vector<unsigned int> size = {};
		size.push_back(a.table.size());
		size.push_back(a.table[0].size());
		
		matrix c(size[0], size[1]);
		for (unsigned int i = 0; i < size[0]; i++) { // строка
			for (unsigned int j = 0; j < size[1]; j++) { // столбец
				c[i][j] = a.table[i][j] * f;
				c[i][j].simplify();
			}
		}
		return c;
	}

	friend matrix operator*(const matrix& a, const matrix& b) {
		vector<unsigned int> size_a = {}, size_b = {};
			size_a.push_back(a.table.size());
			size_a.push_back(a.table[0].size());
			size_b.push_back(b.table.size());
			size_b.push_back(b.table[0].size());
			
		if (size_a[1] == size_b[0]) {
			matrix c(size_a[0], size_b[1]);
			for (unsigned int i = 0; i < size_a[0]; i++) { // по строкам первой матрицы
				for (unsigned int j = 0; j < size_b[1]; j++) { // по столбцам второй матрицы
					for (unsigned int k = 0; k < size_a[1]; k++) { // по столбцам первой и строкам второй матицы
						c[i][j] = c[i][j] + a.table[i][k] * b.table[k][j];
					}
					c[i][j].simplify();
				}
			}
			return c;
		}
		cout << "Tables can't be multiplied due to incompatible sizes (" << size_a[0] << "x" << size_a[1] << " " << size_b[0] << "x" << size_b[1] << ").\n";
		return matrix(1, 1);
	}

	matrix& operator+=(const matrix& a) {
		*this = *this + a;
		return *this;
	}

	matrix& operator+=(const fraction& f) {
		*this = *this + f;
		return *this;
	}

	matrix& operator-=(const matrix& a) {
		*this = *this - a;
		return *this;
	}

	matrix& operator-=(const fraction& f) {
		*this = *this - f;
		return *this;
	}

	matrix& operator*=(const matrix& a) {
		*this = *this * a;
		return *this;
	}

	matrix& operator=(const matrix& a) {
		table = a.table;
		return *this;
	}

	matrix& operator=(const fraction& f) {
		unsigned int size_i = table.size();
		unsigned int size_j = table[0].size();
		if (size_i == size_j) {
			for (unsigned int i = 0; i < size_i; i++) {
				for (unsigned int j = 0; j < size_j; j++) {
					table[i][j] = i == j ? f : 0;
				}
			}
		}
		else {
			cout << "Error. Can't assign identity matrix due to incompatible size (" << size_i << "x" << size_j << ")\n";
		}
		return *this;
	}

	matrix& operator=(const vector<string>& vec) {
		parse(vec);
		return *this;
	}

	matrix transposed() {
		matrix res(table[0].size(), table.size());
		for (unsigned int i = 0; i < table.size(); i++) {
			for (unsigned int j = 0; j < table[0].size(); j++) {
				res[j][i] = table[i][j];
			}
		}
		return res;
	}

	matrix inversed() {
		unsigned int size_i = table.size();
		unsigned int size_j = table[0].size();

		fraction det = this->det();
		if (det.getNumerator() == 0) {
			cout << "Error. Determinant equals zero. Inversed matrix doesn't exist.\n";
			return matrix(size_i, size_j);
		}

		matrix res(size_i, size_j);
		int sign = 1;
		// составим матрицу миноров
		for (unsigned int i = 0; i < size_i; i++) {
			for (unsigned int j = 0; j < size_j; j++) {
				matrix temp = *this; // собираем матрицу для подсчёта минора Mij
				temp.table.erase(temp.table.begin() + i);
				for (unsigned int k = 0; k < size_i - 1; k++) {
					temp[k].erase(temp[k].begin() + j);
				}
				((i + j) % 2 == 0) ? sign = 1 : sign = -1;
				res[i][j] = sign * temp.det(); // записываем минор
			}
		}
		res = (1 / det) * res.transposed();
		return res;
	}

	fraction det() {
		unsigned int size_i = table.size();
		unsigned int size_j = table[0].size();
		if (size_i != size_j) {
			cout << "Error. Can not to find determinant due to M(" << size_i << ") doesn't match with N(" << size_j << ")\n";
			return 1;
		}
		if (size_i == 1) {
			return table[0][0];
		}
		else if (size_i == 2) {
			return table[0][0] * table[1][1] - table[0][1] * table[1][0];
		}
		else if (size_i == 3) {
			//	0----1----2     0----1----2
			//	|    |    |     |    |    |
			//	2----0----1  -  1----2----0
			//	|    |    |     |    |    |
			//	1----2----0     2----0----1
			fraction res =
				table[0][0] * table[1][1] * table[2][2]
				+ table[0][1] * table[1][2] * table[2][0]
				+ table[0][2] * table[1][0] * table[2][1]
				- table[0][0] * table[1][2] * table[2][1]
				- table[0][1] * table[1][0] * table[2][2]
				- table[0][2] * table[1][1] * table[2][0];
			res.simplify();
			return res;
		}
		else {
			fraction res = 0;
			int sign = 1;

			for (unsigned int k = 0; k < size_j; k++) {
				matrix m = *this;
				m.table.erase(m.table.begin()); // сборка матрицы под вычисление определителя
				for (unsigned int i = 0; i < size_i - 1; i++) {
					m.table[i].erase(m.table[i].begin() + k);
				}
				res += sign * table[0][k] * m.det();
				sign *= -1;
			}

			return res;
		}
	}

	vector<fraction>& operator[] (int index) {
		return table[index];
	}
	
};

#endif