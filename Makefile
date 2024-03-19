vpath %.c src 
vpath %.h include

CPPFLAGS = -I include -Wall

objects += main.o util.o

lvl-ip: $(objects)
	$(CC) $(objects) -o build/lvl-ip

clean:
	rm *.o build/ -rf
