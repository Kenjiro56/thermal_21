//読み取ったセンサの行列を圧縮するためのライブラリ
#include <compressArr.h>
//センサを使うためのライブラリ
#include <Adafruit_MLX90640.h>
//ros関連のライブラリ
#include <ros.h>
#include <std_msgs/Int16MultiArray.h>
//センサーで読み取った値を圧縮した後の行列の大きさ
#define HEIGHT 15
#define WIDTH 20

/*
 * ROS関連の設定
 */
//ROSメッセージのインスタンス
ros::NodeHandle  nh;

//ROSメッセージの型
std_msgs::Int16MultiArray thermal_msg;
//Publisherのインスタンスvis_thermal
//トピック名：Thermal
//ROSメッセージのインスタンス:thermal_msg
ros::Publisher vis_thermal("Thermal", &thermal_msg);


//センサの設定
Adafruit_MLX90640 mlx;
//センサで読み取った値を入れる配列
float frame[32*24]; // buffer for full frame of temperatures
//送信するときに圧縮したやつを入れる配列
int16_t int_frame[WIDTH*HEIGHT];



void setup() {
  //thermal_msgのための諸々の設定
  thermal_msg.data = (int16_t*)malloc(sizeof(int16_t) * HEIGHT*WIDTH);
  thermal_msg.data_length = HEIGHT*WIDTH;


  //センサの設定(スケッチ例そのまま)
  while (!Serial) delay(10);
  Serial.begin(115200);
  delay(100);

  Serial.println("Adafruit MLX90640 Simple Test");
  if (! mlx.begin(MLX90640_I2CADDR_DEFAULT, &Wire)) {
    Serial.println("MLX90640 not found!");
    while (1) delay(10);
  }
  Serial.println("Found Adafruit MLX90640");

  Serial.print("Serial number: ");
  Serial.print(mlx.serialNumber[0], HEX);
  Serial.print(mlx.serialNumber[1], HEX);
  Serial.println(mlx.serialNumber[2], HEX);
  
  //mlx.setMode(MLX90640_INTERLEAVED);
  mlx.setMode(MLX90640_CHESS);
  Serial.print("Current mode: ");
  if (mlx.getMode() == MLX90640_CHESS) {
    Serial.println("Chess");
  } else {
    Serial.println("Interleave");    
  }

  mlx.setResolution(MLX90640_ADC_18BIT);
  Serial.print("Current resolution: ");
  mlx90640_resolution_t res = mlx.getResolution();
  switch (res) {
    case MLX90640_ADC_16BIT: Serial.println("16 bit"); break;
    case MLX90640_ADC_17BIT: Serial.println("17 bit"); break;
    case MLX90640_ADC_18BIT: Serial.println("18 bit"); break;
    case MLX90640_ADC_19BIT: Serial.println("19 bit"); break;
  }

  mlx.setRefreshRate(MLX90640_2_HZ);
  Serial.print("Current frame rate: ");
  mlx90640_refreshrate_t rate = mlx.getRefreshRate();
  switch (rate) {
    case MLX90640_0_5_HZ: Serial.println("0.5 Hz"); break;
    case MLX90640_1_HZ: Serial.println("1 Hz"); break; 
    case MLX90640_2_HZ: Serial.println("2 Hz"); break;
    case MLX90640_4_HZ: Serial.println("4 Hz"); break;
    case MLX90640_8_HZ: Serial.println("8 Hz"); break;
    case MLX90640_16_HZ: Serial.println("16 Hz"); break;
    case MLX90640_32_HZ: Serial.println("32 Hz"); break;
    case MLX90640_64_HZ: Serial.println("64 Hz"); break;
  }

  
  //ROSノードのインスタンス「nh」を初期化し、Publisher「vis_therm_pub」をPublishす る
  nh.initNode();
  nh.advertise(vis_thermal);
}

void loop() {
  delay(500);
  if (mlx.getFrame(frame) != 0) {
    Serial.println("Failed");
    return;
  }
  int height = HEIGHT;
  int width = WIDTH;
  int ori_w = 32;
    
  compressArr(frame,ori_w,height,width,int_frame);
  //ROSメッセージをframeに設定
  thermal_msg.data = int_frame;
  for(int i=0;i<height*width;i++){
      Serial.print(int_frame[i]);
      Serial.print(",");
    }
     Serial.println();
  //ROSメッセージをpublishする
  vis_thermal.publish(&thermal_msg);
  nh.spinOnce();
  delay(1000);
}