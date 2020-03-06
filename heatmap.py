import serial
import numpy as np 
import matplotlib.pyplot as plt

# setup pyserial to read from serial monitor
# make sure baud rate below is same as arduino baud rate
# --> this ensures synchronization
BAUD_RATE = 9600
NCOLS = 4
NROWS = 10


def parseData(data):
    res = [] # store resulting data array
    for chunk in data:
        for num in chunk:
            if num != ' ':
                res.append(int(num))
    return res


ser=serial.Serial('COM6', BAUD_RATE)

# make new figure
fig, ax = plt.subplots()
viz = plt.imshow(np.zeros((NROWS, NCOLS)))

# The string that is read from the serial port
# must be validated and santized before it can
# be passed to the heatmap.
# The expected output from the serial monitor can be
# found in the .ino file in this directory.
# The output should look like this:
# r1c1 r2c1 r3c1 r4c1|r1c2 r2c3...
# Where r1c1 corresponds to row1 col1 on the grid
disp = 1
while disp:

    if plt.get_fignums() == []:
        disp = 0

    # read, validate, and sanitize input
    raw = ser.readline().decode("utf-8")
    processed = raw.split("|")
    processed = processed[0:-1]
    if len(processed) == NROWS:
        arr = parseData(processed)
        print(len(arr)==NROWS*NCOLS)
        
        if len(arr) == NROWS*NCOLS:
            print("hi")
            data = np.array(arr).reshape((NCOLS, NROWS)).transpose()
            viz.set_data(data)
            viz.set_clim(0, np.amax(data))
            plt.pause(0.0005)
            

plt.draw() 
