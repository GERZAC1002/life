CC = gcc
CFLAGS = -Wall -lpthread -ffast-math -Os -s -fno-ident -fno-math-errno -ffunction-sections -fdata-sections -fno-stack-protector -fno-unwind-tables -fno-asynchronous-unwind-tables -Wl,--build-id=none -Wl,-z,norelro -Wl,--gc-sections -Wl,--hash-style=gnu 

life:
	$(CC) $(CFLAGS) -o life life.c
	$(CC) $(CFLAGS) -o life_wrap life_wrap.c
	$(CC) $(CFLAGS) -o life_v2 life_v2.c
	$(CC) $(CFLAGS) -o life_v3 life_v3.c


clean:
	rm -f life life_wrap life_v2 life_v3
