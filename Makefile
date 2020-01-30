CC = g++
CFLAGS = -ggdb -Wall
CPPFLAGS = -Iinclude -I/usr/include/SDL2
OBJS = src/main.cpp src/Phong.cpp src/PhongException.cpp src/Sprite.cpp src/stdafx.cpp
LDFLAGS = -lSDL2 -lSDL2_image

all: phong

# --------------
# Binary
# --------------

phong: $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o phong $(OBJS) $(LDFLAGS)
    
# --------------
# Clean
# --------------

clean:
	$(RM) *.o phong

