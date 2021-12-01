from serial import Serial
from datetime import datetime


def main():
    DISTANCE = 2.4
    coilA = datetime.now()
    coilB = datetime.now()
    with Serial('/dev/ttyUSB1', 9600, timeout=0.02) as s:
        while(True):
            msg = s.readline()
            if(msg == b'A'):
                pass
            elif(msg == b'B'):
                coilA = datetime.now()
            elif(msg == b'C'):
                coilB = datetime.now()
                speed = DISTANCE / (coilB - coilA)
                print(f'@{coilB}: {speed}km/h')
            elif(msg == b'D'):
                pass
            else:
                print("msg:", msg.decode('utf-8'))


if __name__ == "__main__":
    main()
