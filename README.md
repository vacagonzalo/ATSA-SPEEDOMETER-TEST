# ATSA-SPEEDOMETER-TEST
Probador de cinemómetros para el laboratorio de [ATSA Argentina](https://atsa.net.ar/).

Autor: Gonzalo Vaca <gvaca@atsa.net.ar>

## Requisitos
1. Intérprete **Python 3**
2. Biblioteca [PySerial](https://pypi.org/project/pyserial/)
3. Entorno de desarrollo [Arduino](https://www.arduino.cc/)

## Instrucciones

### Equipo de prueba
1. Satisfacer el requisito 3
2. Clonar o descargar este repositorio
3. Use el entorno de desarrollo [Arduino](https://www.arduino.cc/) para programar el *Probador de cinemómetros*
4. Conecte el equipo al cinemómetro

Nota: En caso de tener un equipo ya programado puede evitar los pasos 1, 2 y 3

### Software de verificación
1. Satisfacer los requisitos 1 y 2
2. Conectar el equipo al puerto USB de su ordenador
3. Identificar el puerto
4. Escribir el puerto en el campo **PUERTO_SERIE** del script **terminal.py**
5. Ejecutar el script con el comando:
```bash
python3 terminal.py
```
## Licencia
MIT License