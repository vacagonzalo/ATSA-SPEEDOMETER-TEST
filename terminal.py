from serial import Serial
from datetime import datetime

# Colocar el puerto serie por favor
PUERTO_SERIE = '/dev/ttyUSB1'

# Distancia entre espiras (metros)
DISTANCE = 2.4


def main():
    f = datetime.now().timestamp
    coilA = f()
    coilB = f()
    with Serial(PUERTO_SERIE, 9600, timeout=0.02) as s:
        while(True):
            msg = s.readline()
            if(msg == b'A'):
                pass
            elif(msg == b'B'):
                coilA = f()
            elif(msg == b'C'):
                coilB = f()
                speed = DISTANCE / (coilB - coilA)
                print(f'@{datetime.now()}: {speed}km/h')
            elif(msg == b'D'):
                pass
            else:
                print("msg:", msg.decode('utf-8'))


if __name__ == "__main__":
    main()
