#include <iostream>
#include <algorithm>
#include <string>
#include <gtest/gtest.h>
#include <random>
#include <thread>
#include <chrono>
#include "String.h"

#ifdef _DEBUG
#pragma comment(lib,"gtestd.lib")
#else
#pragma comment(lib,"gtest.lib")
#endif // DEBUG

#define String String
//loop time
constexpr int lp = 50;

//random
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> int_dist(0, 100);
std::uniform_int_distribution<> char_dist(static_cast<int>(' '), static_cast<int>('}'));

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
	using namespace cl;

	TEST(String, Constructor)
	{
		{
			cl::String str;
			EXPECT_EQ(0, str.size());
			EXPECT_EQ(0, str.capacity());
			EXPECT_STREQ("", str.c_str().get());
		}

		{
			int i = lp;
			while (i--)
			{
				auto rstr = get_rand_str();
				cl::String str(rstr.c_str());
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
				cl::String str(rstr.c_str(), rl);
				EXPECT_STREQ(rstr.substr(0, rl).c_str(), str.c_str().get());
			}
		}

		{
			int i = lp;
			while (i--)
			{
				auto rstr = get_rand_str();
				cl::String str(rstr.c_str());
				EXPECT_STREQ(rstr.c_str(), str.c_str().get());
				cl::String s(std::move(str));
				EXPECT_STREQ(rstr.c_str(), s.c_str().get());
				EXPECT_STREQ("", str.c_str().get());
			}
		}

		{

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
				cl::String str = rstr.c_str();
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
				cl::String str = rstr.c_str();
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
				cl::String str = rstr.c_str();
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
				cl::String str = rstr.c_str();
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
				cl::String str = rstr.c_str();
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
				cl::String str = rstr.c_str();
				std::sort(rstr.begin(), rstr.end());
				std::sort(str.begin(), str.end());
				EXPECT_STREQ(rstr.c_str(), str.c_str().get());
			}
		}

		//for_each
		{
			int i = lp;
			while (i--)
			{
				std::string rstr = get_rand_str();
				cl::String str = rstr.c_str();
				std::for_each(str.begin(), str.end(), [](char& c)
				{
					c++;
				});
				std::for_each(rstr.begin(), rstr.end(), [](char& c)
				{
					c++;
				});
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
				cl::String str = rstr.c_str();
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
				cl::String str = rstr.c_str();
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
				cl::String str = rstr.c_str();
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
				if (rstr.size() < 2) continue;
				cl::String str = rstr.c_str();
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
				cl::String str = rstr.c_str();
				EXPECT_NE(0, str.size());
				EXPECT_NE(0, str.capacity());
				str.clear();
				EXPECT_EQ(0, str.size());
				EXPECT_NE(0, str.capacity());
			}
		}
	}


	TEST(String, FindTest)
	{
		{
			int i = lp;
			while (i--)
			{
				cl::String str("0123456");
				for (size_t j = 0; j < 7; j++)
				{
					EXPECT_EQ(j, str.find(std::to_string(j).c_str()));
				}
				EXPECT_EQ(str.npos, str.find("7"));
				EXPECT_EQ(str.npos, str.find("787"));
				EXPECT_EQ(str.npos, str.find("fs23"));
			}
		}
	}


	TEST(String, SplitTest)
	{
		{
			WString str = L"A bird came down the walk";
			auto vs = str.split(L" ");
		}
	}

	TEST(String, ToTest)
	{
		{
			String str = "47.328";
			EXPECT_DOUBLE_EQ(47.328, str.to<long double>());
		}
	}

	TEST(String, InsertTest)
	{
		{
			WString s = L"01234567";
			WString s1 = L"kkkkk";
			s.insert(s.begin(), 1, 'c');
		}
	}

	TEST(String, EraseTest)
	{
		{
			String s = "9087654321";
			s.erase(std::remove_if(s.begin(), s.end(), std::bind2nd(std::greater<char>(), '5')), s.end());
		}
	}

	TEST(String, CopyTest)
	{
		{
			String s = "0123456789";
			char buf[11] = { 0 };
			s.copy(buf, 10);
			std::cout << buf << std::endl;
		}
	}
} //namespace
String s = "01234567890123456789\n";
void print()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	std::cout << s;
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}