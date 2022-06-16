LIBS=`pkg-config --cflags --libs allegro-5 allegro_acodec-5 allegro_audio-5 allegro_color-5 allegro_font-5 allegro_image-5 allegro_main-5 allegro_memfile-5 allegro_physfs-5 allegro_primitives-5 allegro_ttf-5` -lm

# INCLUDES=-I/home/pi/allegro5/

all: allegro_base

teste-allegro-lab: teste-allegro-lab.o
	gcc -o teste-allegro-lab teste-allegro-lab.o $(LIBS)

allegro_base: allegro_base.o
	gcc -o allegro_base allegro_base.o $(LIBS)
	
bola: bola.o
	gcc $(INCLUDES) -o bola bola.o $(LIBS)

bola.o: bola.c
	gcc $(INCLUDES) -c bola.c

circles: circles.o
	gcc -o circles circles.o $(LIBS)

circles.o: circles.c
	gcc  -c circles.c $(LIBS)

passaro_andante: passaro_andante.o
	gcc -o passaro_andante passaro_andante.o $(LIBS)

passaro_andante.o: passaro_andante.c
	gcc  -c passaro_andante.c $(LIBS)

passaro_raivoso: passaro_raivoso.o
	gcc -o passaro_raivoso passaro_raivoso.o $(LIBS)

passaro_raivoso.o: passaro_raivoso.c
	gcc  -c passaro_raivoso.c $(LIBS)

bouncer: bouncer.o
	gcc -o bouncer bouncer.o $(LIBS)

bouncer.o: bouncer.c
	gcc  -c bouncer.c $(LIBS)

teclado: teclado.o
	gcc -o teclado teclado.o $(LIBS)

teclado.o: teclado.c
	gcc  -c teclado.c $(LIBS)

louco: louco.o
	gcc -o louco louco.o $(LIBS)

louco.o: louco.c
	gcc  -c louco.c $(LIBS)

frogger: frogger.o
	gcc -o frogger frogger.o $(LIBS)

frogger.o: frogger.c
	gcc  -c frogger.c $(LIBS)

pong: pong.o
	gcc -o pong pong.o $(LIBS)

pong.o: pong.c
	gcc  -c pong.c $(LIBS)

ghero-0.o: ghero-0.c
	gcc -c allegro_base.c $(LIBS)


clean:
	rm -f bola.o
	rm -f bola
	rm -f circles.o
	rm -f circles
	rm -f passaro_andante.o
	rm -f passaro_andante
	rm -f passaro_raivoso.o
	rm -f passaro_raivoso
	rm -f louco.o
	rm -f louco
	rm -f teclado.o
	rm -f teclado
	rm -f bouncer.o
	rm -f bouncer
	rm -f frogger.o
	rm -f frogger
	rm -f pong.o
	rm -f pong
	rm -f allegro_base.o
	rm -f allegro_base

