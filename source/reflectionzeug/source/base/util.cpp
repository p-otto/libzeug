
#include <reflectionzeug/base/util.h>

#ifdef USE_STD_REGEX
    #include <regex>

    namespace regex_namespace = std;
#else
    #include <boost/regex.hpp>

    namespace regex_namespace = boost;
#endif

#include <cctype>
#include <cassert>
#include <algorithm>


namespace reflectionzeug
{


namespace util
{


template <>
char fromString<char>(const std::string & string)
{
    std::stringstream stream(string);
    int value;
    stream >> value;
    return static_cast<char>(value);
}

template <>
unsigned char fromString<unsigned char>(const std::string & string)
{
    std::stringstream stream(string);
    unsigned int value;
    stream >> value;
    return static_cast<unsigned char>(value);
}

template <>
std::string toString<char>(const char & value)
{
    std::stringstream stream;
    stream << static_cast<int>(value);
    return stream.str();
}

template <>
std::string toString<unsigned char>(const unsigned char & value)
{
    std::stringstream stream;
    stream << static_cast<unsigned int>(value);
    return stream.str();
}

std::string trim(const std::string & string, bool removeAllWhitespace)
{
    const regex_namespace::regex regex(removeAllWhitespace ? "\\s+" : "(^\\s+|\\s+$)");
    return regex_namespace::regex_replace(string, regex, "");
}

std::vector<std::string> splitArray(const std::string & string, size_t size)
{
    std::string regexString = "\\s*\\(";
    for (size_t i = 0; i < size - 1; ++i)
        regexString.append("([^,]*),");
    regexString.append("([^,]*)\\)\\s*");

    regex_namespace::smatch match;
    regex_namespace::regex regex(regexString);

    if (!regex_namespace::regex_match(string, match, regex))
        return {};

    std::vector<std::string> result;
    for (size_t i = 1; i < match.size(); ++i)
        result.push_back(trim(match[i].str(), false));

    assert(result.size() == size);
    return result;
}

std::vector<std::string> split(const std::string & input, char delimiter)
{
    std::vector<std::string> result;
    result.push_back(std::string());
    for (const char & c : input)
    {
        if (c == delimiter)
        {
            result.push_back(std::string());
            continue;
        }
        
        result.back().push_back(c);
    }
    return result;
}

bool matchesRegex(const std::string & string, const std::string & regex)
{
    return regex_namespace::regex_match(string, regex_namespace::regex(regex));
}

std::vector<std::string> extract(const std::string & string, const std::string & regex)
{
    std::vector<std::string> values;

    regex_namespace::smatch matchResults;

    std::string s = string;
    while (regex_namespace::regex_search(s, matchResults, regex_namespace::regex(regex)))
    {
        values.push_back(matchResults[0]);
        s = matchResults.suffix().str();
    };

    return values;
}


} // namespace util


} // namespace reflectionzeug
