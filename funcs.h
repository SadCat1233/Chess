
  bool read_switch(byte pin) 
  {
    //dual read as crude debounce
    if ( SENSORS_INVERTING )
      return !digitalRead(pin) && !digitalRead(pin);
    else
      return digitalRead(pin) && digitalRead(pin);
  }


  bool can_step(byte direction, int min_pin, int max_pin)
  {
    //stop us if we're at home and still going 
    if (read_switch(min_pin) && !direction)
      return false;
    //stop us if we're at max and still going
    else if (read_switch(max_pin) && direction)
      return false;
    //default to being able to step
    return true;
  }


  while (Serial.available()) { // Если есть доступные байты в порту для чтения
    char incomingByte = Serial.read(); // Читаем байт из порта
    Result += incomingByte; // Добавляем байт к строке
    lastReceiveTime = millis(); // Обновляем время последнего приема символа
    
    if (Result.length() == 4) { // Если получена строка корректной длины
      Serial.println(Result); // Выводим строку в монитор порта
      lastReceiveTime = millis(); // Обновляем время последнего приема символа
    }
    else if ((Result.length() > 4) || (Result.length() < 4)) { // Если строка слишком длинная или слишком короткая
      Result = ""; // Очищаем строку
      lastReceiveTime = millis(); // Обновляем время последнего приема символа
    }
  }
  
  if (millis() - lastReceiveTime > 3000) { // Если прошло более 3 секунд с момента последнего приема
    Result = ""; // Очищаем строку для следующего чтения
  }



