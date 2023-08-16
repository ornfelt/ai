TARGET = flood
CC = gcc

LIBS = -lopengl32 -lglu32 -lgdi32

all:
	windres res/app.rc -O coff -o res/app.res
	$(CC) main.c win32.c -mwindows -o $(TARGET) $(LIBS) res/app.res

clean:
	$(RM) $(TARGET).exe res/app.res
