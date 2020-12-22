/* Okubo Heavy Industries QT PY Satellite Tracker


 ** PLACE THE LATEST TLE IN THE BOX BELOW TO MAP VARIABLES FOR NEXT TIME!! **
 * 
 * https://celestrak.com/NORAD/elements/
 
 * 
ISS (ZARYA)             
1 25544U 98067A   20354.89281063  .00001225  00000-0  30174-4 0  9990
2 25544  51.6438 149.5966 0001647 143.4601  22.1577 15.49201828260806
 * 
 NOAA 15                 
1 25338U 98030A   20354.81408387  .00000017  00000-0  25430-4 0  9990
2 25338  98.7011  18.7729 0011433  84.6784 275.5700 14.26004618175643
 *
 NOAA 18                 
1 28654U 05018A   20354.74727633  .00000097  00000-0  76996-4 0  9999
2 28654  99.0206  52.6855 0015106  71.0374 289.2433 14.12565845803169
 *
NOAA 19                 
1 33591U 09005A   20354.05656173  .00000009  00000-0  30556-4 0  9994
2 33591  99.1935   4.1966 0013072 279.1717  80.7974 14.12444576611452
 */

#include <U8g2lib.h>
#include <TinyGPS++.h> 
#include <ArduinoP13.h>
#include <Time.h>

const char *tleName = "ISS (ZARYA)";
const char *tlel1   = "1 25544U 98067A   20354.89281063  .00001225  00000-0  30174-4 0  9990";
const char *tlel2   = "2 25544  51.6438 149.5966 0001647 143.4601  22.1577 15.49201828260806";

const char *nitleName = "NOAA 15";
const char *nitlel1   = "1 25338U 98030A   20354.81408387  .00000017  00000-0  25430-4 0  9990";
const char *nitlel2   = "2 25338  98.7011  18.7729 0011433  84.6784 275.5700 14.26004618175643";

const char *santleName = "NOAA 18";
const char *santlel1   = "1 28654U 05018A   20354.74727633  .00000097  00000-0  76996-4 0  9999";
const char *santlel2   = "2 28654  99.0206  52.6855 0015106  71.0374 289.2433 14.12565845803169";

const char *yontleName = "NOAA 19";
const char *yontlel1   = "1 33591U 09005A   20354.05656173  .00000009  00000-0  30556-4 0  9994";
const char *yontlel2   = "2 33591  99.1935   4.1966 0013072 279.1717  80.7974 14.12444576611452";


const char  *pcMyName = "OHI";    // Observer name


double       dfreqRX  = 137.100;     // Nominal downlink frequency
double       dfreqTX  = 437.800;     // Nominal uplink frequency


double       dSatLAT  = 0;           // Satellite latitude
double       dSatLON  = 0;           // Satellite longitude
double       dSatAZ   = 0;           // Satellite azimuth
double       dSatEL   = 0;           // Satellite elevation

double       nidfreqRX  = 137.100;     // Nominal downlink frequency
double       nidfreqTX  = 437.800;     // Nominal uplink frequency


double       nidSatLAT  = 0;           // Satellite latitude
double       nidSatLON  = 0;           // Satellite longitude
double       nidSatAZ   = 0;           // Satellite azimuth
double       nidSatEL   = 0;           // Satellite elevation

double       sandfreqRX  = 137.100;     // Nominal downlink frequency
double       sandfreqTX  = 437.800;     // Nominal uplink frequency


double       sandSatLAT  = 0;           // Satellite latitude
double       sandSatLON  = 0;           // Satellite longitude
double       sandSatAZ   = 0;           // Satellite azimuth
double       sandSatEL   = 0;           // Satellite elevation

double       yondfreqRX  = 137.100;     // Nominal downlink frequency
double       yondfreqTX  = 437.800;     // Nominal uplink frequency


double       yondSatLAT  = 0;           // Satellite latitude
double       yondSatLON  = 0;           // Satellite longitude
double       yondSatAZ   = 0;           // Satellite azimuth
double       yondSatEL   = 0;           // Satellite elevation

double       dSunLAT  = 0;           // Sun latitude
double       dSunLON  = 0;           // Sun longitude
double       dSunAZ   = 0;           // Sun azimuth
double       dSunEL   = 0;           // Sun elevation

char         acBuffer[20];            // Buffer for ASCII time

static const uint32_t GPSBaud = 9600;

TinyGPSPlus gps;

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);  //change this depending on your OLED model

// setup the terminal (U8G2LOG) and connect to u8g2 for automatic refresh of the display
// The size (width * height) depends on the selected font and the display
// assume 4x6 font
#define U8LOG_WIDTH 31
#define U8LOG_HEIGHT 4
uint8_t u8log_buffer[U8LOG_WIDTH*U8LOG_HEIGHT*10];
U8G2LOG u8g2log;

int gpschar; 
 
void setup () 
{
  
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
 

 pinMode(9, OUTPUT);
  
  // Serial.begin(115200);  // for the debug

  Serial1.begin(GPSBaud);

  u8g2.begin();  
  u8g2log.begin(U8LOG_WIDTH, U8LOG_HEIGHT, u8log_buffer);
  u8g2log.setLineHeightOffset(1); // set extra space between lines in pixel, this can be negative
  u8g2log.setRedrawMode(1);   // 0: Update screen with newline, 1: Update screen for every char   
  
}
 
void loop() 

{

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_u8glib_4_tr);    // u8g2 font 
   

    u8g2.drawFrame(0, 0, 128,64);  //setup fixed screen info and borders
    u8g2.drawLine(0, 9, 128,9);
    u8g2.drawLine(0, 28, 128,28);
    u8g2.drawStr(2, 7, "SAT TRACKER ");
    
    u8g2.drawLine(0, 54, 128,54);
    u8g2.drawStr(2, 61, "OKUBO HEAVY INDUSTRIES");
   


  while (Serial1.available()>0)
      {  gpschar = Serial1.read(); //read raw gps data to gpschar
        Serial.write(gpschar);  // uncomment to send raw gps over Serial to debug
      //  u8g2log.write(gpschar);   // write raw gps data to u8g2log buffer
        gps.encode(gpschar);      // extract useful info from raw gps data
      }
  
 // u8g2.drawLog(3, 35, u8g2log);     // draw the log content on the display
  
     double lat_val, lng_val, alt_m_val;
     uint8_t hr_val, min_val, sec_val, hr_val_jp, sats_val;
     bool loc_valid, alt_valid, time_valid, sats_valid;
     lat_val = gps.location.lat();  /* Get latitude data */
     loc_valid = gps.location.isValid(); /* Check if valid location data is available */
     lng_val = gps.location.lng(); /* Get longtitude data */
     alt_m_val = gps.altitude.meters();  /* Get altitude data in meters */
     alt_valid = gps.altitude.isValid(); /* Check if valid altitude data is available */
     hr_val = gps.time.hour(); /* Get hour */
     min_val = gps.time.minute();  /* Get minutes */
     sec_val = gps.time.second();  /* Get seconds */
     time_valid = gps.time.isValid();  /* Check if valid time data is available */
      double year_val = (gps.date.year());
      double month_val = (gps.date.month());
      double day_val = (gps.date.day());
     sats_valid = gps.satellites.isValid();
     sats_val = gps.satellites.value();


      double dMyLAT = gps.location.lat();
      double dMyLON = gps.location.lng();
      double dMyALT = gps.altitude.meters();
        
        //P13Sun Sun;                                                       // Create object for the sun
        P13DateTime MyTime(year_val, month_val, day_val, hr_val, min_val, sec_val); // Set start time for the prediction
        P13Observer MyQTH(pcMyName, dMyLAT, dMyLON, dMyALT);              // Set observer coordinates

        P13Satellite MySAT(tleName, tlel1, tlel2);                        // Create ISS data from TLE

        P13Satellite MySAT2(nitleName, nitlel1, nitlel2);                        // Create NOAA15 data from TLE

        P13Satellite MySAT3(santleName, santlel1, santlel2);                        // Create NOAA18 data from TLE

        P13Satellite MySAT4(yontleName, yontlel1, yontlel2);                        // Create NOAA19 data from TLE

        
     
     if (hr_val < 15) { hr_val_jp = hr_val + 9;  // convert UTC to Japan time zone
     }
     else {hr_val_jp = hr_val -15;
     }

     
     if (!loc_valid)
      {          
      
        u8g2.drawStr(3, 16, "LAT : ********");
        
        u8g2.drawStr(60, 16, "LON : ********");
        
       }
       else
       {
          u8g2.drawStr(3, 16, "LAT :");
          u8g2.setCursor(22, 16);
          u8g2.println(lat_val, 6);
          
          
          u8g2.drawStr(60, 16, "LON :");
          u8g2.setCursor(79, 16);
          u8g2.println(lng_val, 6);
          
        }
        if (!alt_valid)
        {
          
          u8g2.drawStr(3, 24, "ALT : ********");
        }
        else
        {
           
          u8g2.drawStr(3, 24, "ALT :");
          u8g2.setCursor(22, 24);
          u8g2.println(alt_m_val, 2);   
        }
        
        if (!sats_valid)
        {
          
          u8g2.drawStr(60, 24, "SAT : **");
        }
        else
        {
         
          u8g2.drawStr(60, 24, "SAT :");
          u8g2.setCursor(79, 24);
          u8g2.println(sats_val, 1);   
        }
        
        if (!time_valid)
        {
          u8g2.drawStr(65, 7, "Time : ********");
         
        }
        else
        {
          char time_string[32];
          sprintf(time_string, "Time : %02d:%02d:%02d \n", hr_val_jp, min_val, sec_val);
          u8g2.setCursor(65, 7);
          u8g2.print(time_string);    
        }
  
   // u8g2.drawLog(3, 35, u8g2log);     // draw the log content on the display

   //satellite tx rx stuff


        double       dfreqRX  = 145.8000;     // Nominal downlink frequency
        double       dfreqTX  = 144.490;     // Nominal uplink frequency

        double       nidfreqRX  = 137.6200;     // Nominal downlink frequency
        double       nidfreqTX  = 000.000;     // Nominal uplink frequency

        double       sandfreqRX  = 137.9125;     // Nominal downlink frequency
        double       sandfreqTX  = 000.000;     // Nominal uplink frequency

        double       yondfreqRX  = 137.1000;     // Nominal downlink frequency
        double       yondfreqTX  = 000.000;     // Nominal uplink frequency

  

        
  
        MyTime.ascii(acBuffer);             // Get time for prediction as ASCII string
        MySAT.predict(MyTime);              // Predict ISS for specific time
        MySAT.latlon(dSatLAT, dSatLON);     // Get the rectangular coordinates
        MySAT.elaz(MyQTH, dSatEL, dSatAZ);  // Get azimut and elevation for MyQTH

        MySAT2.predict(MyTime);              // Predict NOAA15 for specific time
        MySAT2.latlon(nidSatLAT, nidSatLON);     // Get the rectangular coordinates
        MySAT2.elaz(MyQTH, nidSatEL, nidSatAZ);  // Get azimut and elevation for MyQTH

        MySAT3.predict(MyTime);              // Predict NOAA18 for specific time
        MySAT3.latlon(sandSatLAT, sandSatLON);     // Get the rectangular coordinates
        MySAT3.elaz(MyQTH, sandSatEL, sandSatAZ);  // Get azimut and elevation for MyQTH

        MySAT4.predict(MyTime);              // Predict NOAA19 for specific time
        MySAT4.latlon(yondSatLAT, yondSatLON);     // Get the rectangular coordinates
        MySAT4.elaz(MyQTH, yondSatEL, yondSatAZ);  // Get azimut and elevation for MyQTH
        
        //Serial.print(dSatEL);
        //Serial.print("\n ");
        
        if (dSatEL <= 8) {                  //set lights for a pass higher than 8 degrees
         digitalWrite (0, LOW);}
        else { digitalWrite (0, HIGH);}

        if (nidSatEL <= 8) {
         digitalWrite (1, LOW);}
        else { digitalWrite (1, HIGH);}

        if (sandSatEL <= 8) {
         digitalWrite (2, LOW);}
        else { digitalWrite (2, HIGH);}

        if (yondSatEL <= 8) {
         digitalWrite (3, LOW);}
        else { digitalWrite (3, HIGH);}


        if (sec_val < (15)) {        
        u8g2log.print(" ISS   ");
        u8g2log.print(acBuffer);
        
        u8g2log.print("\n");
        u8g2log.print("Lat: ");
        u8g2log.print(dSatLAT,4);
        u8g2log.print("  Lon: ");
        u8g2log.print(dSatLON,4);

        
 
          u8g2log.print("\n");
          u8g2log.print("Az: ");
          u8g2log.print(dSatAZ,2);
          u8g2log.print("   El: ");
          u8g2log.println(dSatEL,2); 
          
         
          u8g2log.print("RX: ");
          u8g2log.print(MySAT.doppler(dfreqRX, P13_FRX),6);
          u8g2log.print(", TX: ");
          u8g2log.println(MySAT.doppler(dfreqTX, P13_FTX),6);

        }

        else if   (sec_val >= (15) && sec_val < (30)){

          u8g2log.print(" NOAA 15   ");
        u8g2log.print(acBuffer);
        
        u8g2log.print("\n");
        u8g2log.print("Lat: ");
        u8g2log.print(nidSatLAT,4);
        u8g2log.print("  Lon: ");
        u8g2log.print(nidSatLON,4);

        
 
          u8g2log.print("\n");
          u8g2log.print("Az: ");
          u8g2log.print(nidSatAZ,2);
          u8g2log.print("   El: ");
          u8g2log.println(nidSatEL,2); 
          
         
          u8g2log.print("RX: ");
          u8g2log.print(MySAT2.doppler(nidfreqRX, P13_FRX),6);
          u8g2log.print(", TX: ");
          u8g2log.println(MySAT2.doppler(nidfreqTX, P13_FTX),6);

          
        }

        else if   (sec_val >= (30) && sec_val < (45)){

          u8g2log.print(" NOAA 18   ");
        u8g2log.print(acBuffer);
        
        u8g2log.print("\n");
        u8g2log.print("Lat: ");
        u8g2log.print(sandSatLAT,4);
        u8g2log.print("  Lon: ");
        u8g2log.print(sandSatLON,4);

        
 
          u8g2log.print("\n");
          u8g2log.print("Az: ");
          u8g2log.print(sandSatAZ,2);
          u8g2log.print("   El: ");
          u8g2log.println(sandSatEL,2); 
          
         
          u8g2log.print("RX: ");
          u8g2log.print(MySAT3.doppler(sandfreqRX, P13_FRX),6);
          u8g2log.print(", TX: ");
          u8g2log.println(MySAT3.doppler(sandfreqTX, P13_FTX),6);

        }

        else {
        u8g2log.print(" NOAA 19   ");
        u8g2log.print(acBuffer);
        
        u8g2log.print("\n");
        u8g2log.print("Lat: ");
        u8g2log.print(yondSatLAT,4);
        u8g2log.print("  Lon: ");
        u8g2log.print(yondSatLON,4);

       u8g2log.print("\n");
       u8g2log.print("Az: ");
       u8g2log.print(yondSatAZ,2);
       u8g2log.print("   El: ");
       u8g2log.println(yondSatEL,2); 
          
         
       u8g2log.print("RX: ");
       u8g2log.print(MySAT4.doppler(yondfreqRX, P13_FRX),6);
       u8g2log.print(", TX: ");
       u8g2log.println(MySAT4.doppler(yondfreqTX, P13_FTX),6);

        }

      u8g2.drawLog(3, 35, u8g2log);     // draw the log content on the display
    
  } while ( u8g2.nextPage() );
  
}
