from RPIO import PWM
import time

servo = PWM.Servo()
while (1):
	for i in range(45, 255, 28):
		servo.set_servo(18, i*10)
		time.sleep(0.2)
	for i2 in range(255, 45, -28):
		servo.set_servo(18, i2*10)
		time.sleep(0.2)
