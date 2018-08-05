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

LIBS			= -L/usr/lib64 -L/usr/lib64/openssl -lcurl -lcrypto
INCS			= -I/usr/include

TRADING_OBJS	= xcoin_api_client.o
TRADING_EXE		= coin_trading.exe

CURL_OBJS		= curl_example.o
CURL_EXE		= curl_example.exe

OBJS			= $(CURL_OBJS)
EXE				= $(CURL_EXE)

all: build

build: $(OBJS) 
	$(GXX) -o $(EXE) $(OBJS) $(LIBS)

.c.o:
	$(GCC) $(INCS) $(CFLAGS) -o $@ -c $<

.cpp.o:
	$(GXX) $(INCS) $(CFLAGS) -o $@ -c $<

exec:
	./$(TRADING) -t sell -c ETH -u 0.0000001

clean:
	$(RM) $(EXE) *.o

install:
	sudo yum install -y openssl-devel

.PHONY: all build exec clean; 
