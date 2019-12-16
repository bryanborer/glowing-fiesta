import time
import network 
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
  #do_connect()
  while True:
    four(1)
    two(2)
    zero(3)
    nine(4)
    
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
  time.sleep(DELAY)
  
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
  time.sleep(DELAY)

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
  time.sleep(DELAY)

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
  time.sleep(DELAY)
  
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
  time.sleep(DELAY)
  
  
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
  time.sleep(DELAY)
  
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
  time.sleep(DELAY)
  
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
  time.sleep(DELAY)
  
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
  time.sleep(DELAY)
  
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
  time.sleep(DELAY)
  
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
  


