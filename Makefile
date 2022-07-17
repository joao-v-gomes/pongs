CC = gcc
CFLAGS = 
LDLAGS = -lm
TARGET = Pongs
OBJFILES = main.o pongs.o jogadores.o graficos.o bolas.o
LIBS = `pkg-config --cflags --libs allegro-5 allegro_acodec-5 allegro_audio-5 allegro_color-5 allegro_font-5 allegro_image-5 allegro_main-5 allegro_memfile-5 allegro_physfs-5 allegro_primitives-5 allegro_ttf-5`

all: clean $(TARGET)

#teste-allegro-lab: teste-allegro-lab.o
#	$(CC) -o teste-allegro-lab teste-allegro-lab.o $(LIBS) $(LDLAGS)

$(TARGET): clean $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LIBS) $(LDLAGS)
	
clean:
	rm -f $(OBJFILES)
	rm -f $(TARGET)

