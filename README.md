# game-control
This lab is to design a game controller for a “Snake” game. 
The game is initially controlled with four keys on the keyboard: “w”, “a”, “s”, “d”. Our task is to alter the control of the game with the following:
(1) use a joystick to control the movement of the snake
(2) use the gyro sensor (MPU-6050) to control the movement of the snake. For example,
tilting the sensor board to the left will cause the “snake” to move to the left.
(3) beep the buzzer when an apple is eaten.
Note that our design does not have to support both (1) and (2) at the same time, although it is possible to support both simultaneously.
Additional requirements for EECE.5520 students
(4) “Shake” the accelerometer to double the number of points for eating an apple. To do that, you need to measure the acceleration from the sensor (MPU-6050), design a criteria (algorithm) to detect if the sensor is being shaken, if so, notify the game to double the points for the next apple (so now 20 points per apple). After the next apple is eaten, revert the points back to normal (i.e., 10 points per apple).
(5) We  need to change the color of the apple to “golden” to indicate the points are doubled for the new apple. Then change the color back to red after the golden apple is eaten.
