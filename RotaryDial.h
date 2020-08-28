#ifndef RitaryDial_h
#define RotaryDial_h

#include <stdint.h>

#define NO_NUMBER	-1

typedef enum {
	WAITING,
	LISTENING_NOPULSE,
	LISTENING_PULSE
} state_t;

class RotaryDial {
    public:
        RotaryDial (int pulse, int ready);
        uint8_t update();
        uint8_t hasNextNumber();
        int8_t getNextNumber();
    private:
        uint8_t changeStateIfDebounced(state_t newState);
        void completeDial();          
        int _pulsePin;
        int _readyPin;
        state_t _state;
        uint8_t _hasCompletedNumber;
        int8_t _number;
        uint32_t _lastStateChangeMillis;
};

#endif
