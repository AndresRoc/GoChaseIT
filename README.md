# GoChaseIT
Go chase it udacity second project

Udacity project number 2 "Go chase it". Creating a mobile robot capable of following a movable white ball, using image processing.
Visualization available on Rviz and Gaze

## Running the tests

### Simulating

To launch the world project

```
roslaunch my_robot world.launch 
```

### Chasing the ball

A step by step series of examples that tell you how to get a development env running

launching the chaser 

```
roslaunch ball_chaser ball_chaser.launch
```

Run the drive robot node

```
rosrun ball_chaser drive_bot
```

Visualazing the ball

```
rosrun ball_chaser process_image 
```



