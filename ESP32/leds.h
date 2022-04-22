void turn_off(int i);
void blink(int i);
void turn_on(int i);

void blink(int i){
  turn_on(i);
  delay(250);
  turn_off(i);
}

void turn_off(int i){
  digitalWrite(i, LOW);
}

void turn_on(int i){
  digitalWrite(i, HIGH);
}