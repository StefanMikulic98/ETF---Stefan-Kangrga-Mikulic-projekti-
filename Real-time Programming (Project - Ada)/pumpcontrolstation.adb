pragma Warnings (Off);

with Ada.Strings.Fixed; use Ada.Strings.Fixed;
with Ada.Strings.Unbounded;
with Ada.Text_IO; use Ada.Text_IO;
with Ada.Real_Time; use Ada.Real_Time;
with Ada.Calendar; --use Ada.Calendar;
with Ada.Calendar.Formatting;--  use  Ada.Calendar.Formatting;
with Nature; use Nature;

package body PumpControlStation is
   observedPhenomenon: Nature.NatureTask;


   protected body WaterPumpInterruptHandler is

      procedure interruptHandlerHighLevel is
      begin
         Put_Line ("Docekao eventHighLevelOccurred");
         --observedPhenomenon.SetOnSignal; -- ZA TESTIRANJE
         eventHighLevelOccurred := True;
         evenOccurred := True;
      end interruptHandlerHighLevel;

      procedure interruptHandlerLowLevel is
      begin
         Put_Line ("Docekao eventLowLevelOccurred");
         --observedPhenomenon.SetOffSignal; -- ZA TESTIRANJE
         eventLowLevelOccurred := True;
         evenOccurred := True;
      end interruptHandlerLowLevel;

      procedure setCriticalLevel(newValue : Boolean) is
      begin
         criticalLevel := newValue;
         Put_Line ("Postavljena criticalLevel u WaterPumpInterruptHandler: " & criticalLevel'Image);
      end setCriticalLevel;

      procedure setOnOffSignal(newValue : Boolean) is
      begin
         OnOffSignal := newValue;
         Put_Line ("Postavljena OnOffSignal u WaterPumpInterruptHandler: " & OnOffSignal'Image);
      end setOnOffSignal;

      procedure getOnOffSignal(Result : out Boolean) is
      begin
         Result := OnOffSignal;
      end getOnOffSignal;

      entry waitForNextInterruptWaterLevel when evenOccurred is
      begin
         if eventHighLevelOccurred and criticalLevel = False then
            Put_Line ("interruptHandler high level, ukljucuje se pumpa");
            observedPhenomenon.SetOnSignal;
            OnOffSignal := True;
            eventHighLevelOccurred := False;
            evenOccurred := False;
         elsif eventLowLevelOccurred then
            Put_Line ("interruptHandler low level, iskljucuje se pumpa");
            observedPhenomenon.SetOffSignal;
            OnOffSignal := False;
            eventLowLevelOccurred := False;
            evenOccurred := False;
         else
            Put_Line ("Preskacem prekid, criticalLevel status: " & criticalLevel'Image);
         end if;
      end waitForNextInterruptWaterLevel;

   end WaterPumpInterruptHandler;

   task body HighLowWaterDetector is
      onOffSignal : Boolean := False;
      previousOffSignal : Boolean := False;
      dataRegister : Integer := 0;
      statusRegister : Integer := 0;
      nameSensor : String := "High/Low waterlevel detector";
      highBoundary : Integer := 10000000;
      lowBoundary : Integer := 0;
      currentValue : Integer := 0;
      i : Integer := 0;
      j : Integer := 1;
      N : Integer := 56;
      statusString : Ada.Strings.Unbounded.Unbounded_String := Ada.Strings.Unbounded.To_Unbounded_String ("OK");

      currentTime :  Ada.Calendar.Time := Ada.Calendar.Clock;
      nextActivationSensor : Time := Clock;
      nextDeadline : Time := Clock;
      periodSensor : constant Time_Span := Milliseconds(90);
      deadline : constant Time_Span := Milliseconds(40);
      Start_Time, Stop_Time : Time;
      Elapsed_Time          : Time_Span;

      Output         : File_Type;
      fileName : Ada.Strings.Unbounded.Unbounded_String := Ada.Strings.Unbounded.To_Unbounded_String ("HighLowWaterDetector.txt");
   begin
      observedPhenomenon.SetNameTask("Voda            ");
      observedPhenomenon.SetValue(0);
      observedPhenomenon.SetControllableSignal(True);

      Create (Output, Append_File, Ada.Strings.Unbounded.To_String (fileName));
      Put_Line ("Fajl kreiran: " & Ada.Strings.Unbounded.To_String (fileName));
      Put_Line (Output, "Current time:          " & "Data register:    " & "Status register:       "  & "Elapsed time:");

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
            accept SetValueDataRegister (NewValue : Integer) do
               dataRegister := NewValue;
               Put_Line ("Nova vrednost registra podataka: " & dataRegister'Image);
            end SetValueDataRegister;
         or
            accept GetValueDataRegister (Result : out Integer) do
               Result := dataRegister;
            end GetValueDataRegister;
         or
            accept SetHighBoundary (NewValue : Integer) do
               highBoundary := NewValue;
               Put_Line ("Nova najvisa granicna vrednost: " & highBoundary'Image);
            end SetHighBoundary;
         or
            accept SetLowBoundary (NewValue : Integer) do
               lowBoundary := NewValue;
               Put_Line ("Nova najniza granicna vrednost: " & lowBoundary'Image);
            end SetLowBoundary;
         or
            delay until nextActivationSensor;
            nextDeadline := nextActivationSensor + deadline;
            nextActivationSensor := nextActivationSensor + periodSensor;

            select
               delay until nextDeadline;
               Stop_Time    := Clock;
               Elapsed_Time := Stop_Time - Start_Time;
               Close (Output);
               Put_Line (" Za " & nameSensor & " senzor istekao rok izvrsavanja: " & Duration'Image(To_Duration (Elapsed_Time)));
            then abort
               Stop_Time    := Clock;
               Elapsed_Time := Stop_Time - Start_Time;
               Start_Time := Clock;

               dataRegister := currentValue;
               Put_Line (nameSensor & " : " & dataRegister'Image);

               -- random status greske
               i:= randomN;
               if i <=3 then -- OK
                  statusRegister := 1;
               else -- PANIC, ALARM
                  statusRegister := statusRegister + 1;
               end if;

               case statusRegister is
               when 1        => statusString := Ada.Strings.Unbounded.To_Unbounded_String ("OK");
               when 2        => statusString := Ada.Strings.Unbounded.To_Unbounded_String ("ERROR");
               when others   => statusString := Ada.Strings.Unbounded.To_Unbounded_String ("ALARM");
               end case;

               WaterPumpInterruptHandler.getOnOffSignal(onOffSignal);
               if onOffSignal /= previousOffSignal then
                  j := 1;
               end if;

               if j<N+1 then
                  j := j+1;
                  Put_Line ("Ignorisem novu vrednost - " & nameSensor);
               else
                  if dataRegister > highBoundary and statusRegister = 1 and not onOffSignal then
                     WaterPumpInterruptHandler.interruptHandlerHighLevel;
                  elsif dataRegister < lowBoundary and statusRegister = 1 and onOffSignal then
                     WaterPumpInterruptHandler.interruptHandlerLowLevel;
                  end if;
               end if;

               currentTime := Ada.Calendar.Clock;
               Put_Line (Output, Ada.Calendar.Formatting.Image(currentTime) & "         " & dataRegister'Image & "             " & Ada.Strings.Unbounded.To_String(statusString) & "             " & Duration'Image(To_Duration (Elapsed_Time)));
               Close (Output);
               Open (Output, Append_File, Ada.Strings.Unbounded.To_String (fileName));

               previousOffSignal := onOffSignal;

               -- tehnika pomeranja periode
               observedPhenomenon.GetValue(currentValue);
            end select;
         end select;
      end loop;
   end HighLowWaterDetector;

   task body WaterFlowSensor is
      dataRegister : Integer := 0;
      statusRegister : Integer := 0;
      signal : Boolean := False;  -- oznacava da li je pumpa iskljucena (false) ili ukljucena (true)
      previousSignal : Boolean := False;
      nameSensor : String := "Water flow sensor";
      currentValue : Integer := 0;
      previousValue : Integer := 0;
      i : Integer := 0;
      j : Integer := 1;
      N : Integer := 9;
      statusString : Ada.Strings.Unbounded.Unbounded_String := Ada.Strings.Unbounded.To_Unbounded_String ("OK");
      stateString : Ada.Strings.Unbounded.Unbounded_String := Ada.Strings.Unbounded.To_Unbounded_String ("OFF");

      currentTime :  Ada.Calendar.Time := Ada.Calendar.Clock;
      nextActivationSensor : Time := Clock;
      nextDeadline : Time := Clock;
      periodSensor : constant Time_Span := Milliseconds(110);
      deadline : constant Time_Span := Milliseconds(60);
      Start_Time, Stop_Time : Time;
      Elapsed_Time          : Time_Span;

      Output         : File_Type;
      fileName : Ada.Strings.Unbounded.Unbounded_String := Ada.Strings.Unbounded.To_Unbounded_String ("WaterFlowSensor.txt");

   begin
      Create (Output, Append_File, Ada.Strings.Unbounded.To_String (fileName));
      Put_Line ("Fajl kreiran: " & Ada.Strings.Unbounded.To_String (fileName));
      Put_Line (Output, "Current time:          " & "Data register:    " &  "Status register:    " & "Pump state:       "  & "Elapsed time:");
      Start_Time := Clock;

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
            accept GetSignal (Result : out Boolean) do
               Result := signal;
            end GetSignal;
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
            delay until nextActivationSensor;
            nextDeadline := nextActivationSensor + deadline;
            nextActivationSensor := nextActivationSensor + periodSensor;

            select
               delay until nextDeadline;
               Stop_Time    := Clock;
               Elapsed_Time := Stop_Time - Start_Time;
               Close (Output);
               Put_Line (" Za " & nameSensor & " senzor istekao rok izvrsavanja: " & Duration'Image(To_Duration (Elapsed_Time)));
            then abort
               Stop_Time    := Clock;
               Elapsed_Time := Stop_Time - Start_Time;
               Start_Time := Clock;

               previousValue := currentValue;
               Put_Line (nameSensor & " : " & dataRegister'Image);

               dataRegister := currentValue - previousValue;
               WaterPumpInterruptHandler.getOnOffSignal(signal);

               if signal /= previousSignal then
                  j := 1;
               end if;

               -- random status greske
               i:= randomN;
               if i <=3 then -- OK
                  statusRegister := 1;
               else -- PANIC, ALARM
                  statusRegister := statusRegister + 1;
               end if;


               if j<N+1 then
                  j := j+1;
                  Put_Line ("Ignorisem novu vrednost - " & nameSensor);
               else
                  if signal then     -- slucaj kada je pumpa ukljucena
                     if dataRegister >= 1 and statusRegister = 1 then
                        Put_Line ("Alarm: ukljucena pumpa ne ispumpava vodu.");
                     end if;
                  else               -- slucaj kada je pumpa iskljucena
                     if dataRegister < 0 and statusRegister = 1 then
                        Put_Line ("Alarm: Voda se ispumpava dok je pumpa iskljucena.");
                     end if;
                  end if;
               end if;

               currentTime := Ada.Calendar.Clock;

               case statusRegister is
               when 1        => statusString := Ada.Strings.Unbounded.To_Unbounded_String ("OK");
               when 2        => statusString := Ada.Strings.Unbounded.To_Unbounded_String ("ERROR");
               when others   => statusString := Ada.Strings.Unbounded.To_Unbounded_String ("ALARM");
               end case;

               case signal is
               when True    => stateString := Ada.Strings.Unbounded.To_Unbounded_String ("ON");
               when False   => stateString := Ada.Strings.Unbounded.To_Unbounded_String ("OFF");
               end case;

               Put_Line (Output, Ada.Calendar.Formatting.Image(currentTime) & "         " & dataRegister'Image & "                  " & Ada.Strings.Unbounded.To_String(statusString) & "              " & Ada.Strings.Unbounded.To_String(stateString) & "             " & Duration'Image(To_Duration (Elapsed_Time)));
               Close (Output);
               Open (Output, Append_File, Ada.Strings.Unbounded.To_String (fileName));

               previousSignal := signal;

               -- tehnika pomeranja periode
               observedPhenomenon.GetValue(currentValue);
            end select;
         end select;
      end loop;
   end WaterFlowSensor;

   task body WaterPump is
      turnedOn : Boolean := False;  -- oznacava da li je pumpa iskljucena (false) ili ukljucena (true)
      name : String := "Water pump";
      nextActivationSensor : Time := Clock;
      periodSensor : constant Time_Span := Milliseconds(1000);
      Output         : File_Type;
      fileName : Ada.Strings.Unbounded.Unbounded_String := Ada.Strings.Unbounded.To_Unbounded_String ("WaterPump.txt");
      currentTime :  Ada.Calendar.Time := Ada.Calendar.Clock;
      stateString : Ada.Strings.Unbounded.Unbounded_String := Ada.Strings.Unbounded.To_Unbounded_String ("OFF");
   begin
      Create (Output, Append_File, Ada.Strings.Unbounded.To_String (fileName));
      Put_Line ("Fajl kreiran: " & Ada.Strings.Unbounded.To_String (fileName));
      Put_Line (Output, "Current time:          " & "Pump state:   ");

      loop
         select
         --     accept SetNameSensor (NewValue : String) do
         --        name := NewValue;
         --        Put_Line ("Nov naziv: " & name);
         --     end SetNameSensor;
         --  or
         --     accept GetNameSensor (Result : out String) do
         --        Result := name;
         --     end GetNameSensor;
         --  or
            accept GetState (State : out Boolean) do
               State := turnedOn;
            end GetState;
         or
            delay until nextActivationSensor;
            nextActivationSensor := nextActivationSensor + periodSensor;

            Put_Line (name & " novi krug" );
            WaterPumpInterruptHandler.waitForNextInterruptWaterLevel;
            currentTime := Ada.Calendar.Clock;

            if turnedOn then
               turnedOn := False;
               stateString := Ada.Strings.Unbounded.To_Unbounded_String ("OFF");
            else
               turnedOn := True;
               stateString := Ada.Strings.Unbounded.To_Unbounded_String ("ON");
            end if;

            Put_Line (Output, Ada.Calendar.Formatting.Image(currentTime) & "         " & Ada.Strings.Unbounded.To_String (stateString));
            Close (Output);
            Open (Output, Append_File, Ada.Strings.Unbounded.To_String (fileName));

            Put_Line (name & " : " & turnedOn'Image);
         end select;
      end loop;
   end WaterPump;


end PumpControlStation;
