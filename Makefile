CC = gcc
CFLAGS = -Wall -Werror -std=c99 -pedantic -Os
LDFLAGS =

INCLUDE = -I/home/wenford/vedio/logs/app/include/

OUTPUT = bin

SRC = app/src

SOURCES = $(wildcard $(SRC)/*.c)
#OBJECTS = $(patsubst %.c,%.o,$(SOURCES))
#http://bbs.chinaunix.net/thread-1692258-1-1.html
#OBJS_NAME = $(notdir $(patsubst %.c,%.o,$(SOURCES)))
OBJS = $(addprefix $(OUTPUT)/,$(notdir $(patsubst %.c,%.o,$(SOURCES))))

TARGET = bin/Analyze

CFLAGS += `pkg-config --cflags glib-2.0`
LDFLAGS += `pkg-config --libs glib-2.0` -lm

all: $(TARGET)

$(TARGET):$(OUTPUT) $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)

$(OBJS):$(SOURCES)
	$(CC) $(INCLUDE) $(CFLAGS) -o $@ -c $(filter %$(*F).c,$(SOURCES))

clean:
	rm -rf $(OUTPUT)
	mkdir $(OUTPUT)
install:
	cp $(TARGET) /usr/bin 
uninstall:  
	rm -rf /usr/bin/$(TARGET)