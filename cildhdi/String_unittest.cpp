#include <iostream>
#include <algorithm>
#include <string>
#include <gtest/gtest.h>
#include <random>
#include "String.h"
#pragma comment(lib,"gtestd.lib")

#define String String

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> int_dist(0, 100);
std::uniform_int_distribution<> char_dist(static_cast<int>(' '), static_cast<int>('}'));
const int lp = 50;
template<typename Char = char>
std::basic_string<Char> get_rand_str()
{
	std::basic_string<Char> str;
	int i = int_dist(gen);
	str.reserve(i);
	while (i--)
		str.push_back(char_dist(gen));
	return str;
}

namespace
{
	using namespace miles;
	TEST(String, Constructor)
	{
		{
			miles::String str;
			EXPECT_EQ(0, str.size());
			EXPECT_EQ(0, str.capacity());
			EXPECT_STREQ("", str.c_str().get());
		}

		{
			int i = lp;
			while (i--)
			{
				auto rstr = get_rand_str();
				miles::String str(rstr.c_str());
				EXPECT_STREQ(rstr.c_str(), str.c_str().get());
			}
		}

		{
			int i = lp;
			while (i--)
			{
				auto rstr = get_rand_str();
				std::uniform_int_distribution<> ld(0, rstr.size());
				size_t rl = ld(gen);
				miles::String str(rstr.c_str(), rl);
				EXPECT_STREQ(rstr.substr(0, rl).c_str(), str.c_str().get());
			}
		}

		{
			int i = lp;
			while (i--)
			{
				auto rstr = get_rand_str();
				miles::String str(rstr.c_str());
				EXPECT_STREQ(rstr.c_str(), str.c_str().get());
				miles::String s(std::move(str));
				EXPECT_STREQ(rstr.c_str(), s.c_str().get());
				EXPECT_STREQ("", str.c_str().get());
			}
		}
	}

	TEST(String, AtTest)
	{
		{
			int i = lp;
			while (i--)
			{
				std::string rstr = get_rand_str();
				if (rstr.size() < 2)continue;
				miles::String str = rstr.c_str();
				std::uniform_int_distribution<> ld(0, rstr.size() - 1);
				size_t index = ld(gen);
				char ch = char_dist(gen);
				rstr.at(index) = ch;
				str.at(index) = ch;
				EXPECT_STREQ(rstr.c_str(), str.c_str().get());
			}
		}
	}

	TEST(String, FrontTest)
	{
		{
			int i = lp;
			while (i--)
			{
				std::string rstr = get_rand_str();
				if (rstr.size() < 2)continue;
				miles::String str = rstr.c_str();
				std::uniform_int_distribution<> ld(0, rstr.size() - 1);
				size_t index = ld(gen);
				char ch = char_dist(gen);
				rstr.front() = ch;
				str.front() = ch;
				EXPECT_STREQ(rstr.c_str(), str.c_str().get());
			}
		}
	}

	TEST(String, BackTest)
	{
		{
			int i = lp;
			while (i--)
			{
				std::string rstr = get_rand_str();
				if (rstr.size() < 2)continue;
				miles::String str = rstr.c_str();
				std::uniform_int_distribution<> ld(0, rstr.size() - 1);
				size_t index = ld(gen);
				char ch = char_dist(gen);
				rstr.back() = ch;
				str.back() = ch;
				EXPECT_STREQ(rstr.c_str(), str.c_str().get());
			}
		}
	}

	TEST(String, CStrTest)
	{
		//has been tested above;
	}

	TEST(String, IteratorsTest)
	{
		{
			int i = lp;
			while (i--)
			{
				std::string rstr = get_rand_str();
				if (rstr.size() < 2)continue;
				miles::String str = rstr.c_str();
				std::uniform_int_distribution<> ld(0, rstr.size() - 1);
				size_t index = ld(gen);
				char ch = char_dist(gen);
				*rstr.begin() = ch;
				*str.begin() = ch;
				EXPECT_STREQ(rstr.c_str(), str.c_str().get());
			}
		}

		//std::reverse
		{
			int i = lp;
			while (i--)
			{
				std::string rstr = get_rand_str();
				miles::String str = rstr.c_str();
				std::reverse(rstr.begin(), rstr.end());
				std::reverse(str.begin(), str.end());
				EXPECT_STREQ(rstr.c_str(), str.c_str().get());
			}
		}

		//std::sort
		{
			int i = lp;
			while (i--)
			{
				std::string rstr = get_rand_str();
				miles::String str = rstr.c_str();
				std::sort(rstr.begin(), rstr.end());
				std::sort(str.begin(), str.end());
				EXPECT_STREQ(rstr.c_str(), str.c_str().get());
			}
		}
	}

	TEST(String, SizeTest)
	{
		{
			int i = lp;
			while (i--)
			{
				std::string rstr = get_rand_str();
				miles::String str = rstr.c_str();
				EXPECT_EQ(rstr.size(), str.size());
			}
		}
	}

	TEST(String, EmptyTest)
	{
		{
			int i = lp;
			while (i--)
			{
				std::string rstr = get_rand_str();
				miles::String str = rstr.c_str();
				EXPECT_EQ(rstr.empty(), str.empty());
			}
		}
	}

	TEST(String, ResizeTest)
	{
		{
			int i = lp;
			while (i--)
			{
				std::string rstr = get_rand_str();
				miles::String str = rstr.c_str();
				char ch = char_dist(gen);
				std::uniform_int_distribution<> rs(2, rstr.size() + 10);
				size_t ns = rs(gen);
				rstr.resize(ns, ch);
				str.resize(ns, ch);
				EXPECT_STREQ(rstr.c_str(), str.c_str().get());
			}
		}
	}

	TEST(String, ResetTest)
	{
		{
			int i = lp;
			while (i--)
			{
				std::string rstr = get_rand_str();
				if(rstr.size() < 2) continue;
				miles::String str = rstr.c_str();
				str.reset();
				EXPECT_EQ(0, str.size());
				EXPECT_EQ(0, str.capacity());
			}
		}
	}

	TEST(String, ClearTest)
	{
		{
			int i = lp;
			while (i--)
			{
				std::string rstr = get_rand_str();
				if (rstr.size() < 2) continue;
				miles::String str = rstr.c_str();
				EXPECT_NE(0, str.size());
				EXPECT_NE(0, str.capacity());
				str.clear();
				EXPECT_EQ(0, str.size());
				EXPECT_NE(0, str.capacity());
			}
		}
	}

	TEST(String, AppendTest)
	{

	}
} //namespace



int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	return 0;
}