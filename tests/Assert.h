//
// Created by masy on 07.02.20.
//

#ifndef TALESOFCATVENTURE_ASSERT_H
#define TALESOFCATVENTURE_ASSERT_H

#include <stdexcept>
#include <cmath>
#include <functional>

namespace ASSERT
{
	inline static void TRUE(const bool a)
	{
		if (!a)
		{
			throw std::runtime_error(
					std::string("Error in File ")
					+ std::string(__FILE__)
					+ std::string(" in function ")
					+ std::string(__PRETTY_FUNCTION__)
					+ std::string(" (L ")
					+ std::to_string(__LINE__)
					+ std::string("): ")
					+ std::to_string(a)
					+ std::string(" is not true!"));
		}
	}

	inline static void FALSE(const bool a)
	{
		if (a)
		{
			throw std::runtime_error(
					std::string("Error in File ")
					+ std::string(__FILE__)
					+ std::string(" in function ")
					+ std::string(__PRETTY_FUNCTION__)
					+ std::string(" (L ")
					+ std::to_string(__LINE__)
					+ std::string("): ")
					+ std::to_string(a)
					+ std::string(" is not false!"));
		}
	}

	inline static void EQUALS(const bool a, const bool b)
	{
		if (a != b)
		{
			throw std::runtime_error(
					std::string("Error in File ")
					+ std::string(__FILE__)
					+ std::string(" in function ")
					+ std::string(__PRETTY_FUNCTION__)
					+ std::string(" (L ")
					+ std::to_string(__LINE__)
					+ std::string("): ")
					+ std::to_string(a)
					+ std::string(" does not equal ")
					+ std::to_string(b)
					+ std::string("!"));
		}
	}

	inline static void EQUALS(const char a, const char b)
	{
		if (a != b)
		{
			throw std::runtime_error(
					std::string("Error in File ")
					+ std::string(__FILE__)
					+ std::string(" in function ")
					+ std::string(__PRETTY_FUNCTION__)
					+ std::string(" (L ")
					+ std::to_string(__LINE__)
					+ std::string("): ")
					+ std::to_string(a)
					+ std::string(" does not equal ")
					+ std::to_string(b)
					+ std::string("!"));
		}
	}

	inline static void EQUALS(const unsigned char a, const unsigned char b)
	{
		if (a != b)
		{
			throw std::runtime_error(
					std::string("Error in File ")
					+ std::string(__FILE__)
					+ std::string(" in function ")
					+ std::string(__PRETTY_FUNCTION__)
					+ std::string(" (L ")
					+ std::to_string(__LINE__)
					+ std::string("): ")
					+ std::to_string(a)
					+ std::string(" does not equal ")
					+ std::to_string(b)
					+ std::string("!"));
		}
	}

	inline static void EQUALS(const short a, const short b)
	{
		if (a != b)
		{
			throw std::runtime_error(
					std::string("Error in File ")
					+ std::string(__FILE__)
					+ std::string(" in function ")
					+ std::string(__PRETTY_FUNCTION__)
					+ std::string(" (L ")
					+ std::to_string(__LINE__)
					+ std::string("): ")
					+ std::to_string(a)
					+ std::string(" does not equal ")
					+ std::to_string(b)
					+ std::string("!"));
		}
	}

	inline static void EQUALS(const unsigned short a, const unsigned short b)
	{
		if (a != b)
		{
			throw std::runtime_error(
					std::string("Error in File ")
					+ std::string(__FILE__)
					+ std::string(" in function ")
					+ std::string(__PRETTY_FUNCTION__)
					+ std::string(" (L ")
					+ std::to_string(__LINE__)
					+ std::string("): ")
					+ std::to_string(a)
					+ std::string(" does not equal ")
					+ std::to_string(b)
					+ std::string("!"));
		}
	}

	inline static void EQUALS(const int a, const int b)
	{
		if (a != b)
		{
			throw std::runtime_error(
					std::string("Error in File ")
					+ std::string(__FILE__)
					+ std::string(" in function ")
					+ std::string(__PRETTY_FUNCTION__)
					+ std::string(" (L ")
					+ std::to_string(__LINE__)
					+ std::string("): ")
					+ std::to_string(a)
					+ std::string(" does not equal ")
					+ std::to_string(b)
					+ std::string("!"));
		}
	}

	inline static void EQUALS(const unsigned int a, const unsigned int b)
	{
		if (a != b)
		{
			throw std::runtime_error(
					std::string("Error in File ")
					+ std::string(__FILE__)
					+ std::string(" in function ")
					+ std::string(__PRETTY_FUNCTION__)
					+ std::string(" (L ")
					+ std::to_string(__LINE__)
					+ std::string("): ")
					+ std::to_string(a)
					+ std::string(" does not equal ")
					+ std::to_string(b)
					+ std::string("!"));
		}
	}

	inline static void EQUALS(const long a, const long b)
	{
		if (a != b)
		{
			throw std::runtime_error(
					std::string("Error in File ")
					+ std::string(__FILE__)
					+ std::string(" in function ")
					+ std::string(__PRETTY_FUNCTION__)
					+ std::string(" (L ")
					+ std::to_string(__LINE__)
					+ std::string("): ")
					+ std::to_string(a)
					+ std::string(" does not equal ")
					+ std::to_string(b)
					+ std::string("!"));
		}
	}

	inline static void EQUALS(const unsigned long a, const unsigned long b)
	{
		if (a != b)
		{
			throw std::runtime_error(
					std::string("Error in File ")
					+ std::string(__FILE__)
					+ std::string(" in function ")
					+ std::string(__PRETTY_FUNCTION__)
					+ std::string(" (L ")
					+ std::to_string(__LINE__)
					+ std::string("): ")
					+ std::to_string(a)
					+ std::string(" does not equal ")
					+ std::to_string(b)
					+ std::string("!"));
		}
	}

	inline static void EQUALS(const long long a, const long long b)
	{
		if (a != b)
		{
			throw std::runtime_error(
					std::string("Error in File ")
					+ std::string(__FILE__)
					+ std::string(" in function ")
					+ std::string(__PRETTY_FUNCTION__)
					+ std::string(" (L ")
					+ std::to_string(__LINE__)
					+ std::string("): ")
					+ std::to_string(a)
					+ std::string(" does not equal ")
					+ std::to_string(b)
					+ std::string("!"));
		}
	}

	inline static void EQUALS(const unsigned long long int a, const unsigned long long int b)
	{
		if (a != b)
		{
			throw std::runtime_error(
					std::string("Error in File ")
					+ std::string(__FILE__)
					+ std::string(" in function ")
					+ std::string(__PRETTY_FUNCTION__)
					+ std::string(" (L ")
					+ std::to_string(__LINE__)
					+ std::string("): ")
					+ std::to_string(a)
					+ std::string(" does not equal ")
					+ std::to_string(b)
					+ std::string("!"));
		}
	};

	inline static void EQUALS(const float a, const float b, const float delta)
	{
		float d = std::abs(b - a);
		if (d >= delta)
		{
			throw std::runtime_error(
					std::string("Error in File ")
					+ std::string(__FILE__)
					+ std::string(" in function ")
					+ std::string(__PRETTY_FUNCTION__)
					+ std::string(" (L ")
					+ std::to_string(__LINE__)
					+ std::string("): ")
					+ std::to_string(a)
					+ std::string(" does not equal ")
					+ std::to_string(b)
					+ std::string("!"));
		}
	};

	inline static void EQUALS(const double a, const double b, const double delta)
	{
		double d = std::abs(b - a);
		if (d >= delta)
		{
			throw std::runtime_error(
					std::string("Error in File ")
					+ std::string(__FILE__)
					+ std::string(" in function ")
					+ std::string(__PRETTY_FUNCTION__)
					+ std::string(" (L ")
					+ std::to_string(__LINE__)
					+ std::string("): ")
					+ std::to_string(a)
					+ std::string(" does not equal ")
					+ std::to_string(b)
					+ std::string("!"));
		}
	};

	inline static void EQUALS(const long double a, const long double b, const long double delta)
	{
		long double d = std::abs(b - a);
		if (d >= delta)
		{
			throw std::runtime_error(
					std::string("Error in File ")
					+ std::string(__FILE__)
					+ std::string(" in function ")
					+ std::string(__PRETTY_FUNCTION__)
					+ std::string(" (L ")
					+ std::to_string(__LINE__)
					+ std::string("): ")
					+ std::to_string(a)
					+ std::string(" does not equal ")
					+ std::to_string(b)
					+ std::string("!"));
		}
	};

	template <typename t>
	inline static void THROW(std::function<void()> _function)
	{
		try {
			_function();
		}
		catch (t &ex)
		{
			return;
		}

		throw std::runtime_error(
				std::string("Error in File ")
				+ std::string(__FILE__)
				+ std::string(" in function ")
				+ std::string(__PRETTY_FUNCTION__)
				+ std::string(" (L ")
				+ std::to_string(__LINE__)
				+ std::string("): Function did not throw the desired exception!"));
	}
};

#endif //TALESOFCATVENTURE_ASSERT_H
