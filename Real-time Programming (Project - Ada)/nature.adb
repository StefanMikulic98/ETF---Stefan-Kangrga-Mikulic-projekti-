with Ada.Strings.Fixed; use Ada.Strings.Fixed;
with Ada.Strings.Unbounded;
with Ada.Text_IO; use Ada.Text_IO;
with Ada.Real_Time; use Ada.Real_Time;
with Ada.Strings;       use Ada.Strings;
with Ada.Calendar; --use Ada.Calendar;
with Ada.Calendar.Formatting;--  use  Ada.Calendar.Formatting;
with ada.numerics.discrete_random;

package body Nature is   
   
   function randomN return Integer is
      type randRange is new Integer range 1..4;
      package Rand_Int is new ada.numerics.discrete_random(randRange);
      use Rand_Int;
      gen : Generator;
      num : randRange;
      result : Integer;
   begin
      reset(gen);
      num := random(gen);
      result := Integer(num);
      --put_line(randRange'Image(num));
      return result;
   end randomN;

   task body NatureTask is
      Value : Integer := 30;
      Diff : Integer := 0;
      Controllable : Boolean := False;   -- za uticaj na rast i opadanje pojave
      OnSignal : Boolean := False; -- za oduzimanje
      OffSignal : Boolean := True; -- za dodavanje
      fileNotCreated : Boolean := True;
      fileCreated : Boolean := False;
      Name : String := "Nepoznata pojava";
      nextActivationSensor : Time := Clock;
      currentTime :  Ada.Calendar.Time := Ada.Calendar.Clock;
      period : constant Time_Span := Milliseconds(50);
      i : Integer;
      Output         : File_Type;
      fileName : Ada.Strings.Unbounded.Unbounded_String := Ada.Strings.Unbounded.To_Unbounded_String ("empty.txt");

   begin
      loop  
         select   
            accept SetNameTask (NewValue : String) do
               Name := NewValue;
               fileName := Ada.Strings.Unbounded.To_Unbounded_String(Name & ".txt");
               Put_Line ("Nov naziv pracene pojave: " & Name);
            end SetNameTask;
         or
            accept GetNameTask (Result : out String) do
               Result := Name;
            end GetNameTask;
         or
            accept SetControllableSignal (NewValue : Boolean) do
               Controllable := NewValue;
               Put_Line ("Nova Controllable vrednost: " & Controllable'Image);
            end SetControllableSignal;
         or
            accept SetOnSignal do
               OnSignal := True;
               OffSignal := False;
               Put_Line ("Nova OnSignal vrednost: " & OnSignal'Image);
            end SetOnSignal;
         or
            accept SetOffSignal do
               OnSignal := False;
               OffSignal := True;
               Put_Line ("Nova OffSignal vrednost: " & OffSignal'Image);
            end SetOffSignal;
         or
            accept SetValue (NewValue : Integer) do
               Value := NewValue;
               Put_Line ("Nova vrednost " & Name & " : " & Value'Image);
            end SetValue;
         or
            accept SetDiff (NewValue : Integer) do
               Diff := NewValue;
               Put_Line ("Nova razlika " & Name & " : " & Diff'Image);
            end SetDiff;
         or
            accept GetValue (Result : out Integer) do
               Result := Value;
            end GetValue;
         or
            delay until nextActivationSensor;
            nextActivationSensor := nextActivationSensor + period;
            Diff := randomN;
            if Controllable then
               if OnSignal then
                  Value := Value + Diff - 5;
                  if Value < 0 then
                     Value := 0
                  end if;
               end if;
               if OffSignal then
                  Value := Value + Diff;
               end if;
            else
               i:= randomN;
               if i <=2 then -- sabiranje
                  Value := Value + Diff;
               else -- oduzimanje
                  Value := Value - Diff;
               end if;
            end if;
            
            if fileNotCreated and Name /= "Nepoznata pojava"  then
               begin
                  Create (Output, Append_File, Ada.Strings.Unbounded.To_String (fileName));
                  exception
                  when others =>
                      Put_Line("Neuspesno kreiranje fajla '" & Ada.Strings.Unbounded.To_String (fileName) & "'.");
                     --Set_Exit_Status (Failure);
               end;
               
               fileNotCreated := False;
               Put_Line ("Fajl kreiran: " & Ada.Strings.Unbounded.To_String (fileName));
               fileCreated := True;
            end if;
            
            Put_Line (Name & " : " & Value'Image);  -- ZA TESTIRANJE
            
            if fileCreated then
               currentTime := Ada.Calendar.Clock;
               Put_Line (Output, "Current time: " & Ada.Calendar.Formatting.Image(currentTime) & " ,        " & Name & " : " & Value'Image);
               Close (Output);
               Open (Output, Append_File, Ada.Strings.Unbounded.To_String (fileName));
            end if;
         end select;
      end loop;
   end NatureTask;

end Nature;
