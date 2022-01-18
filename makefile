CC := g++
CFLAGS := -Wall -std=c++17 -O2 -v
ALLEGRO_LIBRARIES := allegro-5 allegro_image-5 allegro_font-5 allegro_ttf-5 allegro_dialog-5 allegro_primitives-5 allegro_audio-5 allegro_video-5 allegro_acodec-5
ALLEGRO_FLAGS := $(shell pkg-config --cflags --libs $(ALLEGRO_LIBRARIES)) -lallegro -lallegro_main

OUT:= game
SOURCE = Main.cpp ./algif5/src/algif.c ./algif5/src/bitmap.c ./algif5/src/gif.c ./algif5/src/lzw.c Attack.cpp Circle.cpp GameWindow.cpp global.cpp Level.cpp Menu.cpp Monster.cpp Slider.cpp Tower.cpp People.cpp Item.cpp
OBJ = Main.o algif.o bitmap.o gif.o lzw.o Attack.o Circle.o GameWindow.o global.o Level.o Menu.o Monster.o Slider.o Tower.o  People.o Item.o

all: 
	$(CC) -c -g $(CFLAGS) $(SOURCE) $(ALLEGRO_FLAGS)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJ) $(ALLEGRO_FLAGS)
	rm $(OBJ)

.PHONY:clean
clean:
	rm $(OUT)