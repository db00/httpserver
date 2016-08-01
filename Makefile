#/storage/sdcard1/gcc/bin/make
#CC:=/storage/sdcard1/gcc/bin/arm-linux-androideabi-gcc
CC:=gcc
SRC_DIR:=.
#INCLUDE:=-I"/storage/sdcard1/gcc/arm-linux-androideabi" 
DEFINES:= -D STDC_HEADERS  -D DEBUG -D debug_httpserver
ifeq ($(OS),Windows_NT)
	TARGET:= a.exe
	LIB:=-L"." -L"lib" -lssl -lcrypto -lwsock32 -lgdi32 -liconv -lpthread -lmingw32
else
	TARGET:= ./a.out
	LIB:=-L"/system/lib" -lc -lm -ldl -lssl -lcrypto -lpthread
endif
SRC:= $(foreach x,${SRC_DIR}, $(wildcard $(addprefix ${x}/*,.c)))
OBJS:= $(patsubst %.c,%.o,$(SRC))

CFLAGS = -g $(INCLUDE) $(DEFINES) $(LIB)

all:$(TARGET)
	$(TARGET)

$(TARGET):$(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

#$(TARGET):$(foreach x,${SRC_DIR}, $(wildcard $(addprefix ${x}/*,.h))) $(foreach x,${SRC_DIR}, $(wildcard $(addprefix ${x}/*,.c))) Makefile
#	$(CC) $(SRC) -o $(TARGET) $(CFLAGS)
#	$(TARGET) || gdb $(TARGET)

.c.o:
	$(CC) $(CFLAGS) -c $<
#上下两句相等
#%.o:%.c
#	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY : clean
clean:
	$(RM) $(TARGET) *.o
