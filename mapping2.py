#!/usr/bin/python


import sys
from collections import Counter
import math
from Tkinter import *
import RPi.GPIO as GPIO
import time
from RPIO import PWM
import distance






master = Tk()
delay=.4
debug =0                        #True to print all raw values
num_of_readings=7        #Number of readings to take 
turnAng = 0
incr=180/num_of_readings        #increment of angle in servo
nonreads = 0
ang_l=[0]*(num_of_readings+1)        #list to hold the angle's of readings
dist_l=[0]*(num_of_readings+1)        #list to hold the distance at each angle
dist_non=[0]*(num_of_readings+1) #list to hold all readings that did not find a wall
x=[0]*(num_of_readings+1)        #list to hold the x coordinate of each point
y=[0]*(num_of_readings+1)        #list to hold the y coordinate of each point
x2=[0]*(num_of_readings+1)*10
y2=[0]*(num_of_readings+1)*10


posx=0                                #current x coordinate of car
posy=0                                #current y coordinate of car
ang_car        =0                        #current angle of car
servo = PWM.Servo()
servo.set_servo(18, 2550)        # reset servo to 0 degrees
                


ang=0
index=0
sample=1       #Number of samples for each angle (more the samples, better the data but more the time taken)


print "Getting the data"


while True:
        #Take the readings from the Ultrasonic sensor and process them to get the correct values
        Distance = distance.scan(sample)
        if Distance == 255:
                dist_non[index] = 1
        else:
                dist_non[index] = 0


        ang_l[index]=ang
        dist_l[index]=Distance
        index+=1
        
        #Move the servo to the next angle
        
        nextAng = 3000 - ((2100/num_of_readings*turnAng) + 450)
        servo.set_servo(18, nextAng)
        turnAng+=1
        print "turn"
        
        
        time.sleep(delay)
        ang+=incr
        #print ang
        if turnAng>num_of_readings:
                break


print "mapping"
#Convert the distance and angle to (x,y) coordinates and scale it down
for i in range(num_of_readings+1):        
        x[i]=((dist_l[i]*math.cos(math.pi*(ang_l[i])/180))/10)
        y[i]=(dist_l[i]*math.sin(math.pi*ang_l[i]/180))/10


#Print the values in a grid of 50x50 on the terminal
grid_size=50
#not done yet, unsure how big the final map needs to be.
#Rotate the readings so that it is printed in the correct manner
for i in range(num_of_readings+1):        
        x[i]=(grid_size/2)-x[i]
        y[i]=(grid_size/2)-y[i]
        x2[i]=10*x[i]
        y2[i]=10*y[i]


w = Canvas(master, width=500, height=500)
w.pack()
posx=((grid_size/2)-posx)*10
posy=((grid_size/2)-posy)*10
for i in range(num_of_readings):
        if (dist_non[i] == 1 and dist_non[i+1] == 1):
        	w.create_polygon(posx, posy, x2[i], y2[i], x2[i+1], y2[i+1], fill="white")
	
        else:
                w.create_line(x2[i], y2[i], x2[i+1], y2[i+1], fill="black", width="5")
                w.create_polygon(posx, posy, x2[i], y2[i], x2[i+1], y2[i+1], fill="white")


for i in range(num_of_readings+1):
        print dist_l[i]
mainloop()