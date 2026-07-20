const int BUTTON_PINS[4] = {A5, A4, A3, A2};

void setup() {
    Serial.begin(9600);
    for (int i = 0; i < 4; ++i) {
        pinMode(BUTTON_PINS[i], INPUT);
    }
}

void loop() {
    Serial.print("1: ");
    Serial.print(digitalRead(A5));
    Serial.print(", 2: ");
    Serial.print(digitalRead(A4));
    Serial.print(", 3: ");
    Serial.print(digitalRead(A3));
    Serial.print(", 4: ");
    Serial.println(digitalRead(A2));
    tone(8, 220);
}
