package RegularSensor is
   task type RegularSensor is
      entry GetValueDataRegister (Result : out Integer);
      entry SetValueDataRegister (NewValue : Integer);
      entry GetValueStatusRegister (Result : out Integer);
      entry SetValueStatusRegister (NewValue : Integer);
      entry SetPeriod (NewValue : Time_Span);
      entry SetDeadline (NewValue : Time_Span);
      entry SetNameSensor (NewValue : String);
      entry GetNameSensor (Result : out String);
      entry SetNameNature (NewValue : String);
   end RegularSensor;
end RegularSensor;
