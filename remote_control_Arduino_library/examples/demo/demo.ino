#include <remote_control.h>

remote_control myremote(Serial1);
void setup() {
	Serial.begin(115200);
	Serial1.begin(115200);
}

void loop() {
	if (myremote.keyPressed(remote_control::KEY_0)) {
		Serial.println("KEY_0 pressed");
	}
}
