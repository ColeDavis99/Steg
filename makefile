default: Steg.cpp custom_funcs.cpp
	g++ Steg.cpp custom_funcs.cpp -lpthread -lX11 -o exe -std=c++11
