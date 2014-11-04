import RPi.GPIO as GPIO
import time
from collections import Counter

def scan(sample):
	lim=255	#maximum limit of distance measurement (any value over this which be initialized to the limit value)
	buf=[0]*40
	GPIO.setmode(GPIO.BCM)
	TRIG=3
	ECHO=8
	GPIO.setup(TRIG,GPIO.OUT)
	GPIO.setup(ECHO,GPIO.IN)

	GPIO.output(TRIG,False)
	
	time.sleep(0.005)
	for i in range(sample):
		GPIO.output(TRIG, True)
		time.sleep(0.02)
		GPIO.output(TRIG,False)

		while GPIO.input(ECHO)==0:
			pass
		pulse_start = time.time()

		while GPIO.input(ECHO)==1:
			pass
		pulse_end = time.time()

		pulse_duration = pulse_end - pulse_start

		distance = pulse_duration * 17150

		distance = round(distance, 5)
		
		time.sleep(0.1)
		
		print "Distance:",distance,"cm"

		dist = distance		
		if dist<lim and dist>=0:
			buf[i]=dist
		else:
			return lim
	
		print buf[i]
	#Find the sample that is most common among all the samples for a particular angle
	max=Counter(buf).most_common()	
	rm=-1
	for i in range (len(max)):
		if max[i][0] <> lim and max[i][0] <> 0:
			rm=max[i][0]
			print rm
			break
	return rm

