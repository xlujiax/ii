bigint:
	g++ -c bigint.cpp -o bigint.o
bignum: bigint
	g++ -c bignum.cpp -o bignum.o
all: bignum
	g++ bigint.o bignum.o main.cpp -o main.e