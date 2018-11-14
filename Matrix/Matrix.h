
#ifndef _YL_MATRIX_H_
#define _YL_MATRIX_H_

#include <type_traits>
#include <cstring>
#include <cassert>
#include <vector>
#include <algorithm>
#include <stdexcept>

#pragma warning (disable:4290)

#define SASSERT(bool_constexpr, message) \
	static_assert(bool_constexpr, message)
#define MATRIX_SIZE_CHECK() \
	SASSERT(R == _R && C == _C, "Two matrices' row and column size must be the same")
#define ELEMENT_TYPE_CHECK(T) \
	SASSERT(std::is_arithmetic<T>::value, "Element type must be arithmetic.")
#define ROW_INDEX_CHECK(index) \
	if(index >= row_size()) \
		throw std::out_of_range("subscript out of range")
#define COLUMN_INDEX_CHECK(index) \
	if(index >= column_size()) \
		throw std::out_of_range("subscript out of range")
#define COMBINE_TYPE(T1, op, T2) \
	decltype(T1()  op  T2())

namespace cildhdi
{
	template<size_t R, size_t C, typename E = int>
	class Matrix
	{
	public:
		using ElementType = E;
		using ElementReferenceType = E & ;
		using Type = Matrix<R, C, E>;
		using ReferenceType = Matrix<R, C, E>&;
	private:
		ElementType _raw_data[R][C];
		const size_t _row_size = R;
		const size_t _column_size = C;
		const size_t _data_size = _row_size * _column_size * sizeof(ElementType);
	public: //constructors
		Matrix()
		{
			ELEMENT_TYPE_CHECK(ElementType);
			std::memset(_raw_data, 0, _data_size);
		}

		template<size_t _R, size_t _C, typename _E>
		Matrix(const Matrix<_R, _C, _E>& m)
		{
			ELEMENT_TYPE_CHECK(ElementType);
			MATRIX_SIZE_CHECK();
			for (size_t i = 0; i < _row_size; i++)
			{
				for (size_t j = 0; j < _column_size; j++)
				{
					_raw_data[i][j] = static_cast<ElementType>(m.at(i, j));
				}
			}
		}

		template<typename _E>
		Matrix(_E* data)
		{
			ELEMENT_TYPE_CHECK(ElementType);
			if (data == nullptr)
			{
				Matrix();
			}
			else
			{
				for (size_t i = 0; i < _row_size; i++)
				{
					for (size_t j = 0; j < _column_size; j++)
					{
						_raw_data[i][j] = static_cast<ElementType>(data[i][j]);
					}
				}
			}
		}

		template<typename _E>
		Matrix(const std::vector<std::vector<_E>>& vve)
		{
			ELEMENT_TYPE_CHECK(ElementType);
			try
			{
				data_from(vve);
			}
			catch (const std::exception& e)
			{
				throw e;
			}
		}

		template<typename _E>
		Matrix(const std::vector<_E>& ve)
		{
			ELEMENT_TYPE_CHECK(ElementType);
			try
			{
				data_from(ve);
			}
			catch (const std::exception& e)
			{
				throw e;
			}
		}
	public:
		size_t row_size()const
		{
			return _row_size;
		}

		size_t column_size()const
		{
			return _column_size;
		}

		size_t data_size()const
		{
			return _data_size;
		}

		ElementReferenceType at(size_t row, size_t column)
		{
			ROW_INDEX_CHECK(row);
			COLUMN_INDEX_CHECK(column);
			return _raw_data[row][column];
		}

		const ElementType at(size_t row, size_t column)const
		{
			ROW_INDEX_CHECK(row);
			COLUMN_INDEX_CHECK(column);
			ElementType e = _raw_data[row][column];
			return e;
		}

		template<typename _E>
		void data_from(const std::vector<std::vector<_E>>& vve)
		{
			ELEMENT_TYPE_CHECK(_E);
			if (_row_size != vve.size() || vve.size() == 0 || vve.at(0).size() != _column_size)
			{
				throw std::invalid_argument("size error");
			}
			for (size_t i = 0; i < _row_size; i++)
			{
				for (size_t j = 0; j < _column_size; j++)
				{
					_raw_data[i][j] = static_cast<ElementType>(vve[i][j]);
				}
			}
		}

		template<typename _E>
		void data_from(const std::vector<_E>& ve)
		{
			ELEMENT_TYPE_CHECK(_E);
			if (ve.size() < _row_size * _column_size)
			{
				throw std::invalid_argument("size error");
			}
			size_t t = 0;
			for (size_t i = 0; i < _row_size; i++)
			{
				for (size_t j = 0; j < _column_size; j++)
				{
					_raw_data[i][j] = static_cast<ElementType>(ve.at(t++));
				}
			}
		}

		void swap_row(size_t i, size_t j)
		{
			ROW_INDEX_CHECK(i);
			ROW_INDEX_CHECK(j);
			ElementType t;
			for (size_t column = 0; column < _column_size; column++)
			{
				t = _raw_data[i][column];
				_raw_data[i][column] = _raw_data[j][column];
				_raw_data[j][column] = t;
			}
		}

		void swap_column(size_t i, size_t j)
		{
			COLUMN_INDEX_CHECK(i);
			COLUMN_INDEX_CHECK(j);
			ElementType t;
			for (size_t row = 0; row < _row_size; row++)
			{
				t = _raw_data[row][i];
				_raw_data[row][i] = _raw_data[row][j];
				_raw_data[row][j] = t;
			}
		}

		ElementType max()const
		{
			ElementType me = _raw_data[0][0];
			for (size_t i = 0; i < _row_size; i++)
			{
				for (size_t j = 0; j < _column_size; j++)
				{
					if (me < _raw_data[i][j])
					{
						me = _raw_data[i][j];
					}
				}
			}
			return me;
		}

		ElementType min()const
		{
			ElementType me = _raw_data[0][0];
			for (size_t i = 0; i < _row_size; i++)
			{
				for (size_t j = 0; j < _column_size; j++)
				{
					if (me > _raw_data[i][j])
					{
						me = _raw_data[i][j];
					}
				}
			}
			return me;
		}

		Matrix<C, R, E> transpose()const
		{
			Matrix<C, R, E> m;
			for (size_t i = 0; i < m.row_size(); i++)
			{
				for (size_t j = 0; j < m.column_size(); j++)
				{
					m.at(i, j) = at(j, i);
				}
			}
			return m;
		}
	public: //operators
		ElementType* operator[](size_t row) 
		{
			if (row >= _row_size)
			{
				throw std::out_of_range("subscript out of range");
			}
			return _raw_data[row];
		}

		template<size_t _R, size_t _C, typename _E>
		bool operator==(const Matrix<_R, _C, _E>& rhs)const
		{
			if (R != _R || C != _C || (!std::is_same<E, _E>::value))
			{
				return false;
			}
			for (size_t i = 0; i < _row_size; i++)
			{
				for (size_t j = 0; j < _column_size; j++)
				{
					if (_raw_data[i][j] != rhs.at(i, j))
					{
						return false;
					}
				}
			}
			return true;
		}

		template<size_t _R, size_t _C, typename _E>
		bool operator!=(const Matrix<_R, _C, _E>& rhs)const
		{
			return !(*this == rhs);
		}

		template<typename _E>
		auto operator+(const Matrix<R, C, _E>& rhs)->Matrix<R, C, COMBINE_TYPE(E, +, _E)> const
		{
			Matrix<R, C, COMBINE_TYPE(E, +, _E)> m = *this;
			for (size_t i = 0; i < R; i++)
			{
				for (size_t j = 0; j < C; j++)
				{
					m.at(i, j) += rhs.at(i, j);
				}
			}
			return m;
		}

		template<typename _E>
		auto operator-(const Matrix<R, C, _E>& rhs)->Matrix<R, C, COMBINE_TYPE(E, +, _E)> const
		{
			Matrix<R, C, COMBINE_TYPE(E, +, _E)> m = *this;
			for (size_t i = 0; i < R; i++)
			{
				for (size_t j = 0; j < C; j++)
				{
					m.at(i, j) -= rhs.at(i, j);
				}
			}
			return m;
		}

		Type operator-()const
		{
			auto res = *this;
			for (size_t i = 0; i < _row_size; i++)
			{
				for (size_t j = 0; j < _column_size; j++)
				{
					res.at(i, j) = -res.at(i, j);
				}
			}
			return res;
		}



		template<size_t _R, size_t _C, typename _E>
		auto operator*(const Matrix<_R, _C, _E>& rhs)->Matrix<R, _C, COMBINE_TYPE(E, *, _E)> const
		{
			SASSERT(C == _R, "left matrix's column don't equal right matrix's row size");
			Matrix<R, _C, COMBINE_TYPE(E, *, _E)> m;
			for (size_t i = 0; i < m.row_size(); i++)
			{
				for (size_t j = 0; j < m.column_size(); j++)
				{
					typename decltype(m)::ElementType e = 0;
					for (size_t k = 0; k < column_size(); k++)
					{
						e += (at(i, k)*(rhs.at(k, j)));
					}
					m.at(i, j) = e;
				}
			}
			return m;
		}

		template<typename _E>
		auto operator/(_E rhs)->Matrix<R, C, COMBINE_TYPE(E, *, _E)> const
		{
			Matrix<R, C, COMBINE_TYPE(E, *, _E)> m = *this;
			for (size_t i = 0; i < R; i++)
			{
				for (size_t j = 0; j < C; j++)
				{
					m.at(i, j) /= rhs;
				}
			}
			return m;
		}

	};

}//namespace nsMatrix

#endif