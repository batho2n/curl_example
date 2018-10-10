.SUFFIXES: .c.cpp.o

GCC				= gcc
GXX				= g++
AR				= ar
MKDIR			= mkdir -p
CD				= cd
CP				= cp -R
RM				= rm -rf
LN				= ln -f -s

CFLAGS			= -std=c++11 -Wall -I. -DTTS_DEBUG -DRAW_FEATURE -DUNIX -DLINUX -D_REENTRAN

#LIBS			= -L/usr/lib64 -L/usr/lib64/openssl -lcurl -lcrypto
LIBS			= -lcurl
INCS			= -I/usr/include

TRADING_OBJS	= xcoin_api_client.o
TRADING_EXE		= coin_trading.exe

CURL_OBJS		= curl_example.o
CURL_EXE		= curl_example.exe

WAV_OBJS		= wav_example.o
WAV_EXE			= wav_example.exe

OBJS			= $(CURL_OBJS)	$(WAV_OBJS)	$(TEST_OBJS)
EXE				= $(CURL_EXE)	$(WAV_EXE)	$(TEST_EXE)

TEST_OBJS		= sepheaders.o
TEST_EXE		= sepheaders.exe

all: build

build: $(OBJS) 
	$(GXX) -o $(CURL_EXE) $(CURL_OBJS) $(LIBS)
	$(GXX) -o $(WAV_EXE) $(WAV_OBJS) $(LIBS)
	$(GXX) -o $(TEST_EXE) $(TEST_OBJS) $(LIBS)

.c.o:
	$(GCC) $(INCS) $(CFLAGS) -o $@ -c $<

.cpp.o:
	$(GXX) $(INCS) $(CFLAGS) -o $@ -c $<

curl:
	./$(CURL_EXE) test TTS music_artist_2NE1

wav:
	./$(WAV_EXE) http://www.kozco.com/tech/piano2.wav

test:
	./$(WAV_EXE) https://curl.haxx.se/libcurl/c/url2file.html

clean:
	$(RM) $(EXE) *.o wave.raw header.bin

install:
	sudo yum install -y openssl-devel

.PHONY: all build exec clean; 
