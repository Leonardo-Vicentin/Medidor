import serial
import time
ser = serial.Serial(port='COM7', baudrate=115200, timeout=10)

nome_do_arquivo = input('Nome do arquivo a ser editado:')

for g in range(4):
  
  arquivo = open(nome_do_arquivo+str(g)+".txt", 'w+')




  a=ser.read_until(b"7000\r")
  for i in range(2002):
    line = ser.readline()   # read a byte

    if line:
      string = line.decode()  # convert the byte string to a unicode string
          #num = int(string) # convert the unicode string to an int
      print(string)
      arquivo.writelines(string)

          
        
  arquivo.close()

ser.close()
