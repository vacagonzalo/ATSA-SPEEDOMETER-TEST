from serial import Serial
from time import time
# Colocar el puerto serie por favor
# Si está en windows es un puerto COM, en linux ttyACM
PUERTO_SERIE = '/dev/ttyACM0'

# Distancia entre espiras (metros)
DISTANCE = 2.4


def main():
    state = 0
    delta = 0
    start = 0
    with Serial(PUERTO_SERIE, 115200, timeout=0.02) as s:
        while(True):
            msg = s.readline()
            if len(msg) != 0:
                report = msg[0]

            if(report == 65):  # A
                state = 0
                pass
            elif(report == 66):
                if state == 0:
                    start = time()
                    state = 1
            elif(report == 67):
                if state == 1:
                    delta = time() - start
                    if delta != 0:
                        speed = ((DISTANCE / delta) * (18/5))
                        print(f'Velocidad: {speed}km/h, Tiempo: {delta}')
                    state = 2
            elif(report == 68):
                state = 3
                delta = 0
                start = 0
            else:
                pass


if __name__ == "__main__":
    main()
