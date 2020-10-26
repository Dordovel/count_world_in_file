#ifndef ALGORITHM
#define ALGORITHM

#include <vector>
#include <string>
#include <algorithm>

class Algorithm
{
	private:
		std::vector<std::pair<std::string, int>> _predicate;
		Algorithm* _p;
		std::string _fileEncoding;
		bool _needConvert;
		bool _caseSensitive;

		void search_without_register(const std::string& buffer);

		void search_with_register(const std::string& buffer);

	public:
		Algorithm();
		~Algorithm() = default;

		void add_predicate(const std::string& value);

		void set_encoding(const std::string& encoding);

		void case_sensitive(bool flag);

		auto get_predicats()->decltype(this->_predicate);

		void operator()(const std::string& value);
};

#endif //ALGORITHM
