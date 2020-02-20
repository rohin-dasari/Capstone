import serial
import numpy as np 
import matplotlib.pyplot as plt

# setup pyserial to read from serial monitor
# make sure baud rate below is same as arduino baud rate
# --> this ensures synchronization
BAUD_RATE = 9600
NCOLS = 4
NROWS = 4

ser=serial.Serial('COM3', BAUD_RATE)

# make new figure
fig, ax = plt.subplots()

while 1:
    
    # read, validate, and sanitize input
    raw = str(ser.readline())
    data = []
    processed = raw.split("|")
    processed = processed[0:-1]

    if len(processed) == NCOLS:
        processed[0] = processed[0][2:-1]
        for row in processed:
            temp = row.split(" ")
            if len(temp) > NROWS:
                temp = temp[0:-1]
            temp = [int(num) for num in temp]
            data.extend(temp)

        # store data as 4x4 numpy array, then render heatmap
        if len(data) == NCOLS*NROWS:
            data = np.array(data).reshape((4, 4)).transpose()
            fig.imshow(data, vmin=0, vmax=np.amax(data))
            plt.pause(0.0005)

            

plt.show() 