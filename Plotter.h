GStepper<STEPPER2WIRE> stepperx(SPT, M1_D, M1_S);
GStepper<STEPPER2WIRE> steppery(SPT, M2_D, M2_S);


struct Plotter{
  bool is_moving_to_corner = false;
  void init_plotter(){
    pinMode(M2_MIN_PIN, INPUT_PULLUP);
    pinMode(M2_MAX_PIN, INPUT_PULLUP);
    pinMode(M1_MIN_PIN, INPUT_PULLUP);
    pinMode(M1_MAX_PIN, INPUT_PULLUP);

    stepperx.setRunMode(FOLLOW_POS); // режим поддержания скорости
    stepperx.setMaxSpeedDeg(6000);
    stepperx.setSpeedDeg(3000);         // в градусах/сек
    stepperx.setAccelerationDeg(500);

    steppery.setRunMode(FOLLOW_POS); // режим поддержания скорости
    steppery.setMaxSpeedDeg(6000);
    steppery.setSpeedDeg(3000);         // в градусах/сек
    steppery.setAccelerationDeg(500);

    stepperx.setCurrent(0);
    steppery.setCurrent(0);
  }


  void move_to_corner(){              //функция для передвижения магнита в угол доски
      stepperx.setTarget(-100000);
      steppery.setTarget(-100000);
      is_moving_to_corner = true;
  }


  void process_command(int& command, int& command2){  //Функция с набором команд для управления роботом через Serial Monitor
    stepperx.setTargetDeg(command * X_K, ABSOLUTE);
    steppery.setTargetDeg(command2 * Y_K, ABSOLUTE);
    MAG = !MAG;
    command_type = 0;
    command = 0;
    command2 = 0;
  }


  bool is_moving(){                                       //Функция возвращающая bool-значение определяющее движется магнит или нет
    return (stepperx.getState() || steppery.getState());
  }


  void update_m(){
    byte dirx = stepperx.getCurrentDeg() < stepperx.getTarget();      //определение направления движения моторов
    byte diry = steppery.getCurrentDeg() < steppery.getTarget();
    stepperx.tick();
    steppery.tick();
    
    if (!can_step(dirx, M1_MIN_PIN, M1_MAX_PIN)){     //остановка моторов если невозможно их движение
      stepperx.brake();
      if (is_moving_to_corner){
        stepperx.reset();
        //stepperx.setTarget(0);
      }
    }
    if (!can_step(diry, M2_MIN_PIN, M2_MAX_PIN)){     //остановка моторов если невозможно их движение
      steppery.brake();
      if (is_moving_to_corner){
        steppery.reset();
        //steppery.setTarget(0);
      }
    }
    if (is_moving_to_corner && (stepperx.getTargetDeg() == 0) && (steppery.getTargetDeg() == 0)){
      is_moving_to_corner = 0;
    }
  }
};