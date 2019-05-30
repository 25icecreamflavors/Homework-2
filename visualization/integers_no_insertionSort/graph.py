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

with open('TimeData.csv', 'r') as csvfile:
    plots= csv.reader(csvfile, delimiter=',')
    for row in plots:
        x.append(float(row[0]))
        y.append(float(row[1]))
        y1.append(float(row[2]))
        y2.append(float(row[3]))
        y3.append(float(row[4]))
        y4.append(float(row[5]))
        y5.append(float(row[6]))
plt.plot(x,y, marker='', color='green', label='InsertionSort')
plt.plot(x,y2, marker='', color='grey', label='MergeSort')
plt.plot(x,y3, marker='', color='cyan', label='MergeSortList')
plt.plot(x,y4, marker='', color='orange', label='QuickSort')
plt.plot(x,y5, marker='', color='indigo', label='QuickSortList')
pylab.legend(loc='upper left')
plt.title('Algorithm Performance')
plt.xlabel('Number of elements in the vector')
plt.ylabel('Time in milliseconds')
plt.show()
