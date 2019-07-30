#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    // TODO: Request a sertvice and pass the velocities to it to drive the robot
	ball_chaser::DriveToTarget srv;
	srv.request.linear_x = lin_x;
	srv.request.angular_z = ang_z;

	if(!client.call(srv)){
		ROS_ERROR("No srv called");
	}
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{

    int white_pixel = 255;
	
	// TODO: Loop through each pixel in the image and check if there's a bright white one
    // Step 1: Looking for white pixel by presence and position using ' width = step= x' ' heigh= y'
    
    for(int x=0; x<img.step; x++){ // X coord
    	for(int y=0; y<img.step; y++){ // Y coord
    		int loc = x+y*img.step; // dimensional location, 
		    // Then, identify if this pixel falls in the left, center, or right side of the image
    		if(img.data[loc] == white_pixel)
    		{
   			    // Depending on the white ball position, call the drive_bot function and pass velocities to it
    			float dir = (float)x / img.width; // Locating the direction by ocuppancy
    			if (dir < .3) // left 
    			{ 
    				drive_robot(0., .2);
    			}
    			else if (.7 < dir)  // right
    			{
    				drive_robot(0., -.2);

    			}
    			else 
    			{
    				drive_robot(0.2,0.); // center
    			}
    			return;
    		}
    	}
    }
    // Request a stop when there's no white ball seen by the camera
    drive_robot(0., 0.);
    return;
}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}
