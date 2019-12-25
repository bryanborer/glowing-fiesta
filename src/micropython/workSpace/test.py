from machine import Pin, PWM
import utime

DELAY = 0.0005

data = Pin(16, Pin.Out)
pwm = PWM(Pin(4), freq=2000, duty=1000)

while True: 
  data.value(0)
  utime.sleep(DELAY)
  data.value(1)
  utime.sleep(DELAY)
