default: Steg.cpp custom_funcs.cpp
	g++ Steg.cpp custom_funcs.cpp -lpthread -lX11 -o exe -g -std=c++11

clean:
	rm img1.bmp && rm img2.bmp && clear
