with Ada.Strings.Fixed; use Ada.Strings.Fixed;
with Ada.Text_IO; use Ada.Text_IO;
with Ada.Real_Time; use Ada.Real_Time;
--pragma Warnings (Off);
--with PumpControlStation; --use PumpControlStation;
--with EnvironmentMonitoringStation; --use EnvironmentMonitoringStation;

package ControlRoom is

   task UserInput is
      entry SetNameTask (NewValue : String);
      entry GetNameTask (Result : out String);
   end UserInput;
   
    task ControlRoom is
      entry SetNameTask (NewValue : String);
      entry GetNameTask (Result : out String);
   end ControlRoom;
   
end ControlRoom;
