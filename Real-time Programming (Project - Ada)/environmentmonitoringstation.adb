with Ada.Strings.Fixed; use Ada.Strings.Fixed;
with Ada.Strings.Unbounded;
with Ada.Real_Time; use Ada.Real_Time;
with Ada.Text_IO; use Ada.Text_IO;
with Ada.Calendar; --use Ada.Calendar;
with Ada.Calendar.Formatting;--  use  Ada.Calendar.Formatting;
with RegularSensor; use RegularSensor;


package body EnvironmentMonitoringStation is
   type State is (OK, Panic, Alarm);
   for State use (OK   => 1, Panic    => 2, Alarm  => 3);

   task body EnvironmentMonitoringStationTask is
      COsensor: RegularSensor.RegularSensor;
      methaneSensor: RegularSensor.RegularSensor;
      airFlowSensor: RegularSensor.RegularSensor;
      boundary : Integer := 1000000;
      methaneBoundary : Integer := 1000000;
      nextActivation : Time;
      period : constant Time_Span := Milliseconds(45);
      i : Natural := 0;
      currentLevelCO : Integer := 0;
      currentLevelMethane : Integer := 0;
      currentLevelAirFlow : Integer := 0;
      statusCO : Integer := 0;
      statusMethane : Integer := 0;
      statusAirFlow : Integer := 0;
      errorState : State := OK;
      criticalLevel : Boolean := False;
      Output         : File_Type;
      fileName : Ada.Strings.Unbounded.Unbounded_String := Ada.Strings.Unbounded.To_Unbounded_String ("EnvironmentMonitoringStation.txt");
      fileCreated : Boolean := False;
      currentTime :  Ada.Calendar.Time := Ada.Calendar.Clock;
      message : Ada.Strings.Unbounded.Unbounded_String := Ada.Strings.Unbounded.To_Unbounded_String ("OK");
      
   begin
      
      Put_Line("EnvironmentMonitoringStationTask start");
      
      methaneSensor.SetPeriod(Milliseconds(90));
      methaneSensor.SetDeadline(Milliseconds(40));
      
      COsensor.SetNameSensor("CO sensor     ");
      methaneSensor.SetNameSensor("Methane sensor");
      airFlowSensor.SetNameSensor("Airflow sensor");
      
      COsensor.SetNameNature("CO              ");
      methaneSensor.SetNameNature("Methane         ");
      airFlowSensor.SetNameNature("Air flow        ");
      
      Create (Output, Append_File, Ada.Strings.Unbounded.To_String (fileName));
      fileCreated := True;
      Put_Line ("Fajl kreiran: " & Ada.Strings.Unbounded.To_String (fileName));
      Put_Line (Output, "Current time:          " & "status CO:    " & "status methane:   " & "status air flow:    " & "error state:   " & "message:   ");
      nextActivation := Clock + period;
      loop
         select
            accept GetCriticalLevelStatus (State : out Boolean) do
               State := criticalLevel;
            end GetCriticalLevelStatus;
         or
            delay until nextActivation;
            nextActivation := nextActivation + period;
            message := Ada.Strings.Unbounded.To_Unbounded_String ("OK");
            -- criticalLevel := False;
            
            COsensor.GetValueStatusRegister(statusCO);
            methaneSensor.GetValueStatusRegister(statusMethane);
            airFlowSensor.GetValueStatusRegister(statusAirFlow);
            
            COsensor.GetValueDataRegister(currentLevelCO);
            methaneSensor.GetValueDataRegister(currentLevelMethane);
            airFlowSensor.GetValueDataRegister(currentLevelAirFlow);
            
            if currentLevelMethane > methaneBoundary then
               criticalLevel := True;
               statusMethane := 3;
               Put_Line ("ALARM: Critical level (CH4)");
               message := Ada.Strings.Unbounded.To_Unbounded_String ("ALARM: Critical level (CH4)");
            elsif currentLevelCO > boundary then
               criticalLevel := True;
               statusCO := 3;
               Put_Line ("ALARM: Critical level (CO)");
               message := Ada.Strings.Unbounded.To_Unbounded_String ("ALARM: Critical level (CO)");
            elsif currentLevelAirFlow > boundary then
               criticalLevel := True;
               statusAirFlow := 3;
               Put_Line ("ALARM: Critical level (Air flow)");
               message := Ada.Strings.Unbounded.To_Unbounded_String ("ALARM: Critical level (Air flow)");
            else
               criticalLevel := False;
            end if;
            
            
            case Integer'Max(statusCO, Integer'Max (statusMethane, statusAirFlow)) is
               when 1        =>  errorState := OK;
               when 2        =>  errorState := PANIC;
               when others   =>  
                  errorState := ALARM;
                  if criticalLevel then
                     null;
                  else
                     message := Ada.Strings.Unbounded.To_Unbounded_String ("ALARM: Error status sensor");
                  end if;
            end case;
            
            
            Put_Line ("=====================================================");
            
            if fileCreated then
               currentTime := Ada.Calendar.Clock;       
               Put_Line (Output, Ada.Calendar.Formatting.Image(currentTime) & "         " & statusCO'Image & "             " & statusMethane'Image & "                   " & statusAirFlow'Image & "             " & errorState'Image & "           " & Ada.Strings.Unbounded.To_String (message));
               Close (Output);
               Open (Output, Append_File, Ada.Strings.Unbounded.To_String (fileName));
            end if;
         --or
            --terminate;
         end select;
      end loop;
   end EnvironmentMonitoringStationTask;

end EnvironmentMonitoringStation;
