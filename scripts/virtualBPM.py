#!/usr/bin/env python3
import numpy as np
import time

import rospy
from std_msgs.msg import Float32 #import Float32 msg from std_msg package

class VirtualSensorBPM():
    def __init__(self):
        rospy.init_node('virtual_bpm_node', anonymous=True)
        self.bpm = Float32() #bpm will be our message to be published
        self.bpm.data = 65 #medium beginning rate for init
        self.data_pub = rospy.Publisher("virtual_bpm",Float32, queue_size=10) #publisher object params:(topic_name,type,queue size)
        self.rate = rospy.Rate(50)#50Hz of publish frequency
    
    def run(self):
        while not rospy.is_shutdown():
            self.get_data()
            self.data_pub.publish(self.bpm)
            self.rate.sleep()



    def get_data(self): #this is for fake data
        rand = np.random.uniform(low=-2,high=2) #random law
        if self.bpm.data <= 45: #limit for coherency
            new = self.bpm.data+1.0
        elif self.bpm.data >= 150:#limit for coherency
            new = self.bpm.data-1.0
        else: #follows the random law otherwise
            new = self.bpm.data+rand
        self.bpm.data = new
        #print(new)

if __name__ == "__main__":
    s = VirtualSensorBPM()
    s.run()
    rospy.spin()