#include "Arduino.h"
#include "RotaryDial.h"

#define DEBOUNCE_DELAY	15

RotaryDial::RotaryDial (int pulsePin, int readyPin) {
	_pulsePin = pulsePin;
	_readyPin = readyPin;
	pinMode(_pulsePin, INPUT_PULLUP);
	pinMode(_pulsePin, INPUT_PULLUP);
	_lastStateChangeMillis = millis();
}


uint8_t RotaryDial::changeStateIfDebounced(state_t newState) {
	uint32_t currentMillis = millis();
	if ((uint32_t)((currentMillis - _lastStateChangeMillis) > DEBOUNCE_DELAY)) {
		_state = newState;
		_lastStateChangeMillis = currentMillis;
		return 1;
	}
	else {
		return 0;
	}
}


void RotaryDial::completeDial(void) {
	if (!changeStateIfDebounced(WAITING)) {
		return;
	}
	if (_number > 0 && _number <= 10) {
		if (_number == 10) {
			_number = 0;
		}
		_hasCompletedNumber = 1;
	}
}


uint8_t RotaryDial::update (void) {
	uint8_t readyStatus = digitalRead(_readyPin);
	uint8_t pulseStatus = digitalRead(_pulsePin);

	switch(_state) {
		case WAITING:
			if (readyStatus == 0 && changeStateIfDebounced(LISTENING_NOPULSE)) {
				_hasCompletedNumber = 0;
				_number = 0;
			}
			break;
		case LISTENING_NOPULSE:
			if (readyStatus == 1) {
				completeDial();
			}
            		else if (pulseStatus == 1) {
				changeStateIfDebounced(LISTENING_PULSE);
			}
			break;
		case LISTENING_PULSE:
			if (readyStatus == 1) {
				completeDial();
			}
            		else if (pulseStatus == 0 && changeStateIfDebounced(LISTENING_NOPULSE)) {
				_number++;
			}
			break;
	}
	return _hasCompletedNumber;
}


uint8_t RotaryDial::hasNextNumber() {
	return _hasCompletedNumber;
}


int8_t RotaryDial::getNextNumber() {
	if (_hasCompletedNumber) {
		_hasCompletedNumber = 0;
		return _number;
	}
    	else {
		return NO_NUMBER;
	}
}
