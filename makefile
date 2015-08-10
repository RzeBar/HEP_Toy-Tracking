CC=g++
CFLAGS= `root-config --cflags` -g -Wall -c -std=c++0x
LDFLAGS=`root-config --ldflags`
LIBS=`root-config --glibs` -lRooFit -lRooFitCore -lTMVA -lReflex -lRooStats


SOURCES= src/EventUtils.C src/Sensor.C src/Detector.C src/StatisticTools.C src/Experiment.C main.C 
OBJECTS=$(SOURCES:.C=.o)
EXECUTABLE=ToyTracking

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(LIBS) $(OBJECTS) -o $@

all: $(SOURCES) $(EXECUTABLE)

.C.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
run:
	./$(EXECUTABLE)

.PHONY: all clean run
