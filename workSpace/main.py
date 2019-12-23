import utime
import ntptime
import math
from machine import Pin

DELAY = 0.0055  # Delay between writing to each digit of HEX

segA = Pin(16, Pin.OUT)  # A
segB = Pin(27, Pin.OUT)  # B
segC = Pin(26, Pin.OUT)  # C
segD = Pin(25, Pin.OUT)  # D
segE = Pin(33, Pin.OUT)  # E
segF = Pin(4, Pin.OUT)   # F
segG = Pin(14, Pin.OUT)  # G
dp = Pin(32, Pin.OUT)    # Decimal Point

dig1 = Pin(19, Pin.OUT)  # Digit 1
dig2 = Pin(18, Pin.OUT)  # Digit 2
dig3 = Pin(5, Pin.OUT)   # Digit 3
dig4 = Pin(17, Pin.OUT)  # Digit 4


def main():
  # Setup section
  do_connect()                            # Connect to internet
  ntptime.settime()                       # Set machine time to internet time
  current_time = utime.time()              # Get time since program start
  
  # Calculate time for the first time so vars aren't null
  hour, minute = calculate_time()
  firstDigH = math.floor(hour/10)
  firstDigM = math.floor(minute/10)
  
  #while True:
  #  one(1)
  #  two(2)
  #  three(3)
  #  four(4)
  
  while True:  # Run forever to continually display correct time
    if utime.time() - current_time > 5:  # Check the current time every 5 seconds as to not hog CPU
      hour, minute = calculate_time()
      firstDigH = math.floor(hour/10)
      firstDigM = math.floor(minute/10)
      
    print_number(firstDigH, 1)
    print_number(hour - firstDigH * 10, 2)
    
    
    print_number(firstDigM, 3)
    print_number(minute - firstDigM * 10, 4)
    
def do_connect():
  import network
  sta_if = network.WLAN(network.STA_IF)  # Instantiate station object
  if not sta_if.isconnected():
    print('connecting to network...')
    sta_if.active(True)  # Activate station interface
    sta_if.connect('ALLOE6CC5', 'magicalbird445')  # Connect to network
    while not sta_if.isconnected():
      pass
  print('network config:', sta_if.ifconfig())
    
def calculate_time():
  year, month, mday, hour, minute, second, weekday, yearday = utime.localtime()  # Returns time in GMT, 6 hours ahead of CST
  delta = hour - 6
  
  if delta <= 0:
    mday = mday - 1  # Rewind a day 
    hour = 24 + delta - 12  # Convert to CST (non-military time)
  else:
    hour = hour - 6  # Adjust time for CST
    if hour > 12:
      hour = hour - 12  # Convert to non-military time
  
  # Only need hour and minute for now
  return hour, minute
  
  
def print_number(number, digit):
  if number == 0:
    zero(digit)
  if number == 1:
    one(digit)
  if number == 2:
    two(digit)
  if number == 3:
    three(digit)
  if number == 4:
    four(digit)
  if number == 5:
    five(digit)
  if number == 6:
    six(digit)
  if number == 7:
    seven(digit)
  if number == 8:
    eight(digit)
  if number == 9:
    nine(digit)

def allLow():
  segA.value(0)
  segB.value(0)
  segC.value(0)
  segD.value(0)
  segE.value(0)
  segF.value(0)
  segG.value(0)
  dp.value(0)
  
def allHigh():
  segA.value(1)
  segB.value(1)
  segC.value(1)
  segD.value(1)
  segE.value(1)
  segF.value(1)
  segG.value(1)
  dp.value(1)
  
def zero(digit):
  allLow()
  selectDigit(digit)
  segA.value(1)
  segB.value(1)
  segC.value(1)
  segD.value(1)
  segE.value(1)
  segF.value(1)
  segG.value(0)
  dp.value(0)
  utime.sleep(DELAY)
  
def one(digit):
  allLow()
  selectDigit(digit)
  segA.value(0)
  segB.value(1)
  segC.value(1)
  segD.value(0)
  segE.value(0)
  segF.value(0)
  segG.value(0)
  dp.value(0)
  utime.sleep(DELAY)

def two(digit):
  allLow()
  selectDigit(digit)
  segA.value(1)
  segB.value(1)
  segC.value(0)
  segD.value(1)
  segE.value(1)
  segF.value(0)
  segG.value(1)
  dp.value(0)
  utime.sleep(DELAY)

def three(digit):
  allLow()
  selectDigit(digit)
  segA.value(1)
  segB.value(1)
  segC.value(1)
  segD.value(1)
  segE.value(0)
  segF.value(0)
  segG.value(1)
  dp.value(0)
  utime.sleep(DELAY)
  
def four(digit):
  allLow()
  selectDigit(digit)
  segA.value(0)
  segB.value(1)
  segC.value(1)
  segD.value(0)
  segE.value(0)
  segF.value(1)
  segG.value(1)
  dp.value(0)
  utime.sleep(DELAY)
  
  
def five(digit):
  allLow()
  selectDigit(digit)
  segA.value(1)
  segB.value(0)
  segC.value(1)
  segD.value(1)
  segE.value(0)
  segF.value(1)
  segG.value(1)
  dp.value(0)
  utime.sleep(DELAY)
  
def six(digit):
  allLow()
  selectDigit(digit)
  segA.value(1)
  segB.value(0)
  segC.value(1)
  segD.value(1)
  segE.value(1)
  segF.value(1)
  segG.value(1)
  dp.value(0)
  utime.sleep(DELAY)
  
def seven(digit):
  allLow()
  selectDigit(digit)
  segA.value(1)
  segB.value(1)
  segC.value(1)
  segD.value(0)
  segE.value(0)
  segF.value(0)
  segG.value(0)
  dp.value(0)
  utime.sleep(DELAY)
  
def eight(digit):
  allLow()
  selectDigit(digit)
  segA.value(1)
  segB.value(1)
  segC.value(1)
  segD.value(1)
  segE.value(1)
  segF.value(1)
  segG.value(1)
  dp.value(0)
  utime.sleep(DELAY)
  
def nine(digit):
  allLow()
  selectDigit(digit)
  segA.value(1)
  segB.value(1)
  segC.value(1)
  segD.value(1)
  segE.value(0)
  segF.value(1)
  segG.value(1)
  dp.value(0)
  utime.sleep(DELAY)
  
def selectDigit(digit):
  if digit == 1:
    dig1.value(1)
    dig2.value(1)
    dig3.value(1)
    dig4.value(1)
    dig1.value(0)
  if digit == 2:
    dig1.value(1)
    dig2.value(1)
    dig3.value(1)
    dig4.value(1)
    dig2.value(0)
  if digit == 3:
    dig1.value(1)
    dig2.value(1)
    dig3.value(1)
    dig4.value(1)
    dig3.value(0)
  if digit == 4:
    dig1.value(1)
    dig2.value(1)
    dig3.value(1)
    dig4.value(1)
    dig4.value(0)

def deselectDigit(digit):
  if digit == 1:
    dig1.value(1)
  if digit == 2:
    dig2.value(1)
  if digit == 3:
    dig3.value(1)
  if digit == 4:
    dig4.value(1)
   
def deselectAll(): 
  deselectDigit(1)
  deselectDigit(2)
  deselectDigit(3)
  deselectDigit(4)
    
  
if __name__ == '__main__':
  main()
  





