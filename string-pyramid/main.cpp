//for test framework
#include <igloo/igloo_alt.h>
using namespace igloo;

//solution

#include <cmath>
std::string nc(char c, size_t n)
{
    std::string s;
    while (n--)
        s += c;
    return s;
}

std::string watchPyramidFromTheSide(std::string characters)
{
    if (characters.empty())
        return "";
    std::string res;
    int num = 1, len = characters.size() * 2 - 1;
    for (auto it = characters.rbegin(); it != characters.rend(); it++, num += 2)
    {
        res += nc(' ', (len - num) / 2);
        res += nc(*it, num);
        res += nc(' ', (len - num) / 2);
        res += '\n';
    }
    res.pop_back();
    return res;
}

std::string watchPyramidFromAbove(std::string characters)
{
    if (characters.empty())
        return "";
    int len = characters.size() * 2 - 1;
    std::vector<std::vector<char>> mp(len, std::vector<char>(len, ' '));
    for (int i = 0; i < len; i++)
        for (int j = 0; j < len; j++)
            mp[i][j] = characters[std::min({i, j, len - i - 1, len - j - 1})];
    std::string s;
    for (auto &vc : mp)
    {
        for (auto c : vc)
            s += c;
        s += '\n';
    }
    s.pop_back();
    return s;
}

int countVisibleCharactersOfThePyramid(std::string characters)
{
    if (characters.empty())
        return -1;
    return std::pow(characters.size() * 2 - 1, 2);
}

int countAllCharactersOfThePyramid(std::string characters)
{
    if (characters.empty())
        return -1;
    int sum = 0, i = characters.size() + 1;
    while (--i)
        sum += std::pow(i * 2 - 1, 2);
    return sum;
}

//test cases
#include <algorithm>
#include <math.h>
#include <functional>
#include <string>
#include <ctime>

Describe(Test){
    It(_0_EmptyTest){
        Assert::That(watchPyramidFromTheSide(""), Is().EqualTo(""));
Assert::That(watchPyramidFromAbove(""), Is().EqualTo(""));
Assert::That(countVisibleCharactersOfThePyramid(""), Is().EqualTo(-1));
Assert::That(countAllCharactersOfThePyramid(""), Is().EqualTo(-1));
}

It(_1_ExampleTest1)
{
    std::string testCharacters = "*#";

    // Test FromSide
    std::string expectedWatchFromSide = " # \n***";
    std::string actualWatchFromSide = watchPyramidFromTheSide(testCharacters);

    Assert::That("\n" + actualWatchFromSide, Is().EqualTo("\n" + expectedWatchFromSide));

    // Test FromAbove
    std::string expectedWatchFromAbove = "***\n*#*\n***";
    std::string actualWatchFromAbove = watchPyramidFromAbove(testCharacters);

    Assert::That("\n" + actualWatchFromAbove, Is().EqualTo("\n" + expectedWatchFromAbove));

    // Test CountVisibleCharacters
    Assert::That(countVisibleCharactersOfThePyramid(testCharacters), Is().EqualTo(9));

    // Test CountAllCharacters
    Assert::That(countAllCharactersOfThePyramid(testCharacters), Is().EqualTo(10));
}

It(_2_ExampleTest2)
{
    std::string testCharacters = "abc";

    // Test FromSide
    std::string expectedWatchFromSide = "  c  \n bbb \naaaaa";
    std::string actualWatchFromSide = watchPyramidFromTheSide(testCharacters);

    Assert::That("\n" + actualWatchFromSide, Is().EqualTo("\n" + expectedWatchFromSide));

    //Test FromAbove
    std::string expectedWatchFromAbove = "aaaaa\nabbba\nabcba\nabbba\naaaaa";
    std::string actualWatchFromAbove = watchPyramidFromAbove(testCharacters);

    Assert::That("\n" + actualWatchFromAbove, Is().EqualTo("\n" + expectedWatchFromAbove));

    // Test CountVisibleCharacters
    Assert::That(countVisibleCharactersOfThePyramid(testCharacters), Is().EqualTo(25));

    // Test CountAllCharacters
    Assert::That(countAllCharactersOfThePyramid(testCharacters), Is().EqualTo(35));
}

It(_3_SameCharacters)
{
    std::string testCharacters = "aaa";

    // Test FromSide
    std::string expectedWatchFromSide = "  a  \n aaa \naaaaa";
    std::string actualWatchFromSide = watchPyramidFromTheSide(testCharacters);

    Assert::That("\n" + actualWatchFromSide, Is().EqualTo("\n" + expectedWatchFromSide));

    //Test FromAbove
    std::string expectedWatchFromAbove = "aaaaa\naaaaa\naaaaa\naaaaa\naaaaa";
    std::string actualWatchFromAbove = watchPyramidFromAbove(testCharacters);

    Assert::That("\n" + actualWatchFromAbove, Is().EqualTo("\n" + expectedWatchFromAbove));

    // Test CountVisibleCharacters
    Assert::That(countVisibleCharactersOfThePyramid(testCharacters), Is().EqualTo(25));

    // Test CountAllCharacters
    Assert::That(countAllCharactersOfThePyramid(testCharacters), Is().EqualTo(35));
}

It(_4_DescendingOrderedCharacters)
{
    std::string testCharacters = "54321";

    // Test FromSide
    std::string expectedWatchFromSide = "    1    \n   222   \n  33333  \n 4444444 \n555555555";
    std::string actualWatchFromSide = watchPyramidFromTheSide(testCharacters);

    Assert::That("\n" + actualWatchFromSide, Is().EqualTo("\n" + expectedWatchFromSide));

    //Test FromAbove
    std::string expectedWatchFromAbove = "555555555\n544444445\n543333345\n543222345\n543212345\n543222345\n543333345\n544444445\n555555555";
    std::string actualWatchFromAbove = watchPyramidFromAbove(testCharacters);

    Assert::That("\n" + actualWatchFromAbove, Is().EqualTo("\n" + expectedWatchFromAbove));

    // Test CountVisibleCharacters
    Assert::That(countVisibleCharactersOfThePyramid(testCharacters), Is().EqualTo(81));

    // Test CountAllCharacters
    Assert::That(countAllCharactersOfThePyramid(testCharacters), Is().EqualTo(165));
}

It(_5_RandomTests)
{
    std::function<std::string(std::string)> solutionWatchPyramidFromTheSide = [](std::string characters) {
        if (characters.empty())
        {
            return characters;
        }

        int charactersLength = characters.size();

        std::vector<std::string> layers;
        for (int i = 0; i < charactersLength; i++)
        {
            int layerLength = (charactersLength - i) * 2 - 1;
            std::string layer = std::string(i, ' ') + std::string(layerLength, characters[i]) + std::string(i, ' ');

            layers.push_back(layer);
        }

        std::reverse(layers.begin(), layers.end());

        std::string result;
        for (int i = 0; i < charactersLength; i++)
        {
            if (i != 0)
            {
                result.append(1, '\n');
            }

            result.append(layers[i]);
        }

        return result;
    };

    std::function<std::string(std::string)> solutionWatchPyramidFromAbove = [](std::string characters) {
        if (characters.empty())
        {
            return characters;
        }

        std::vector<std::string> layers;

        int maxlayerlength = characters.size() * 2 - 1;

        for (int i = 0; i < maxlayerlength; i++)
        {
            int sl1 = (maxlayerlength / 2) - abs(i - (maxlayerlength / 2));

            std::string layer;

            for (int j = 0; j < maxlayerlength; j++)
            {
                int sl2 = (maxlayerlength / 2) - abs(j - (maxlayerlength / 2));

                layer.append(1, characters[std::min(sl2, sl1)]);
            }

            layers.push_back(layer);
        }

        std::string result;
        for (int i = 0; i < maxlayerlength; i++)
        {
            if (i != 0)
            {
                result.append(1, '\n');
            }

            result.append(layers[i]);
        }

        return result;
    };

    std::function<int(std::string)> solutionCountVisibleCharactersOfThePyramid = [](std::string characters) {
        if (characters.empty())
        {
            return -1;
        }

        return int(pow(characters.size() * 2 - 1, 2));
    };

    std::function<int(std::string)> solutionCountAllCharactersOfThePyramid = [](std::string characters) {
        if (characters.empty())
        {
            return -1;
        }

        int countCharacters = 0;

        for (int i = 0; i < characters.size(); i++)
        {
            countCharacters += int(pow((i + 1) * 2 - 1, 2));
        }

        return countCharacters;
    };

    srand(std::time(0));
    for (int i = 0; i < 100; i++)
    {
        int randomLength = rand() % 6;

        std::string randomTestCharacters;
        for (int j = 0; j < randomLength; j++)
        {
            randomTestCharacters.append(1, (char)rand() % 31 + 48);
        }

        // Test FromSide
        std::string expectedWatchFromSide = solutionWatchPyramidFromTheSide(randomTestCharacters);
        std::string actualWatchFromSide = watchPyramidFromTheSide(randomTestCharacters);

        Assert::That("\n" + actualWatchFromSide, Is().EqualTo("\n" + expectedWatchFromSide));

        //Test FromAbove
        std::string expectedWatchFromAbove = solutionWatchPyramidFromAbove(randomTestCharacters);
        std::string actualWatchFromAbove = watchPyramidFromAbove(randomTestCharacters);

        Assert::That("\n" + actualWatchFromAbove, Is().EqualTo("\n" + expectedWatchFromAbove));

        // Test CountVisibleCharacters
        Assert::That(countVisibleCharactersOfThePyramid(randomTestCharacters), Is().EqualTo(solutionCountVisibleCharactersOfThePyramid(randomTestCharacters)));

        // Test CountAllCharacters
        Assert::That(countAllCharactersOfThePyramid(randomTestCharacters), Is().EqualTo(solutionCountAllCharactersOfThePyramid(randomTestCharacters)));
    }
}
}
;

int main()
{
    return TestRunner::RunAllTests();
}