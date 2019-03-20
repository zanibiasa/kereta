#include <NewPing.h>

//define semua pin sensor
#define Echo1 2
#define Trig1 3
#define Echo2 4
#define Trig2 5
#define Echo3 6
#define Trig3 7
#define Echo4 8
#define Trig4 9

#define motorKiriForward 10
#define motorKiriReverse 11
#define motorKananForward 12
#define motorKananReverse 13

#define SONAR_NUM 4      // Number or sensors.
#define MAX_DISTANCE 25  // Max distance in cm.
#define PING_INTERVAL 10  // Milliseconds between pings.

unsigned long pingTimer[SONAR_NUM]; // When each pings.
unsigned int cm[SONAR_NUM];         // Store ping distances.
uint8_t currentSensor = 0;          // Which sensor is active.

NewPing sonar[SONAR_NUM] = {
    // Sensor object array.
    NewPing(Trig1, Echo1, MAX_DISTANCE),
    NewPing(Trig2, Echo2, MAX_DISTANCE),
    NewPing(Trig3, Echo3, MAX_DISTANCE),
    NewPing(Trig4, Trig4, MAX_DISTANCE),
};

void setup()
{

    Serial.begin(9600);
    //enable semua pin
    pinMode(Echo1, INPUT);
    pinMode(Trig1, OUTPUT);
    pinMode(Echo2, INPUT);
    pinMode(Echo3, OUTPUT);
    pinMode(Trig3, INPUT);
    pinMode(Echo4, OUTPUT);
    pinMode(Trig4, INPUT);

    pinMode(motorKiriForward, OUTPUT);
    pinMode(motorKiriReverse, OUTPUT);
    pinMode(motorKananForward, OUTPUT);
    pinMode(motorKananReverse, OUTPUT);

    pingTimer[0] = millis() + 75; // First ping start in ms.
    for (uint8_t i = 1; i < SONAR_NUM; i++)
    {
        pingTimer[i] = pingTimer[i - 1] + PING_INTERVAL;
    }
}

void loop()
{
    for (uint8_t i = 0; i < SONAR_NUM; i++)
    {
        if (millis() >= pingTimer[i])
        {
            pingTimer[i] += PING_INTERVAL * SONAR_NUM;
            if (i == 0 && currentSensor == SONAR_NUM - 1)
            {
                oneSensorCycle(); // Do something with results.
            }
            sonar[currentSensor].timer_stop();
            currentSensor = i;
            cm[currentSensor] = 0;
            sonar[currentSensor].ping_timer(echoCheck);
        }
    }
}


void echoCheck() { // If ping echo, set distance to array.
  if (sonar[currentSensor].check_timer())
    cm[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;
}


void oneSensorCycle() { // Do something with the results.
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    Serial.print(i);
    Serial.print("=");
    Serial.print(cm[i]);
    Serial.print("cm ");
  }
  Serial.println();
}

void motorKeKiri()
{
    digitalWrite(motorKiriForward, LOW);
    digitalWrite(motorKiriReverse, HIGH);
    digitalWrite(motorKananForward, HIGH);
    digitalWrite(motorKananReverse, LOW);
}

void motorKeKanan()
{
    digitalWrite(motorKiriForward, HIGH);
    digitalWrite(motorKiriReverse, LOW);
    digitalWrite(motorKananForward, LOW);
    digitalWrite(motorKananReverse, HIGH);
}

void motorKeDepan()
{
    digitalWrite(motorKiriForward, HIGH);
    digitalWrite(motorKiriReverse, LOW);
    digitalWrite(motorKananForward, HIGH);
    digitalWrite(motorKananReverse, LOW);
}

void motorKeBelakang()
{
    digitalWrite(motorKiriForward, LOW);
    digitalWrite(motorKiriReverse, HIGH);
    digitalWrite(motorKananForward, LOW);
    digitalWrite(motorKananReverse, HIGH);
}