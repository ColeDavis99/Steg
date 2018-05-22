default: Steg.cpp custom_funcs.cpp
	g++ Steg.cpp custom_funcs.cpp -lpthread -lX11 -o stegify -g -std=c++11
