default: Steg.cpp custom_funcs.cpp
	g++ Steg.cpp custom_funcs.cpp -lpthread -lX11 -o exe -g -std=c++11

clean:
	rm steg.jpg && rm original.jpg && clear
