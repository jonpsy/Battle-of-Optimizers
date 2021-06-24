benchmark:
	g++ main.cpp -larmadillo -O3 -o main

benchmark-debug:
	g++ main.cpp -g -larmadillo -o main-debug

accuracy:
	g++ indicator.cpp -larmadillo -O3 -o indicator

accuracy-debug:
	g++ indicator.cpp -larmadillo -O3 -o indicator-debug

all: benchmark benchmark-debug accuracy accuracy-debug
	@echo "Done"

clean:
	rm main main-debug indicator indicator-debug
