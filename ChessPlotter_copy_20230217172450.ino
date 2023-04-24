#include <GyverStepper.h>
#include "const.h"
#include "funcs.h"
#include "Plotter.h"
#include <ArduinoQueue.h>
#define PIN_RELAY A3


String readString;
struct scommand{ 
  byte c = 0;
  int c1 = 0;
  int c2 = 0;
};

scommand buf;
scommand buff;

Plotter p;

String Result = "";
unsigned long lastReceiveTime = 0;
int command = 0;
int command2 = 0;
byte command_type = 0;
ArduinoQueue<scommand> commands;


void setup() {
  Serial.begin(9600);
  Serial.setTimeout(2);
  p.init_plotter();
  p.move_to_corner();
  pinMode(PIN_RELAY, OUTPUT);
  digitalWrite(PIN_RELAY, LOW);
}


void loop() {
  p.update_m();
  if (Serial.available()){
    update_commands();
  }
  process_commands();
  if (MAG == true) {
    digitalWrite(PIN_RELAY, HIGH)
  }
  else {
    digitalWrite(PIN_RELAY, LOW)
  }
}


void process_commands(){                          //Обработка команды из struct и запуск функции с переменными из этой команды в качестве аргументов
  if (!p.is_moving() && !commands.isEmpty()){
    buff = commands.dequeue();
    command_type = buff.c;
    command = buff.c1;
    command2 = buff.c2;
  }
  p.process_command(command_type, command, command2);
}


void update_commands(){           //Обработка данных из Serial Monitor и добавление команды в очередь
    buf.c = Serial.peek();
    buf.c1 = Serial.parseInt();
    buf.c2 = Serial.parseInt();
    commands.enqueue(buf);
  }


