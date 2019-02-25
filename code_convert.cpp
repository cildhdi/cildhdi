#include <codecvt>
#include <windows.h>
#include <memory>

std::wstring utf8str2wstr(const std::string &u8str)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    return conv.from_bytes(u8str);
}

std::string wstr2utf8str(const std::wstring &wstr)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    return conv.to_bytes(wstr);
}

std::string wstr2str(const std::wstring &wstr)
{
    if (wstr.empty())
        return "";
    std::unique_ptr<char[]> buffer = nullptr;
    int size = ::WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
    if (size > 0)
    {
        buffer.reset(new char[size + 1]);
        ::ZeroMemory(buffer.get(), (size + 1) * sizeof(char));
        ::WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, buffer.get(), size, NULL, NULL);
    }
    return buffer.get();
}

std::wstring str2wstr(const std::string &str)
{
    if (str.empty())
        return L"";
    std::unique_ptr<wchar_t[]> buffer = nullptr;
    int size = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
    if (size > 0)
    {
        buffer.reset(new wchar_t[size + 1]);
        ZeroMemory(buffer.get(), (size + 1) * sizeof(wchar_t));
        MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, buffer.get(), size);
    }
    return buffer.get();
}