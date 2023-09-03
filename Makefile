compile:
	cd engine && g++ -std=c++11 -o validator -O3 main.cpp core/algorithm.cpp randomAccess/randomAccess.cpp -pthread -Wall -Wextra -Wpedantic

run:
	cd engine && ./validator

clean:
	cd engine && rm -f validator
