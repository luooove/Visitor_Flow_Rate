//程序包含几部分
//1.检测人流和方向
//2.记录时间
//3.存到SD卡上
//4.不工作时候进入睡眠状态
//人数存到EEPRAM

#include <SPI.h>
#include <SD.h>
const int chipSelect = 4;
char Director1 = 0;//flag
long int VisitorsIn = 0;
long int VisitorsOut = 0;
void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  // put your setup code here, to run once:
  attachInterrupt(0, Detect1, RISING );//下降沿说明有
  attachInterrupt(1, Detect2, RISING );//下降沿说明人
}

void loop() {
  // put your main code here, to run repeatedly:

}

void Detect1()
{
  //Serial.println("Detect1()");
  if (Director1 == 0) //means people is go in and not yet pass
  {
    Director1 = 1;
  }
if (Director1 == 2) //means people is going out
  {
    Director1 = 0;
    VisitorsOut ++;
    SD_Data();
  }
}
void Detect2()
{
  //Serial.println("Detect2()");
  if (Director1 == 0) //means people is go out and not yet pass
  {
    Director1 = 2;
  }
  if(Director1 == 1)
  {
    Director1 = 0;
    VisitorsIn ++;
    SD_Data();
  }
}

void SD_Data()
{
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.print("IN:");
    dataFile.print(VisitorsIn);
    dataFile.print("  ");
    dataFile.print("OUT:");
    dataFile.println(VisitorsOut);
    dataFile.close();
    
    Serial.print("IN:");
    Serial.print(VisitorsIn);
    Serial.print("  ");
    Serial.print("OUT:");
    Serial.println(VisitorsOut);
    // print to the serial port too:
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
}
