#ifndef attinyEnergyConf_h
#define attinyEnergyConf_h
struct energyData{
	float realPower;
	float apparentPower;
	float powerFactor;
  float supplyVoltage;
  float Irms;
};
typedef struct energyData EnergyData;
EnergyData ener;
#endif
