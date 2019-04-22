#ifndef to_pic_h
#define to_pic_h
//TOPIC COMANDO IN INGRESSO -> subscrive
const char* riscaldaTopic = "homie/esterno/caldaia/relay"; // 0 o 1 per attivare il riscaldamento
const char* acquaTopic ="homie/esterno/caldaia/acqua";  //0 o 1 per attivare il preriscaldamento acqua
const char* resetTopic ="homie/esterno/caldaia/reset"; //0 o 1 per premere pulsante reset
//TOPIC DI RISPOSTA/ALLARME -> publish
const char* alarmTopic ="homie/esterno/caldaia/alarm";   //ON OFF allarme blocco attivo
const char* extSensTopic ="homie/esterno/sensori"; // temp H20 caldaia
const char* powerTopic ="homie/esterno/caldaia/power"; // apertura valvola gas caldaia
const char* logTopic ="homie/log"; // log generico per lo piu non usato
const char* casaSensTopic = "homie/interno/sensori";
const char* systemTopic = "homie/general";
const char* updateTopic = "homie/update";
//1= caldaia
const char* teleTopic = "homie/telegram";
#endif
