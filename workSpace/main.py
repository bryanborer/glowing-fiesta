import time
import network 
from machine import Pin

DELAY = 0.0055

segA = Pin(16, Pin.OUT)
segB = Pin(27, Pin.OUT)
segC = Pin(26, Pin.OUT)
segD = Pin(25, Pin.OUT)
segE = Pin(33, Pin.OUT)
segF = Pin(4, Pin.OUT)
segG = Pin(14, Pin.OUT)
dp = Pin(32, Pin.OUT)

dig1 = Pin(19, Pin.OUT)
dig2 = Pin(18, Pin.OUT)
dig3 = Pin(5, Pin.OUT)
dig4 = Pin(17, Pin.OUT)

sta_if = network.WLAN(network.STA_IF)
sta_if.active(True)
sta_if.connect('ALLOE6CC5', 'magicalbird445')

def main():
  print(time.time())
  while True:
    four(1)
    two(2)
    zero(3)
    nine(4)

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
  


