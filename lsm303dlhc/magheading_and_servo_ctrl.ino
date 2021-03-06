#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Servo.h> 

Servo myServo;
//#include <math.h>

/* Assign a unique ID to this sensor at the same time */
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);

void displaySensorDetails(void)
{
  sensor_t sensor;
  mag.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" uT");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" uT");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" uT");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void setup(void) 
{
  Serial.begin(9600);
  Serial.println("Magnetometer Test"); Serial.println("");
  
  /* Enable auto-gain */
  mag.enableAutoRange(true);
  
  /* Initialise the sensor */
  if(!mag.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }
  
  /* Display some basic information on this sensor */
  displaySensorDetails();

  //usage: servo.attach(pin, minPWM, maxPWM)
  myServo.attach(5, 600, 2400);
  myServo.writeMicroseconds(1500);
  delay(5000);
  myServo.writeMicroseconds(2400);
  delay(5000);
  myServo.writeMicroseconds(600);
  delay(5000);
}

void loop(void) 
{
  /* Get a new sensor event */ 
  sensors_event_t event; 
  mag.getEvent(&event);

 double az = atan2(event.magnetic.y, event.magnetic.x) *180/PI -10; //-10 is calibration of magentic declination for waterloo area so that the compass points to true north instead of magnetic north 
 
  Serial.print("Az: "); Serial.print(az); Serial.println("  ");
  //Display the results (magnetic vector values are in micro-Tesla (uT)) 
 /*
 Serial.print("X: "); Serial.print(event.magnetic.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.magnetic.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.magnetic.z); Serial.print("  ");Serial.println("uT");
 */
 myServo.writeMicroseconds( 1500+ az*10);
 delay(500);
}
