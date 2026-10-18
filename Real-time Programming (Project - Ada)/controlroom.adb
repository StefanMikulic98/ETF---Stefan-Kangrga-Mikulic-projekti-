with Ada.Text_IO; use Ada.Text_IO;
with Ada.Real_Time; use Ada.Real_Time;
with Ada.Strings.Unbounded;
with Ada.Text_IO.Unbounded_IO;
with Ada.Integer_Text_IO;
with Ada.Calendar; --use Ada.Calendar;
with Ada.Calendar.Formatting;--  use  Ada.Calendar.Formatting;
with PumpControlStation; use PumpControlStation; -- za testiranje logike vezano za pumpu
with EnvironmentMonitoringStation; use EnvironmentMonitoringStation;  -- za testiranje CO, methane i airflow senzor

package body ControlRoom is
   environmentMonitoringStationTask: EnvironmentMonitoringStation.EnvironmentMonitoringStationTask;
   highLowWaterDetector: PumpControlStation.HighLowWaterDetector;
   waterFlowSensor: PumpControlStation.WaterFlowSensor;
   waterPump: PumpControlStation.WaterPump;

   task body UserInput is
      OnOff : Boolean := False;
      criticalLevel : Boolean := False;
      name : String := "User Input";
      nextActivationSensor : Time := Clock;
      period : constant Time_Span := Milliseconds(1000);
      --input: Ada.Strings.Unbounded.Unbounded_String;
      input : Integer;
   begin
       Put_Line(name);
      loop
         select   
            accept SetNameTask (NewValue : String) do
               name := NewValue;
               Put_Line ("Nov naziv: " & name);
            end SetNameTask;
         or
            accept GetNameTask (Result : out String) do
               Result := name;
            end GetNameTask;
         or
            delay until nextActivationSensor;
            nextActivationSensor := nextActivationSensor + period;
            Put_Line("Unesi komandu (1 - ukljuci pumpu, 2- iskljuci pumpu, [a-z,A-Z] - za prekid programa): ");
            Ada.Integer_Text_IO.Get(input);
            
            environmentMonitoringStationTask.GetCriticalLevelStatus(criticalLevel);
            PumpControlStation.WaterPumpInterruptHandler.getOnOffSignal(OnOff);
            
            case input is
               when 1        =>               
                  if OnOff then
                     if criticalLevel then
                        Put_Line("Pumpa se iskljucuje zbog kriticnog nivoa CH4");
                        WaterPumpInterruptHandler.interruptHandlerLowLevel;
                     else
                        Put_Line("Pumpa je vec ukljucena"); 
                     end if;
                  else 
                     Put_Line("Pumpa se ukljucuje");
                     WaterPumpInterruptHandler.interruptHandlerHighLevel;
                  end if;
                     
               when 2        => 
                  if OnOff then
                     Put_Line("Pumpa se iskljucuje");
                     WaterPumpInterruptHandler.interruptHandlerLowLevel;
                  else 
                     Put_Line("Pumpa je vec iskljucena");
                  end if;
               when others   => 
                  Put_Line("Pogresan unos");
            end case;
            
            Put_Line("=========================================");
            --  input := Ada.Strings.Unbounded.To_Unbounded_String(Ada.Text_IO.Get_Line);
            --  Ada.Text_IO.Put_Line(Ada.Strings.Unbounded.To_String(input));
            --  Ada.Text_IO.Unbounded_IO.Put_Line(input);              

         end select;
      end loop;
   end UserInput;
   
   task body ControlRoom is
      OnOff : Boolean := False;
      criticalLevel : Boolean := False;
      previousLevel : Boolean := False;
      name : String := "Kontrolna soba";
      nextActivationSensor : Time := Clock;
      period : constant Time_Span := Milliseconds(45);
      Output         : File_Type;
      fileName : Ada.Strings.Unbounded.Unbounded_String := Ada.Strings.Unbounded.To_Unbounded_String ("ControlRoom.txt");
      currentTime :  Ada.Calendar.Time := Ada.Calendar.Clock;
   begin
      Put_Line(name);
      Create (Output, Append_File, Ada.Strings.Unbounded.To_String (fileName));
      Put_Line ("Fajl kreiran: " & Ada.Strings.Unbounded.To_String (fileName));
      Put_Line (Output, "Current time:          " & "Pump state:    " & "Critical Level:   ");
      loop
         select   
            accept SetNameTask (NewValue : String) do
               name := NewValue;
               Put_Line ("Nov naziv: " & name);
            end SetNameTask;
         or
            accept GetNameTask (Result : out String) do
               Result := name;
            end GetNameTask;
         or
            delay until nextActivationSensor;
            nextActivationSensor := nextActivationSensor + period;
            
            environmentMonitoringStationTask.GetCriticalLevelStatus(criticalLevel);
            PumpControlStation.WaterPumpInterruptHandler.getOnOffSignal(OnOff);
            currentTime := Ada.Calendar.Clock;
            
            if criticalLevel /= previousLevel then
               WaterPumpInterruptHandler.setCriticalLevel(criticalLevel);
            end if;
            
            if OnOff then
               if criticalLevel then
                  Put_Line("Pumpa se iskljucuje zbog kriticnog nivoa CH4");
                  WaterPumpInterruptHandler.interruptHandlerLowLevel; 
               end if;
            end if;
            
            Put_Line (Output, Ada.Calendar.Formatting.Image(currentTime) & "         " & OnOff'Image & "             " & criticalLevel'Image);
            Close (Output);
            Open (Output, Append_File, Ada.Strings.Unbounded.To_String (fileName));
            
            previousLevel := criticalLevel;
         end select;
      end loop;
   end ControlRoom;
   

end ControlRoom;
