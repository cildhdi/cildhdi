#include "LinkList.h"
#include <vector>

int main()
{
	using namespace ll;
	using List = LinkList<int>;
	{
		List list;
	}

	{
		List list(4);
	}

	{
		List list(4, 4);
	}

	{
		List list = { 1,2,3,4 };
	}

	{
		List list = { 1,2,3,4 };
		List copy(list);
	}

	{
		List list = { 1,2,3,4 };
		List copy(std::move(list));
	}

	{
		struct complex
		{
			int _a, _b;
			complex(int a, int b) :_a(a), _b(b) {}
			complex() {}
		};
		LinkList<complex> list;
		list.emplace_front(1, 2);
		list.emplace_front(3, 4);
		list.emplace_front(5, 6);
	}

	{
		List list = { 1,2,3,4,5,6,7,8 };
		list.erase_after(list.begin(), list.end());
	}

	{
		List list = { 1,2,3,4,5,6,7,8,9 };
		list.resize(5);
	}

	{
		List list = { 1,2,3,4 }, other = { 5,6,7,8 };
		list.splice_after(list.begin(), other);
		list.remove_if([](const int& i) { return i >= 7; });
	}

	{
		List list = { 44,35,5,67,878,8 };
		list.sort(std::less<int>());
	}

	{
		List list = { 1,1,2,3,4,4,5,5,5 };
		list.unique();
		list.clear();
	}
	return 0;
}