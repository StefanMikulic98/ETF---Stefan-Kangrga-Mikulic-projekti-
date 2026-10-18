package Nature is
   function randomN return Integer;

   task type NatureTask is
      entry GetValue (Result : out Integer);
      entry SetValue (NewValue : Integer);
      entry SetDiff (NewValue : Integer);
      entry SetControllableSignal (NewValue : Boolean);
      entry SetOnSignal;
      entry SetOffSignal;
      entry SetNameTask (NewValue : String);
      entry GetNameTask (Result : out String);
   end NatureTask;

end Nature;
