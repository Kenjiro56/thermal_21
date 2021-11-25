# Name
 
## thermal_21
 
#### RCAP2021で使用するサーマルセンサ**mlx90640**をArudinoでrosserial通信をしてPublish、Subscribeしてヒートマップを作成するプログラム。
 
# DESCRIPTION
 
デフォルトの32×24のデータ量を渡そうとするとデータの制限の問題に突き当たるので本リポジトリのプログラムでは、HEIGHTとWIDTHで切り出してデータ量を削減しました。HEIGHTとWIDTHで指定した範囲でヒートマップを作成できます。
  
# Requirement
 
- compressArr_lib
- Adafruit MLX90640
 
# Installation
 
compressArr_libはzip形式でインストールしてライブラリを手動で追加する。
Adafruit MLX90640に関しては、下記サイトを参考にした。

https://learn.adafruit.com/adafruit-mlx90640-ir-thermal-camera/arduino
 
# Usage
 
comprArr_lib_float32も作成したが、バッファサイズを超えてしまうため、使用できない。
 
# Note
 
https://github.com/ros-drivers/rosserial/issues/299

上記のエラーが出るため、Publishのコードは改善の余地あり。
 
