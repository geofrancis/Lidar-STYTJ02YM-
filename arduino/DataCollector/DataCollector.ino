

//Max lidar resolution is 752, to make it easier to send and display in pygame program reduces it to 188 (752/4 = 188)
#define LIDAR_RESOLUTION 240
#define FRAME_LENGTH 120


//### LIDAR
int lidar_frame[FRAME_LENGTH];
int distances[LIDAR_RESOLUTION];
int signals[LIDAR_RESOLUTION];

void setup() {
  

  //Serial monitor
  Serial.begin(230400);
  Serial1.begin(230400);

  
  //setting all distance in the array to 0
  for (int a = 0; a < LIDAR_RESOLUTION; a++) {
    distances[a] = 0;
    signals[a] = 50;
  }
}



long last_send = 0;


void loop() {
    if (Serial1.read() == 170) {
      GetLidarData();
      if(lidar_frame[2] == 1 && lidar_frame[3] == 97){
      int circleSegment = ((lidar_frame[10]*256+lidar_frame[11])/2250);
      int points = (lidar_frame[6] - 5) / 3;
      if(points > 30 && circleSegment < 16){
        for(int p = 0; p < 15; p++){
            int d = (lidar_frame[13 + p*6]*256 + lidar_frame[14 + p*6]) * 0.25;
            int signal = (lidar_frame[12+p*6]);
            if(d < 8000 && signal >= 100){           
              signals[circleSegment*15+p] = signal;
              distances[circleSegment*15+p] = d;
            }
          }
        }
      }
    }
}




void GetLidarData() {
  for (int a = 0; a < FRAME_LENGTH; a++) {
    while (!Serial1.available());
    lidar_frame[a] = Serial1.read();
  }
}
