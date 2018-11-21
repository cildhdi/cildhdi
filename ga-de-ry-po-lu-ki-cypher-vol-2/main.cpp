#include <string>
#include <igloo/igloo_alt.h>
#include <vector>
#include <map>
using namespace igloo;
//solution

#include <string>
using namespace std;
std::map<char, char> keys;
#define tsf(c) (c >= 'a' && c <= 'z' ? toupper(c) : tolower(c))
void set_key(const std::string& key)
{
	for (int i = 'a'; i <= 'z'; i++) keys[i] = i;
	for (int i = 'A'; i <= 'Z'; i++) keys[i] = i;
	for (int i = 0; i < key.size(); i += 2)
	{
		keys[key[i]] = key[i + 1];
		keys[key[i + 1]] = key[i];
		keys[tsf(key[i])] = tsf(key[i + 1]);
		keys[tsf(key[i + 1])] = tsf(key[i]);
	}
	keys[' '] = ' ';
}
string encode(string str, string key)
{
	set_key(key);
	for (auto& c : str) c = keys[c];
	return str;
}
string decode(string str, string key)
{
	return encode(str, key);
}

//test cases
#include <string>
#include <algorithm>
using namespace std;

int gp(char *array, size_t size, char c)
{
	char* end = array + size;
	char* match = std::find(array, end, c);
	return (end == match) ? -1 : (match - array);
}

string e(string str, string key)
{
	char *cypher = new char[key.length() * 2 + 1];
	strcpy(cypher, key.c_str());
	std::transform(key.begin(), key.end(), key.begin(), ::toupper);
	strcat(cypher, key.c_str());
	char* secret = new char[str.length() + 1];
	strcpy(secret, str.c_str());
	for (int i = 0; i < str.length(); i++)
	{
		int pos = gp(cypher, strlen(cypher), secret[i]);
		if (pos != -1)
			secret[i] = (pos % 2 == 1) ? cypher[pos - 1] : cypher[pos + 1];
	}
	return secret;
}

static const char alphanum[] =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";


Describe(ScoutsAreWaiting)
{
	It(BasicTest)
	{
		Assert::That(encode("Ala has a cat", "gaderypoluki"), Equals("Gug hgs g cgt"));
		Assert::That(decode("Gug hgs g cgt", "gaderypoluki"), Equals("Ala has a cat"));
		Assert::That(decode("Dkucr pu yhr ykbir", "politykarenu"), Equals("Dance on the table"));
		Assert::That(decode("Hide our beers", "regulaminowy"), Equals("Hmdr nge brres"));
		Assert::That(encode("ABCD", "gaderypoluki"), Equals("GBCE"));
		Assert::That(decode("GBCE", "gaderypoluki"), Equals("ABCD"));
		Assert::That(encode("gaderypoluki", "gaderypoluki"), Equals("agedyropulik"));
		Assert::That(decode("agedyropulik", "gaderypoluki"), Equals("gaderypoluki"));
	}

	It(RandomTest)
	{
		for (unsigned int j = 0; j < 100; j++)
		{
			string* keys = new string[5]{
			  "regulaminowy", "gaderypoluki", "politykarenu", "kaceminutowy", "koniecmatury" };
			string Str;
			for (unsigned int i = 0; i < 21; ++i)
			{
				Str += alphanum[rand() % (sizeof(alphanum) - 1)];
			}
			cout << endl << "Message: " << Str << endl << "Key: " << keys[j % 5] << endl <<
				" => Expected result: " << e(Str, keys[j % 5]) << endl;
			Assert::That(encode(Str, keys[j % 5]), Equals(e(Str, keys[j % 5])));
		}
	}
};

int main()
{
	return TestRunner::RunAllTests();
}