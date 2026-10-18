with Ada.Strings.Fixed; use Ada.Strings.Fixed;
with Ada.Text_IO; use Ada.Text_IO;
with Ada.Real_Time; use Ada.Real_Time;
with PumpControlStation;

package body Sensor is

   task body Sensor is
      observedPhenomenon : Nature.NatureTask;
      dataRegister : Integer := 0;
      signal : Boolean := True;  -- oznacava da li je low level(false) i high level detector(true)
      nameSensor : String := "Unknown sensor";
      boundary : Integer := 100;
      nextActivationSensor : Time := Clock;
      periodSensor : constant Time_Span := Milliseconds(1000);
      currentValue : Integer := 0;
   begin
      --observedPhenomenon.SetNameTask(""); -- setovace se samo ime senzora
      observedPhenomenon.SetValue(0);
      observedPhenomenon.SetControllableSignal(True);
      loop
         select
            accept SetNameSensor (NewValue : String) do
               nameSensor := NewValue;
               Put_Line ("Nov naziv: " & nameSensor);
            end SetNameSensor;
         or
            accept GetNameSensor (Result : out String) do
               Result := nameSensor;
            end GetNameSensor;
         or
            accept SetSignal (NewValue : Boolean) do
               Signal := NewValue;
            end SetSignal;
         or
            accept SetValueDataRegister (NewValue : Integer) do
               dataRegister := NewValue;
               Put_Line ("Nova vrednost registra podataka: " & dataRegister'Image);
            end SetValueDataRegister;
         or
            accept GetValueDataRegister (Result : out Integer) do
               Result := dataRegister;
            end GetValueDataRegister;
         or
            accept SetBoundary (NewValue : Integer) do
               boundary := NewValue;
               Put_Line ("Nova granicna vrednost: " & boundary'Image);
            end SetBoundary;
         or
            delay until nextActivationSensor;
            nextActivationSensor := nextActivationSensor + periodSensor;
            observedPhenomenon.GetValue(currentValue);
            dataRegister := currentValue;
            if signal then
               if dataRegister > boundary then

               end if;
            else
               if dataRegister < boundary then

               end if;
            end if;
            Put_Line (nameSensor & " : " & dataRegister'Image);
         end select;
      end loop;
   end Sensor;

end Sensor;
