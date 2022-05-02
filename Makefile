sim: main.cpp quadTree.cpp body.cpp
	g++ -o sim main.cpp quadTree.cpp body.cpp -lGL -lGLU -lglut
