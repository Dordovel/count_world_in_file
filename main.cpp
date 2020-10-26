#include "./header/algorithm.h"

#include <iostream>
#include <fstream>
#include <iterator>
#include <time.h>

int main(const int argc, char** argv)
{
    clock_t tStart = clock();

	if(argc <= 1)
	{
		std::cout<<"Not Found Params\n";
		return EXIT_FAILURE;
	}
	else
	{
		std::ifstream stream(argv[1]);

		if(stream.is_open())
		{
			Algorithm algorithm;

			std::string param;
			for(int a = 2; a < argc; ++a)
			{
				param = argv[a];
				if(param == "-e")
				{
					algorithm.set_encoding(argv[a + 1]);
					a += 1;
					continue;
				}

				if(param == "-n_cs")
				{
					algorithm.case_sensitive(false);
					continue;
				}

				algorithm.add_predicate(param);
			}

			auto begin = std::istream_iterator<std::string>(stream);
			auto end = std::istream_iterator<std::string>();

			std::for_each(begin, end, algorithm);

			auto predicates = algorithm.get_predicats();

			for(auto&& var : predicates)
			{
				std::cout<<"Predicate: '"<<var.first<<"' Found: "<<var.second<<std::endl;
			}
		}
		else
		{
			std::cout<<"File '"<<argv[1]<<"' Not Open\n";
		}

		stream.close();
	}

    printf("Time taken: %.5fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

	return EXIT_SUCCESS;
}
