#include "../header/algorithm.h"

#include <glib.h>
#include <stdexcept>

namespace
{
    std::string convert_str(const std::string& str, const std::string& from, const std::string& to)
    {
        std::size_t write;
        gchar* buffer = g_convert(str.c_str(), -1, to.c_str(), from.c_str(), nullptr, &write, nullptr);

        if(buffer == nullptr)
            throw std::logic_error("Invalid Encoding: " + from);

        std::string result(buffer, write);

        g_free(buffer);
            
        return result;
    }

    std::string convert_to_lower_case(const std::string& str)
    {
		const std::size_t size = str.size();

        std::string result;
		result.reserve(size);

		for(std::size_t i = 0; i < size; ++i)
			result[i] = std::tolower(str[i]);

        return result;
    }
};

Algorithm::Algorithm():_p(this), _needConvert(false), _caseSensitive(true){}

void Algorithm::add_predicate(const std::string& value)
{
    this->_predicate.emplace_back(value, 0);
}

void Algorithm::set_encoding(const std::string& encoding)
{
    this->_needConvert = true;
    this->_fileEncoding = encoding;
}

void Algorithm::case_sensitive(bool flag)
{
    this->_caseSensitive = flag;
}

auto Algorithm::get_predicats()->decltype(this->_predicate)
{
    return this->_predicate;
}

void Algorithm:: search_without_register(const std::string& buffer)
{
    auto begin = std::begin(this->_p->_predicate);
    auto end = std::end(this->_p->_predicate);

    if(auto val = std::find_if(begin, end, [&buffer](auto key)
                                                {return convert_to_lower_case(key.first) == convert_to_lower_case(buffer);});
            val != end)
    {
        ++val->second;
    }
}

void Algorithm::search_with_register(const std::string& buffer)
{
    auto begin = std::begin(this->_p->_predicate);
    auto end = std::end(this->_p->_predicate);

    if(auto val = std::find_if(begin, end, [&buffer](auto key)
                                                {return key.first == buffer;});
            val != end)
    {
        ++val->second;
    }
}

void Algorithm::operator()(const std::string& value)
{
    std::string buffer;
    if(this->_needConvert)
        buffer = convert_str(value, this->_p->_fileEncoding, "utf-8");
    else
        buffer = value;

    if(this->_caseSensitive)
        this->search_with_register(buffer);
    else
        this->search_without_register(buffer);
}
