LIBS=`pkg-config --cflags --libs allegro-5 allegro_acodec-5 allegro_audio-5 allegro_color-5 allegro_font-5 allegro_image-5 allegro_main-5 allegro_memfile-5 allegro_physfs-5 allegro_primitives-5 allegro_ttf-5  -lm

# INCLUDES=-I/home/pi/allegro5/

all: clean pongs

teste-allegro-lab: teste-allegro-lab.o
	gcc -o teste-allegro-lab teste-allegro-lab.o $(LIBS)

pongs: clean pongs.o
	gcc -o Pongs pongs.o $(LIBS) 
	
clean:
	rm -f pongs.o
	rm -f Pongs

