correl_matrix: corr.o
	g++ -o correl_matrix -std=gnu++98 -Wall -Werror -pedantic corr.o
corr.o: corr.cpp corr.hpp
	g++ -c -std=gnu++98 -Wall -Werror -pedantic -ggdb3 $<

clean:
	rm -f *.o *~
