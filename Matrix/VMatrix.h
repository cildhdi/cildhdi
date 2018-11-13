#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

#pragma warning(disable:4290)


namespace nsMatrix
{
	template<typename _Ty>
	class Matrix
	{
	public:
		using value_type = _Ty;
		using value_reference = value_type & ;
		using matrix_type = Matrix<value_type>;
		using matrix_reference = matrix_type & ;
		using row_type = std::vector<value_type>;
		using row_reference = row_type & ;
	public:
		Matrix() {};
		Matrix(size_t row, size_t column);
		Matrix(std::vector<std::vector<value_type>> _vvT);
		Matrix(size_t row, size_t column, std::string str);
		template<typename Ty>Matrix(const Matrix<Ty>& mat);
		void init(std::vector<std::vector<value_type>> _vvT)throw(std::exception);
		size_t row_size()const;
		size_t column_size()const;
		value_reference at(size_t row, size_t column)throw(std::exception);
		template<typename _Fn> void for_each_ele(_Fn _Proc);
		template<typename _Fn> void for_each_row(_Fn _Proc);
		void swap_row(size_t i, size_t j)throw(std::exception);
		void swap_column(size_t i, size_t j)throw(std::exception);
		void remove_row(size_t row)throw(std::exception);
		void remove_column(size_t column)throw(std::exception);
		value_type max()const;
		value_type min()const;
		matrix_type transpose();
	public://²Ù×÷·û
		template<typename Ty> matrix_reference operator=(const Matrix<Ty>& matrix)const;
		matrix_reference operator-();
		row_reference operator[](size_t i)throw(std::exception);
		template<typename _Tn> void operator +=(_Tn rhs);
		template<typename _Tn> void operator -=(_Tn rhs);
		template<typename _Tn> void operator *=(_Tn rhs);
		template<typename _Tn> void operator /=(_Tn rhs)throw(std::exception);

	private:
		std::vector<row_type> _matrix;
	};
}	//namespace nsMatrix


namespace nsMatrix
{

	template<typename _Ty>
	Matrix<_Ty>::Matrix(size_t row, size_t column)
	{
		for (size_t i = 0; i < row; i++)
		{
			_matrix.push_back(std::vector<_Ty>(column, 0));
		}
	}

	template<typename _Ty>
	Matrix<_Ty>::Matrix(std::vector<std::vector<value_type>> _vvT)
	{
		Matrix();
		init(_vvT);
	}

	template<typename _Ty>
	Matrix<_Ty>::Matrix(size_t row, size_t column, std::string str)
	{
		for (auto c : str)
		{
			if (!(c == ' ' || (c >= '0' && c <= '9')))
				throw std::invalid_argument("invalid_argument");
		}
		std::istringstream iss;
		iss.str(str);
		std::vector<std::vector<_Ty>> _vvT;
		_Ty _Ele = _Ty();
		for (size_t i = 0; i < row; i++)
		{
			std::vector<_Ty> _vT;
			for (size_t j = 0; j < column; j++)
			{
				iss >> _Ele;
				_vT.push_back(_Ele);
			}
			_vvT.push_back(_vT);
		}
		init(_vvT);
	}

	template<typename _Ty>
	template<typename Ty>
	Matrix<_Ty>::Matrix(const Matrix<Ty>& mat)
	{
		Matrix(mat.row_size(), mat.column_size());
		for (size_t i = 0; i < row_size(); i++)
		{
			for (size_t j = 0; j < column_size(); j++)
			{
				at(i, j) = const_cast<Matrix<Ty>&>(mat).at(i, j);
			}
		}
	}


	template<typename _Ty>
	void Matrix<_Ty>::init(std::vector<std::vector<value_type>> _vvT)throw(std::exception)
	{
		if (_vvT.empty())
			throw std::domain_error("empty matrix");
		size_t size = _vvT.at(0).size();
		std::for_each(_vvT.begin(), _vvT.end(), [&](std::vector<_Ty> _vT)
		{
			if (_vT.size() != size)
				throw std::domain_error("not a matrix");
		});
		_matrix = _vvT;
	}

	template<typename _Ty>
	size_t Matrix<_Ty>::row_size()const
	{
		return _matrix.size();
	}

	template<typename _Ty>
	size_t Matrix<_Ty>::column_size()const
	{
		if (_matrix.empty())
			return 0;
		return _matrix.at(0).size();
	}

	template<typename _Ty>
	auto Matrix<_Ty>::at(size_t row, size_t column)throw(std::exception)->value_reference
	{
		if (!(row >= 0 && column >= 0 && row < row_size() && column < column_size()))
			throw std::out_of_range("out of range");
		return _matrix.at(row).at(column);
	}

	template<typename _Ty>
	auto Matrix<_Ty>::operator[](size_t i)throw(std::exception)->row_reference
	{
		return _matrix[i];
	}

	template<typename _Ty>
	template<typename _Fn>
	void Matrix<_Ty>::for_each_ele(_Fn _Func)
	{
		for (size_t i = 0; i < row_size(); i++)
		{
			for (size_t j = 0; j < column_size(); j++)
			{
				_Func(at(i, j));
			}
		}
	}

	template<typename _Ty>
	template<typename _Fn>
	void Matrix<_Ty>::for_each_row(_Fn _Func)
	{
		for (size_t i = 0; i < row_size(); i++)
		{
			_Func(_matrix.at(i));
		}
	}

	template<typename _Ty>
	void Matrix<_Ty>::swap_row(size_t i, size_t j)throw(std::exception)
	{
		if (!(i < row_size() && j < row_size()))
			throw std::out_of_range();
		std::vector<_Ty> _vT(_matrix.at(i));
		_matrix.at(i) = _matrix.at(j);
		_matrix.at(j) = _vT;
	}

	template<typename _Ty>
	void Matrix<_Ty>::swap_column(size_t i, size_t j)throw(std::exception)
	{
		if (!(i < column_size() && j < column_size()))
			throw std::out_of_range();
		_Ty _TempEle;
		for_each_row([&_TempEle, i, j](std::vector<_Ty>& _vT)
		{
			_TempEle = _vT.at(i);
			_vT.at(i) = _vT.at(j);
			_vT.at(j) = _TempEle;
		});
	}

	template<typename _Ty>
	auto Matrix<_Ty>::transpose()->matrix_type
	{
		Matrix<_Ty> matrix(column_size(), row_size());
		for (size_t i = 0; i < matrix.row_size(); i++)
		{
			for (size_t j = 0; j < matrix.column_size(); j++)
			{
				matrix.at(i, j) = at(j, i);
			}
		}
		return matrix;
	}


	template<typename _Ty>
	void Matrix<_Ty>::remove_row(size_t row)throw(std::exception)
	{
		if (row >= row_size())
		{
			throw std::out_of_range("out_of_range");
		}
		auto it = _matrix.begin();
		while (row--) it++;
		try
		{
			_matrix.erase(it);
		}
		catch (...)
		{
			throw;
		}
	}

	template<typename _Ty>
	void Matrix<_Ty>::remove_column(size_t column)throw(std::exception)
	{
		unsigned int c;
		for (auto& ve : _matrix)
		{
			c = column;
			auto it = ve.begin();
			while (c--)it++;
			try
			{
				ve.erase(it);
			}
			catch (...)
			{
				throw;
			}
		}
	}

	template<typename _Ty>
	auto Matrix<_Ty>::max()const->value_type
	{
		if (_matrix.empty)
		{
			throw std::domain_error("empty matrix");
		}
		try
		{
			value_type mv = at(0, 0);
			for (auto& vt : _matrix)
			{
				for (auto& t : vt)
				{
					if (t > mv)
						mv = t;
				}
			}
			return mv;
		}
		catch (...)
		{
			throw;
		}
	}

	template<typename _Ty>
	auto Matrix<_Ty>::min()const->value_type
	{
		if (_matrix.empty)
		{
			throw std::domain_error("empty matrix");
		}
		try
		{
			value_type mv = at(0, 0);
			for (auto& vt : _matrix)
			{
				for (auto& t : vt)
				{
					if (t < mv)
						mv = t;
				}
			}
			return mv;
		}
		catch (...)
		{
			throw;
		}
	}


	template<typename _Ty1, typename _Ty2>
	bool operator==(const Matrix<_Ty1>& lhs, const Matrix<_Ty2>& rhs)
	{
		if ((lhs.row_size() != rhs.row_size()) || (lhs.column_size() != rhs.column_size()))
			return false;
		bool ret = true;
		for (unsigned int i = 0; i < lhs.row_size(); i++)
		{
			for (unsigned int j = 0; j < lhs.column_size(); j++)
			{
				if (lhs.at(i, j) != rhs.at(i, j))
				{
					ret = false;
					break;
				}
				if (!ret)
					break;
			}
		}
		return ret;
	}

	template<typename _Ty1, typename _Ty2>
	bool operator!=(const Matrix<_Ty1>& lhs, const Matrix<_Ty2>& rhs)
	{
		return !(lhs == rhs);
	}

	template<typename _Ty>
	template<typename Ty>
	auto Matrix<_Ty>::operator=(const Matrix<Ty>& matrix)const->matrix_reference
	{
		for (unsigned int i = 0; i < lhs.row_size(); i++)
		{
			for (unsigned int j = 0; j < lhs.column_size(); j++)
			{
				matrix.at(i, j) = rhs.at(i, j);
			}
		}
		return *this;
	}

	template<typename _Ty1, typename _Ty2>
	auto operator+(const Matrix<_Ty1>& lhs, const Matrix<_Ty2>& rhs)->Matrix<decltype(_Ty1() + _Ty2())>
	{
		Matrix<decltype(_Ty1() + _Ty2())> matrix;
		matrix = lhs;
		if ((lhs.row_size() != rhs.row_size()) || (lhs.column_size() != rhs.column_size()))
			throw std::invalid_argument("matrices have different row and column size");
		for (unsigned int i = 0; i < lhs.row_size(); i++)
		{
			for (unsigned int j = 0; j < lhs.column_size(); j++)
			{
				matrix.at(i, j) += rhs.at(i, j);
			}
		}
		return matrix;
	}

	template<typename _Ty>
	auto Matrix<_Ty>::operator-()->matrix_reference
	{
		for_each_ele([](value_reference _Ele) { _Ele = -_Ele; });
		return *this;
	}

	template<typename _Ty1, typename _Ty2>
	auto operator-(const Matrix<_Ty1>& lhs, const Matrix<_Ty2>& rhs)->Matrix<decltype(_Ty1() + _Ty2())>
	{
		Matrix<decltype(_Ty1() + _Ty2())> matrix;
		matrix = lhs + (-rhs);
		return matrix;
	}

	template<typename _Ty, typename _Tn>
	auto operator*(const Matrix<_Ty>& lhs, _Tn rhs)->Matrix<decltype(_Ty() * _Tn())>
	{
		using element_type = decltype(_Ty()*_Tn());
		std::vector<std::vector<element_type>> vve;
		const_cast<Matrix<_Ty>&>(lhs).for_each_row([&](const std::vector<_Ty>& row)
		{
			std::vector<element_type> ve;
			for (const element_type e : row)
			{
				ve.push_back(e * rhs);
			}
			vve.push_back(ve);
		});
		return Matrix<element_type>(vve);
	}

	template<typename _Ty, typename _Tn>
	auto operator*(_Tn lhs, const Matrix<_Ty>& rhs)->Matrix<decltype(_Ty() * _Tn())>
	{
		return rhs * lhs;
	}

	template<typename _Ty, typename _Tn>
	auto operator+(const Matrix<_Ty>& lhs, _Tn rhs)->Matrix<decltype(_Ty() + _Tn())>
	{
		Matrix<decltype(_Ty() + _Tn())> mat(lhs);
		mat.for_each_ele([&](_Ty& e)
		{
			e += rhs;
		});
		return mat;
	}

	template<typename _Ty, typename _Tn>
	auto operator+(_Tn lhs, const Matrix<_Ty>& rhs)->Matrix<decltype(_Ty() + _Tn())>
	{
		return rhs + lhs;
	}

	template<typename _Ty, typename _Tn>
	auto operator-(const Matrix<_Ty>& lhs, _Tn rhs)->Matrix<decltype(_Ty() - _Tn())>
	{
		Matrix<decltype(_Ty() - _Tn())> mat(lhs);
		mat.for_each_ele([&](_Ty& e)
		{
			e -= rhs;
		});
		return mat;
	}

	template<typename _Ty, typename _Tn>
	auto operator-(_Tn lhs, const Matrix<_Ty>& rhs)->Matrix<decltype(_Ty() - _Tn())>
	{
		return (-rhs) + lhs;
	}

	template<typename _Ty, typename _Tn>
	auto operator/(const Matrix<_Ty>& lhs, _Tn rhs)->Matrix<decltype(_Ty() / static_cast<_Tn>(1))>
	{
		Matrix<decltype(_Ty() / static_cast<_Tn>(1))> mat(lhs);
		mat.for_each_ele([&](_Ty& e)
		{
			e /= rhs;
		});
		return mat;
	}

	template<typename _Ty, typename _Tn>
	auto operator/(_Tn lhs, const Matrix<_Ty>& rhs)->Matrix<decltype(_Tn() / static_cast<_Ty>(1))>
	{
		Matrix<decltype(_Tn() / static_cast<_Ty>(1))> mat(rhs);
		mat.for_each_ele([&](_Ty& e)
		{
			e = lhs / e;
		});
		return mat;
	}

	template<typename _Ty1, typename _Ty2>
	auto operator*(const Matrix<_Ty1>& lhs, const Matrix<_Ty2>& rhs)throw(std::exception)->Matrix<decltype(_Ty1()*_Ty2())>
	{
		if (lhs.column_size() != rhs.row_size())
			throw std::invalid_argument("left matrix's column don't equal right matrix's row size");
		Matrix<decltype(_Ty1()*_Ty2())> matrix(lhs.row_size(), rhs.column_size());
		for (size_t i = 0; i < matrix.row_size(); i++)
		{
			for (size_t j = 0; j < matrix.column_size(); j++)
			{
				typename decltype(matrix)::value_type _Ele = 0;
				for (size_t k = 0; k < lhs.column_size(); k++)
				{
					_Ele += (const_cast<Matrix<_Ty1>&>(lhs).at(i, k)*const_cast<Matrix<_Ty2>&>(rhs).at(k, j));
				}
				matrix.at(i, j) = _Ele;
			}
		}
		return matrix;
	}

	template<typename _Ty>
	std::ostream& operator<<(std::ostream& os, const Matrix<_Ty>& matrix)
	{
		const_cast<Matrix<_Ty>&>(matrix).for_each_row([](const std::vector<_Ty>& vi)
		{
			for (_Ty i : vi)
			{
				std::cout << i << " ";
			}
			std::cout << std::endl;
		});
		return os;
	}

	template<typename _Ty>
	template<typename _Tn>
	void Matrix<_Ty>::operator+=(_Tn rhs)
	{
		for_each_ele([&](value_reference ve)
		{
			ve += rhs;
		});
	}

	template<typename _Ty>
	template<typename _Tn>
	void Matrix<_Ty>::operator-=(_Tn rhs)
	{
		for_each_ele([&](value_reference ve)
		{
			ve -= rhs;
		});
	}

	template<typename _Ty>
	template<typename _Tn>
	void Matrix<_Ty>::operator*=(_Tn rhs)
	{
		for_each_ele([&](value_reference ve)
		{
			ve *= rhs;
		});
	}

	template<typename _Ty>
	template<typename _Tn>
	void Matrix<_Ty>::operator/=(_Tn rhs)throw(std::exception)
	{
		if (rhs == 0)
		{
			throw std::runtime_error();
		}
		for_each_ele([&](value_reference ve)
		{
			ve /= rhs;
		});
	}

	template <typename _Ty>
	Matrix<_Ty> pow(const Matrix<_Ty>& matrix, unsigned int y)throw(std::exception)
	{
		if (0 == y)
			throw std::invalid_argument();
		Matrix<_Ty> mat(matrix);
		for (unsigned int j = y; j > 1; j--)
		{
			mat = mat * matrix;
		}
		return mat;
	}
}	//namespace nsMatrix

#endif

