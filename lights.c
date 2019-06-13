#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <pigpio.h>

#define PIN_RED 17
#define PIN_YELLOW 27
#define PIN_GREEN 22

void set(bool red, bool yellow, bool green) {
    gpioWrite(PIN_RED, !!red);
    gpioWrite(PIN_YELLOW, !!yellow);
    gpioWrite(PIN_GREEN, !!green);
}

inline void clear() {
    set(false, false, false);
}

int load() {
    if (gpioInitialise() < 0) {
        fprintf(stderr, "GPIO initialisation failed\n");
        return -1;
    }
    gpioSetMode(PIN_RED, PI_OUTPUT);
    gpioSetMode(PIN_YELLOW, PI_OUTPUT);
    gpioSetMode(PIN_GREEN, PI_OUTPUT);
    clear();
    return 0;
}

int upgrade() {
    return load();
}

void unload() {
    clear();
    gpioTerminate();
}
