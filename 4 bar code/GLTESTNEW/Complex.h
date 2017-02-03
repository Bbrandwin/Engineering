//#ifdef COMPLEXDLL_EXPORTS
#define COMPLEXDLL_API __declspec(dllexport) 
/*#else
#define COMPLEXDLL_API __declspec(dllimport) 
#endif*/

//   complex.h - declaration of class
//   of complex number
//
//   The code is property of LIBROW
//   You can use it on your own
//   When utilizing credit LIBROW site

#ifndef _COMPLEX_H_
#define _COMPLEX_H_

class complex
{
protected:
	//   Internal presentation - real and imaginary parts
	double m_re;
	double m_im;

public:
	//   Imaginary unity
	COMPLEXDLL_API static const complex i;
	COMPLEXDLL_API static const complex j;

	//   Constructors
	COMPLEXDLL_API complex(): m_re(0.), m_im(0.) {}
	COMPLEXDLL_API complex(double re, double im): m_re(re), m_im(im) {}
	COMPLEXDLL_API complex(double val): m_re(val), m_im(0.) {}

	//   Assignment
	COMPLEXDLL_API complex& operator= (const double val)
	{
		m_re = val;
		m_im = 0.;
		return *this;
	}

	//   Basic operations - taking parts
	COMPLEXDLL_API double re() const { return m_re; }
	COMPLEXDLL_API double im() const { return m_im; }

	//   Conjugate number
	COMPLEXDLL_API complex conjugate() const
	{
		return complex(m_re, -m_im);
	}

	//   Norm   
	COMPLEXDLL_API double norm() const
	{
		return m_re * m_re + m_im * m_im;
	}

	//   Arithmetic operations
	COMPLEXDLL_API complex operator+ (const complex& other) const
	{
		return complex(m_re + other.m_re, m_im + other.m_im);
	}

	COMPLEXDLL_API complex operator- (const complex& other) const
	{
		return complex(m_re - other.m_re, m_im - other.m_im);
	}

	COMPLEXDLL_API complex operator* (const complex& other) const
	{
		return complex(m_re * other.m_re - m_im * other.m_im,
			m_re * other.m_im + m_im * other.m_re);
	}

	COMPLEXDLL_API complex operator/ (const complex& other) const
	{
		const double denominator = other.m_re * other.m_re + other.m_im * other.m_im;
		return complex((m_re * other.m_re + m_im * other.m_im) / denominator,
			(m_im * other.m_re - m_re * other.m_im) / denominator);
	}

	COMPLEXDLL_API complex& operator+= (const complex& other)
	{
		m_re += other.m_re;
		m_im += other.m_im;
		return *this;
	}

	COMPLEXDLL_API complex& operator-= (const complex& other)
	{
		m_re -= other.m_re;
		m_im -= other.m_im;
		return *this;
	}

	COMPLEXDLL_API complex& operator*= (const complex& other)
	{
		const double temp = m_re;
		m_re = m_re * other.m_re - m_im * other.m_im;
		m_im = m_im * other.m_re + temp * other.m_im;
		return *this;
	}

	COMPLEXDLL_API complex& operator/= (const complex& other)
	{
		const double denominator = other.m_re * other.m_re + other.m_im * other.m_im;
		const double temp = m_re;
		m_re = (m_re * other.m_re + m_im * other.m_im) / denominator;
		m_im = (m_im * other.m_re - temp * other.m_im) / denominator;
		return *this;
	}

	COMPLEXDLL_API complex& operator++ ()
	{
		++m_re;
		return *this;
	}

	COMPLEXDLL_API complex operator++ (int)
	{
		complex temp(*this);
		++m_re;
		return temp;
	}

	COMPLEXDLL_API complex& operator-- ()
	{
		--m_re;
		return *this;
	}

	COMPLEXDLL_API complex operator-- (int)
	{
		complex temp(*this);
		--m_re;
		return temp;
	}

	COMPLEXDLL_API complex operator+ (const double val) const
	{
		return complex(m_re + val, m_im);
	}

	COMPLEXDLL_API complex operator- (const double val) const
	{
		return complex(m_re - val, m_im);
	}

	COMPLEXDLL_API complex operator* (const double val) const
	{
		return complex(m_re * val, m_im * val);
	}

	COMPLEXDLL_API complex operator/ (const double val) const
	{
		return complex(m_re / val, m_im / val);
	}

	COMPLEXDLL_API complex& operator+= (const double val)
	{
		m_re += val;
		return *this;
	}

	COMPLEXDLL_API complex& operator-= (const double val)
	{
		m_re -= val;
		return *this;
	}

	COMPLEXDLL_API complex& operator*= (const double val)
	{
		m_re *= val;
		m_im *= val;
		return *this;
	}

	COMPLEXDLL_API complex& operator/= (const double val)
	{
		m_re /= val;
		m_im /= val;
		return *this;
	}

	COMPLEXDLL_API friend complex operator+ (const double left, const complex& right)
	{
		return complex(left + right.m_re, right.m_im);
	}

	COMPLEXDLL_API friend complex operator- (const double left, const complex& right)
	{
		return complex(left - right.m_re, -right.m_im);
	}

	COMPLEXDLL_API friend complex operator* (const double left, const complex& right)
	{
		return complex(left * right.m_re, left * right.m_im);
	}

	COMPLEXDLL_API friend complex operator/ (const double left, const complex& right)
	{
		const double denominator = right.m_re * right.m_re + right.m_im * right.m_im;
		return complex(left * right.m_re / denominator,
			-left * right.m_im / denominator);
	}

	//   Boolean operators
	COMPLEXDLL_API bool operator== (const complex &other) const
	{
		return m_re == other.m_re && m_im == other.m_im;
	}

	COMPLEXDLL_API bool operator!= (const complex &other) const
	{
		return m_re != other.m_re || m_im != other.m_im;
	}

	COMPLEXDLL_API bool operator== (const double val) const
	{
		return m_re == val && m_im == 0.;
	}

	COMPLEXDLL_API bool operator!= (const double val) const
	{
		return m_re != val || m_im != 0.;
	}

	COMPLEXDLL_API friend bool operator== (const double left, const complex& right)
	{
		return left == right.m_re && right.m_im == 0.;
	}

	COMPLEXDLL_API friend bool operator!= (const double left, const complex& right)
	{
		return left != right.m_re || right.m_im != 0.;
	}
};

#endif