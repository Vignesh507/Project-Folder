#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

int led = 12;          // D7
int flame_sensor = 13; // D6
int buzzer = 4;        // D2
int relay = 5;         // D1
int smoke_sensor = A0; // A0
int temp_smoke_sensor;
int flame_sensor_read;

char auth[] = "Vmfy9NMjT84nXFuZQMtTvR_7WAo8bKi8";
char ssid[] = "";
char pass[] = "1883311M3";

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(flame_sensor, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(smoke_sensor, INPUT);
  
  digitalWrite(led, LOW);
  digitalWrite(buzzer, LOW);
  digitalWrite(relay, LOW);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop() 

{
  flame_sensor_read = digitalRead(flame_sensor);
  Blynk.virtualWrite(V0, flame_sensor_read); 
  Serial.print("Flame Status:");
  Serial.println(flame_sensor_read);
  int led_status = digitalRead(led);
  if (led_status == HIGH)
  {
    Blynk.virtualWrite(V1, 255);
  }
  else
  {
    Blynk.virtualWrite(V1, 0);
  }
  
  temp_smoke_sensor = analogRead(smoke_sensor);
  Blynk.virtualWrite(V2, temp_smoke_sensor);
  Serial.print("Current Gas Level:");
  Serial.println(temp_smoke_sensor);
  if (temp_smoke_sensor > 1000)
  {
    digitalWrite(led, HIGH);
    digitalWrite(buzzer, HIGH);
    digitalWrite(relay, HIGH);
    Blynk.notify("Alert Smoke Detected");  
    }
  else
    {
     digitalWrite(led, LOW);
     digitalWrite(buzzer, LOW);
     digitalWrite(relay, LOW);
    }

if (flame_sensor_read == 0)
    {
    digitalWrite(led, HIGH);
    digitalWrite(buzzer, HIGH);
    digitalWrite(relay, HIGH);
    Blynk.notify("Alert Fire Detected");  
    }
  else
      {
      digitalWrite(led, LOW);
      digitalWrite(buzzer, LOW);
      digitalWrite(relay, LOW);
      }
      delay(200);
      Blynk.run();
}
