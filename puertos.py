from serial.tools import list_ports


def main():
    if 0 == len(list_ports.comports()):
        print("No se detectaron puertos activos")
    for port in list_ports.comports():
        print("Puerto:", port.name)


if __name__ == "__main__":
    main()
