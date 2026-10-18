package Sensor is

   task type Sensor is
      entry GetValueDataRegister (Result : out Integer);
      entry SetValueDataRegister (NewValue : Integer);
      entry SetDiff (NewValue : Integer);
      entry SetSignal (NewValue : Boolean);
      entry SetNameSensor (NewValue : String);
      entry GetNameSensor (Result : out String);
      entry SetBoundary (NewValue : Integer);
   end Sensor;

end Sensor;
