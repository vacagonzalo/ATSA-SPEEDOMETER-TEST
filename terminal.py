from serial import Serial


def main():
    with Serial('/dev/ttyUSB1', 9600, timeout=0.02) as s:
        msg = s.readline()
        print(msg, end='\r')


if __name__ == "__main__":
    main()
