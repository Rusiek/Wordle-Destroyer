compile:
	cd engine && g++ -std=c++11 -o validator -O3 main.cpp core/algorithm.cpp randomAccess/randomAccess.cpp baseline/baseline.cpp -pthread -Wall -Wextra -Wpedantic

debug:
	cd engine && g++ -g -std=c++11 -o validator -O0 main.cpp core/algorithm.cpp randomAccess/randomAccess.cpp baseline/baseline.cpp -pthread -Wall -Wextra -Wpedantic

run:
	cd engine && ./validator

clean:
	cd engine && rm -f validator
