CC=g++
CFLAGS=-c -Wall --std=c++11 -g
LDFLAGS=--std=c++11 -lsfml-window -lsfml-graphics -lsfml-system -lsfml-network -lBox2D -lz -ltmx-loader -lpugi -g
SOURCES=main.cpp node.cpp entity.cpp physics_system.cpp rect_factory.cpp draw_system.cpp transform_c.cpp car_system.cpp keyboard_input_c.cpp car_factory.cpp ai_system.cpp weapon_factory.cpp contactlistener.cpp tmx2box2d.cpp factory.cpp invisible_wall_factory.cpp session.cpp main_menu.cpp winscreen.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=micromachines

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)
