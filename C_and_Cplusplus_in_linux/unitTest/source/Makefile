INC=-I/usr/local/include
LIB=-L/usr/local/lib

all:test.c CUnitRunTest.c testMain.c
	gcc $^ -o test $(INC) $(LIB) -lcunit

clean:
	rm -f test
