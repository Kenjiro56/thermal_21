#!/usr/bin/env python3
import rospy
from std_msgs.msg import Int16MultiArray
#plotするためのモジュール
import matplotlib.pyplot as plt
import numpy as np

height = 15
width = 20

def callback(message):
    print(message.data)
 # bicubicのデータ
		frame = np.array(list(message.data))
		sensordata = frame.reshape(height,width)
    fig = plt.imshow(data, cmap="inferno", interpolation="bicubic")
    plt.colorbar()
		plt.pause(.1)
		plt.clf()
	

if __name__ == "__main__":
    rospy.init_node('vis_therm_sub')
    sub = rospy.Subscriber('Thermal', Int16MultiArray , callback)
    rospy.spin()