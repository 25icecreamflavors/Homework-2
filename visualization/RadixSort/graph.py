import matplotlib.pyplot as plt
import csv
import webbrowser
import pylab 

x=[]
y=[]
x1=[]
y1=[]
y2=[]
y3=[]
y4=[]
y5=[]

with open('data.csv', 'r') as csvfile:
    plots= csv.reader(csvfile, delimiter=',')
    for row in plots:
        x.append(float(row[0]))
        y.append(float(row[1]))
        y1.append(float(row[2]))
plt.plot(x,y, marker='', color='maroon', label='RadixSort10')
plt.plot(x,y1, marker='', color='grey', label='RadixSort2')
pylab.legend(loc='upper left')
plt.title('Algorithm Performance/Strings')
plt.xlabel('Number of elements in the vector')
plt.ylabel('Time in milliseconds')
plt.show()
