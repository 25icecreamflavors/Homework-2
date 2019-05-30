import matplotlib.pyplot as plt
import csv
import webbrowser
import pylab 

x=[]
x1=[]
x2=[]
y=[]
x1=[]
y1=[]
y2=[]
y3=[]
y4=[]
y5=[]
r1=[]
r2=[]
c1=[]
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
with open('radix1.csv', 'r') as csvfile:
    plots= csv.reader(csvfile, delimiter=',')
    for row in plots:
        x1.append(float(row[0]))
        r1.append(float(row[1]))
        r2.append(float(row[2]))
with open('counting100.csv', 'r') as csvfile:
    plots= csv.reader(csvfile, delimiter=',')
    for row in plots:
        x2.append(float(row[0]))
        c1.append(float(row[1]))
        
plt.plot(x,y, marker='', color='indigo', label='InsertionSort')
plt.plot(x,y1, marker='', color='grey', label='InsertionSortList')
plt.plot(x,y2, marker='', color='blue', label='MergeSort')
plt.plot(x,y3, marker='', color='red', label='MergeSortList')
plt.plot(x,y4, marker='', color='purple', label='QuickSort')
plt.plot(x,y5, marker='', color='orange', label='QuickSortList')

plt.plot(x1,r1, marker='', color='maroon', label='RadixSort10')
plt.plot(x1,r2, marker='', color='pink', label='RadixSort2')
plt.plot(x2,c1, marker='', color='cyan', label='CoutingSort100k')

pylab.legend(loc='upper left')
plt.title('Algorithm Performance')
plt.xlabel('Number of elements in the vector')
plt.ylabel('Time in milliseconds')
plt.show()
