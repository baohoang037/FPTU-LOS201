CC ?= gcc
CFLAGS ?= -Wall -Wextra -pthread -I. -O2
LDFLAGS ?= -pthread -lrt -lm

ARM_CC = arm-linux-gnueabihf-gcc

SRCS = circular_buffer.c logger_thread.c alert_thread.c processor_thread.c sensor_thread.c sms_app.c
OBJS = $(SRCS:.c=.o)

all: host

host:
	$(CC) $(CFLAGS) $(SRCS) -o sms_app_x86 $(LDFLAGS)

arm:
	$(ARM_CC) $(CFLAGS) $(SRCS) -o sms_app $(LDFLAGS)

clean:
	rm -f *.o sms_app sms_app_x86 test_cb
