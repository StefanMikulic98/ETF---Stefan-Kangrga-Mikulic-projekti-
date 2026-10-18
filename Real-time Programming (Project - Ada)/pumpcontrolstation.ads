with Ada.Strings.Fixed; use Ada.Strings.Fixed;
with Ada.Text_IO; use Ada.Text_IO;
with Ada.Real_Time; use Ada.Real_Time;
with Nature; use Nature;

package PumpControlStation is
   --observedPhenomenon: Nature.NatureTask;
 
   protected WaterPumpInterruptHandler is
      procedure interruptHandlerHighLevel; -- true za high level event i false low level event
      procedure interruptHandlerLowLevel;
      procedure setCriticalLevel(newValue : Boolean);
      procedure setOnOffSignal(newValue : Boolean);
      procedure getOnOffSignal(Result : out Boolean);
      entry waitForNextInterruptWaterLevel;
   private
      criticalLevel : Boolean := False;
      eventHighLevelOccurred : Boolean := False;
      eventLowLevelOccurred : Boolean := False;
      evenOccurred : Boolean := False;
      OnOffSignal : Boolean := False;
   end WaterPumpInterruptHandler;
   
   task type HighLowWaterDetector is
      entry GetValueDataRegister (Result : out Integer);
      entry SetValueDataRegister (NewValue : Integer);
      entry SetNameSensor (NewValue : String);
      entry GetNameSensor (Result : out String);
      entry SetHighBoundary (NewValue : Integer);
      entry SetLowBoundary (NewValue : Integer);
   end HighLowWaterDetector;
   
   task type WaterFlowSensor is
      entry GetValueDataRegister (Result : out Integer);
      entry SetValueDataRegister (NewValue : Integer);
      entry SetNameSensor (NewValue : String);
      entry GetNameSensor (Result : out String);
      entry SetSignal (NewValue : Boolean);
      entry GetSignal (Result : out Boolean);
   end WaterFlowSensor;
   
   task type WaterPump is
      entry GetState (State : out Boolean);
   end WaterPump;
      
end PumpControlStation;
