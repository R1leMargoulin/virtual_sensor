#include "ros/ros.h"
#include "std_msgs/Float32.h"

#include <bits/stdc++.h>
#include <random>
#include <sstream>



void get_data(std_msgs::Float32* bpm, float rand){ //function for virtual sensor, replace with your data collect
		if(bpm->data <= 45.0){
			bpm->data = bpm->data + 1.0;
		}
		else if(bpm->data >= 150.0){
			bpm->data = bpm->data - 1.0;
		}
    else{
			bpm->data = bpm->data + rand; //update the ros message data
		}
}


int main(int argc, char **argv)
{
  assert(CHAR_BIT * sizeof (float) == 32);
  ros::init(argc, argv, "virtual_bpm_node"); //unique node name here
  ros::NodeHandle n;
  ros::Publisher vsensor_pub = n.advertise<std_msgs::Float32>("virtual_bpm", 1000); //publisher initialize
  ros::Rate loop_rate(50);

  std_msgs::Float32* bpm = new std_msgs::Float32; //init of our ros message
	bpm->data = 65.0; //initial value

	// random generator
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dist(-2.0, 2.0);

  while (ros::ok())
  {
		float rand = dist(gen); //generate a new random number
		get_data(bpm, rand);  //update the virtual data with the random number
    vsensor_pub.publish(*bpm); //publish in the topic.

    ros::spinOnce();
    loop_rate.sleep(); //sleep in order to get a  50 Hz rate
  }
  delete bpm; //free memory by deleting the pointer


  return 0;
}