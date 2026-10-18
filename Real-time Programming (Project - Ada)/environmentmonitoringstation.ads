package EnvironmentMonitoringStation is
   task type EnvironmentMonitoringStationTask is
      entry GetCriticalLevelStatus (State : out Boolean);
   end EnvironmentMonitoringStationTask;
end EnvironmentMonitoringStation;
