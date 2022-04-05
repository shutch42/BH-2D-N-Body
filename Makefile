sim: main.cpp octTree.cpp body.cpp
	g++ -o sim main.cpp octTree.cpp body.cpp -lGL -lGLU -lglut
