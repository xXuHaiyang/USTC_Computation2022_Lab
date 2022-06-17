import matplotlib.pyplot as plt
import numpy as np
import os

dir = "C:\\Users\\x\\Desktop\\twodown\\computation\\lab1\\data\\"
for i,j,file in os.walk(dir):
    files = (file)


for i in range(len(files)):
    xs = []
    ys = []
    target = files[i]
    f = open(dir+target,"r")
    content = f.readlines()
    l = len(content)
    for j in range(l):
        x,y = content[j].strip("\n").split(" ")
        xs.append(x)
        ys.append(y)
    #print(xs,ys)
    #plt.plot(xs,ys)
    plt.scatter(xs, ys)
    plt.show()
