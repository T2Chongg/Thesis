 // eFFL includes
#include <Fuzzy.h>
#include <FuzzyComposition.h>
#include <FuzzyInput.h>
#include <FuzzyIO.h>
#include <FuzzyOutput.h>
#include <FuzzyRule.h>
#include <FuzzyRuleAntecedent.h>
#include <FuzzyRuleConsequent.h>
#include <FuzzySet.h>

//pin assigments
#define MoistureSensor A0
#define WaterSensor A1
#define WaterPump 6

//object library
Fuzzy *fuzzy = new Fuzzy();

void setup() {
  //PinModes
  Serial.begin(9600);
  pinMode(MoistureSensor, INPUT);
  pinMode(WaterSensor, INPUT);
  pinMode(WaterPump, OUTPUT);


//fuzzy sets
//Soil Moisture
FuzzySet *dry = new FuzzySet(1, 1, 15, 40);
FuzzySet *moist = new FuzzySet(20, 50, 50, 80);
FuzzySet *wet = new FuzzySet(60, 85, 100, 100);

//Water Level
FuzzySet *empty = new FuzzySet(1, 1, 15, 40);
FuzzySet *half = new FuzzySet(20, 50, 50, 80);
FuzzySet *full = new FuzzySet(60, 85, 100, 100);

//Water Output
FuzzySet *verylow = new FuzzySet(0, 0, 15, 30);
FuzzySet *low = new FuzzySet(15, 30, 30, 45);
FuzzySet *medium = new FuzzySet(35, 50, 50, 65);
FuzzySet *high = new FuzzySet(55, 70, 70, 85);
FuzzySet *veryhigh = new FuzzySet(70, 85, 100, 100);

// variables
// variable SoilMoisture with 1-100 as input
FuzzyInput *SoilMoisture = new FuzzyInput(1);
SoilMoisture->addFuzzySet(dry);
SoilMoisture->addFuzzySet(moist);
SoilMoisture->addFuzzySet(wet);
fuzzy->addFuzzyInput(SoilMoisture);

//variable WaterLevel with 0-100 as input
FuzzyInput *WaterLevel = new FuzzyInput(2);
WaterLevel->addFuzzySet(empty);
WaterLevel->addFuzzySet(half);
WaterLevel->addFuzzySet(full);
fuzzy->addFuzzyInput(WaterLevel);

//variable WaterOutput with 0-100 as output
FuzzyOutput *WaterOutput = new FuzzyOutput(1);
WaterOutput->addFuzzySet(verylow);
WaterOutput->addFuzzySet(low);
WaterOutput->addFuzzySet(medium);
WaterOutput->addFuzzySet(high);
WaterOutput->addFuzzySet(veryhigh);
fuzzy->addFuzzyOutput(WaterOutput);

//rules
//if Moisture Level is Dry and Water Level is Empty then Water Output is Low
FuzzyRuleAntecedent *ifMoistureDryAndLevelEmpty = new FuzzyRuleAntecedent();
ifMoistureDryAndLevelEmpty->joinWithAND(dry, empty);
FuzzyRuleConsequent *thenOutputLow = new FuzzyRuleConsequent();
thenOutputLow->addOutput(low);
FuzzyRule *FuzzyRule1 = new FuzzyRule(1, ifMoistureDryAndLevelEmpty, thenOutputLow);
fuzzy->addFuzzyRule(FuzzyRule1);

//if Moisture Level is Dry and Water Level is Half then Water Output is High
FuzzyRuleAntecedent *ifMoistureDryAndLevelHalf = new FuzzyRuleAntecedent();
ifMoistureDryAndLevelHalf->joinWithAND(dry, half);
FuzzyRuleConsequent *thenOutputHigh = new FuzzyRuleConsequent();
thenOutputHigh->addOutput(high);
FuzzyRule *FuzzyRule2 = new FuzzyRule(2, ifMoistureDryAndLevelHalf, thenOutputHigh);
fuzzy->addFuzzyRule(FuzzyRule2);

//if Moisture Level is Dry and Water Level is Full then Water Output is Very High
FuzzyRuleAntecedent *ifMoistureDryAndLevelFull = new FuzzyRuleAntecedent();
ifMoistureDryAndLevelFull->joinWithAND(dry, full);
FuzzyRuleConsequent *thenOutputVeryHigh = new FuzzyRuleConsequent();
thenOutputLow->addOutput(veryhigh);
FuzzyRule *FuzzyRule3 = new FuzzyRule(3, ifMoistureDryAndLevelFull, thenOutputVeryHigh);
fuzzy->addFuzzyRule(FuzzyRule3);

//if Moisture Level is Moist and Water Level is Empty then Water Output is Low
FuzzyRuleAntecedent *ifMoistureMoistAndLevelEmpty = new FuzzyRuleAntecedent();
ifMoistureMoistAndLevelEmpty->joinWithAND(moist, empty);
FuzzyRuleConsequent *thenOutputLow2 = new FuzzyRuleConsequent();
thenOutputLow2->addOutput(low);
FuzzyRule *FuzzyRule4 = new FuzzyRule(4, ifMoistureMoistAndLevelEmpty, thenOutputLow2);
fuzzy->addFuzzyRule(FuzzyRule4);

//if Moisture Level is Moist and Water Level is Half then Water Output is Medium
FuzzyRuleAntecedent *ifMoistureMoistAndLevelHalf = new FuzzyRuleAntecedent();
ifMoistureMoistAndLevelHalf->joinWithAND(moist, half);
FuzzyRuleConsequent *thenOutputMedium = new FuzzyRuleConsequent();
thenOutputMedium->addOutput(medium);
FuzzyRule *FuzzyRule5 = new FuzzyRule(5, ifMoistureMoistAndLevelHalf, thenOutputMedium);
fuzzy->addFuzzyRule(FuzzyRule5);

//if Moisture Level is Moist and Water Level is Full then Water Output is High
FuzzyRuleAntecedent *ifMoistureMoistAndLevelFull = new FuzzyRuleAntecedent();
ifMoistureMoistAndLevelFull->joinWithAND(moist, full);
FuzzyRuleConsequent *thenOutputHigh2 = new FuzzyRuleConsequent();
thenOutputHigh2->addOutput(high);
FuzzyRule *FuzzyRule6 = new FuzzyRule(6, ifMoistureMoistAndLevelFull, thenOutputHigh2);
fuzzy->addFuzzyRule(FuzzyRule6);\

//if Moisture Level is Wet and Water Level is Empty then Water Output is Very Low
FuzzyRuleAntecedent *ifMoistureWetAndLevelEmpty = new FuzzyRuleAntecedent();
ifMoistureWetAndLevelEmpty->joinWithAND(wet, empty);
FuzzyRuleConsequent *thenOutputVeryLow = new FuzzyRuleConsequent();
thenOutputVeryLow->addOutput(verylow);
FuzzyRule *FuzzyRule7 = new FuzzyRule(7, ifMoistureWetAndLevelEmpty, thenOutputVeryLow);
fuzzy->addFuzzyRule(FuzzyRule7);

//if Moisture Level is Wet and Water Level is Half then Water Output is Very Low
FuzzyRuleAntecedent *ifMoistureWetAndLevelHalf = new FuzzyRuleAntecedent();
ifMoistureWetAndLevelHalf->joinWithAND(wet, half);
FuzzyRuleConsequent *thenOutputVeryLow2 = new FuzzyRuleConsequent();
thenOutputVeryLow2->addOutput(verylow);
FuzzyRule *FuzzyRule8 = new FuzzyRule(8, ifMoistureWetAndLevelHalf, thenOutputVeryLow2);
fuzzy->addFuzzyRule(FuzzyRule8);

//if Moisture Level is Wet and Water Level is Full then Water Output is Very Low
FuzzyRuleAntecedent *ifMoistureWetAndLevelFull = new FuzzyRuleAntecedent();
ifMoistureWetAndLevelFull->joinWithAND(wet, full);
FuzzyRuleConsequent *thenOutputVeryLow3 = new FuzzyRuleConsequent();
thenOutputVeryLow3->addOutput(verylow);
FuzzyRule *FuzzyRule9 = new FuzzyRule(9, ifMoistureWetAndLevelFull, thenOutputVeryLow3);
fuzzy->addFuzzyRule(FuzzyRule9);
}

//return Soil Moisture
int soilmoisture() {
  return analogRead(MoistureSensor);
}

//return Water Level
int waterlevel() {
  return analogRead(WaterSensor);
}

//main loop
void loop() {
  int moisture = soilmoisture();
  int level = waterlevel();

  //map
  moisture = map(moisture, 0, 1023, 0, 100);
  level = map(level, 0, 1023, 0, 100);

  //Fuzzification Process
  fuzzy->setInput(1, moisture); //sets "moisture" as FuzzyInput1 (Soil Moisture)
  fuzzy->setInput(2, level); //sets "level" as FuzzyInput2 (Water Level)
  fuzzy->fuzzify();

  //Defuzzyfication Process
  int output = fuzzy->defuzzify(1); //defuzzify FuzzyOutput1

  //Outputs
  if (output>80 && output<100) {
    digitalWrite(WaterPump, HIGH);
    delay(10000);
  } else if (output>60 && output<81) {
    digitalWrite(WaterPump, HIGH);
    delay(8000);
  }else if (output>40 && output<61) {
    digitalWrite(WaterPump, HIGH);
    delay(6000);
  }else if (output>20 && output<41) {
    digitalWrite(WaterPump, HIGH);
    delay(4000);
  }else if (output>0 && output<21) {
    digitalWrite(WaterPump, HIGH);
    delay(2000);
  }
}

//Serial Monitor
void print(int moisture, int level, int output) {
  Serial.print("Soil Moisture: ");
  Serial.print(moisture);
  Serial.print("  Water Level: ");
  Serial.print(level);
  Serial.print("  Water Pump Output: ");
  Serial.print(output);
  Serial.println();
}
