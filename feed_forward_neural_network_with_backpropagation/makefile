all: predictor

predictor: reluneuron.o dataset.o converters.o network.o predictor.o	
	g++ -g3 -ggdb reluneuron.o dataset.o converters.o network.o predictor.o -o predictor

reluneuron.o: reluneuron.cpp
	g++ -c -g3 reluneuron.cpp

dataset.o: dataset.cpp
	g++ -c -g3 dataset.cpp

converters.o : converters.cpp
	g++ -c -g3 converters.cpp

network.o: network.cpp
	g++ -c -g3 network.cpp

predictor.o: predictor.cpp
	g++ -c -g3 predictor.cpp

clean:
	rm *.o