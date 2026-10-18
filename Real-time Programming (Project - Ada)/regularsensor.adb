with Ada.Strings.Fixed; use Ada.Strings.Fixed;
with Ada.Strings.Unbounded;
with Ada.Text_IO; use Ada.Text_IO;
with Ada.Real_Time; use Ada.Real_Time;
with Ada.Calendar; --use Ada.Calendar;
with Ada.Calendar.Formatting;--  use  Ada.Calendar.Formatting;
with Nature; use Nature;

package body RegularSensor is

   task body RegularSensor is
      observedPhenomenon : Nature.NatureTask;
      nameSensor : String := "Unknown sensor";
      i : Integer := 0;
      currentValue : Integer := 0;

      dataRegister : Integer := 0;
      statusRegister : Integer := 1;
      statusString : Ada.Strings.Unbounded.Unbounded_String := Ada.Strings.Unbounded.To_Unbounded_String ("OK");
      
      currentTime :  Ada.Calendar.Time := Ada.Calendar.Clock;
      nextActivationSensor : Time := Clock;
      nextDeadline : Time := Clock;
      periodSensor : Time_Span := Milliseconds(150);
      deadline : Time_Span := Milliseconds(100);
      Start_Time, Stop_Time : Time;
      Elapsed_Time          : Time_Span;

      Output         : File_Type;
      fileName : Ada.Strings.Unbounded.Unbounded_String := Ada.Strings.Unbounded.To_Unbounded_String ("empty.txt");
      fileCreated : Boolean := False;
   begin
      observedPhenomenon.SetValue(0);
      Start_Time := Clock;
      loop
         select
            accept SetNameSensor (NewValue : String) do
               nameSensor := NewValue;
               Put_Line ("Nov naziv: " & nameSensor);
               
               fileName := Ada.Strings.Unbounded.To_Unbounded_String(nameSensor & ".txt");
               Create (Output, Append_File, Ada.Strings.Unbounded.To_String (fileName));
               fileCreated := True;
               Put_Line ("Fajl kreiran: " & Ada.Strings.Unbounded.To_String (fileName));
               Put_Line (Output, "Current time:          " & "Data register:          " & "Status register:         " & "Elapsed time:");
            end SetNameSensor;
         or
            accept GetnameSensor (Result : out String) do
               Result := nameSensor;
            end GetnameSensor;
         or
            accept SetNameNature (NewValue : String) do
               observedPhenomenon.SetNameTask(NewValue);
               --Put_Line ("Nov naziv pracene pojave: " & NewValue); --vec ce se ispisati
            end SetNameNature;
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
            accept SetValueStatusRegister (NewValue : Integer) do
               statusRegister := NewValue;
               Put_Line ("Nova vrednost statusnog registra: " & statusRegister'Image);
            end SetValueStatusRegister;
         or
            accept GetValueStatusRegister (Result : out Integer) do
               Result := statusRegister;
            end GetValueStatusRegister;
         or
            accept SetPeriod (NewValue : Time_Span) do
               periodSensor := NewValue;
               Put_Line ("Nova vrednost periode senzora: " & Duration'Image(To_Duration (periodSensor)));
            end SetPeriod;
         or
            accept SetDeadline (NewValue : Time_Span) do
               deadline := NewValue;
               Put_Line ("Nova vrednost roka izvrsavanja senzora: " & Duration'Image(To_Duration (deadline)));
            end SetDeadline;
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

               -- Kraj AD konverzije
               dataRegister := currentValue;
            
               -- random status greske da se doda
               i:= randomN;
               if i <=3 then -- OK
                  statusRegister := 1;
               else -- PANIC, ALARM
                  statusRegister := statusRegister + 1;
               end if;
            
               Put_Line (nameSensor & " data: " & dataRegister'Image);
               Put_Line (nameSensor & " status: " & statusRegister'Image);
            
               if fileCreated then
                  currentTime := Ada.Calendar.Clock;
               
                  case statusRegister is
                  when 1        => statusString := Ada.Strings.Unbounded.To_Unbounded_String ("OK");
                  when 2        => statusString := Ada.Strings.Unbounded.To_Unbounded_String ("ERROR");
                  when others   => statusString := Ada.Strings.Unbounded.To_Unbounded_String ("ALARM");
                  end case;
               
                  Put_Line (Output, Ada.Calendar.Formatting.Image(currentTime) & "         " & dataRegister'Image & "                       " & Ada.Strings.Unbounded.To_String(statusString) & "             " & Duration'Image(To_Duration (Elapsed_Time)));
                  Close (Output);
                  Open (Output, Append_File, Ada.Strings.Unbounded.To_String (fileName));
               end if;
               
               -- tehnika pomeranja periode
               observedPhenomenon.GetValue(currentValue);
               --delay 0.07; -- za testiranje kraj roka
            end select;
         end select;
      end loop;
   end RegularSensor;

end RegularSensor;
