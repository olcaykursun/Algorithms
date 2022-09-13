"""
Closest Pair (Divide&Conquer vs Brute Force)
Created on Sun Mar 27 16:07:13 2022
@author: Olcay Kursun, Dept. of Computer Science, Auburn University at Montgomery
"""

import numpy as np
import time

def distSquare(p1, p2) :   #no need for square root all the time
    global BasicOperationCnt
    BasicOperationCnt += 1
    diff = p1-p2
    return np.dot(diff, diff)
    
def bruteForceClosestDistance(arr) :
    n = arr.shape[0]
    result = np.inf
    for i in range(0, n-1) :
        for j in range(i+1, n) :
            dis = distSquare(arr[i], arr[j])
            if dis < result :
                result = dis
    return np.sqrt(result)     #compute sqrt only once

def findClosestDistance(pointsX, pointsY) :
    global BasicOperationCnt
    N = pointsX.shape[0]
    if (N<=3) :
        return bruteForceClosestDistance(pointsX)
    
    #DIVIDE RECURSIVELY
    median = pointsX[N//2][0]
    
    M = N//2
    dL = findClosestDistance(pointsX[:M], pointsY[pointsY[:,0]<median])
    dR = findClosestDistance(pointsX[M:], pointsY[pointsY[:,0]>=median])
    #Repeated values of the median results in uneven split of pointsY.
    #If we have the median value on both sides, then the min(dL, dR) may not produce the optimal d which may lead to worse performance
    #Uncomment line 55 to see how maxLenY is affected

    #MERGE / CONQUER in linear time so that it will be n*logn
    d = min(dL, dR)
    Y = pointsY[np.logical_and(pointsY[:,0]>(median-d), pointsY[:,0]<=(median+d))]
    for i in range(0, len(Y)-1) :        
        for j in range(i+1, i+7) :  #anything less than 7 is not guaranteed to work (4+4-1 = 7)
            dis = np.sqrt(distSquare(Y[i], Y[min(j,len(Y)-1)]))  
            BasicOperationCnt += 1
            if dis < d :
                d = dis  #tighten d 
    return d


#MAIN
maxBasicOperationCnt = 0
for trial in range(10) :   #check if the results match this many times
    N = 100              #note that brute-force is too slow for large N
    D = 2                 #more complex code/algorithm/prrof when D>2 but can still be made to work
    myPoints = np.random.rand(N, D)    #create random points

    #myPoints[:,0] = 0.5
    
    BasicOperationCnt = 0
    start = time.time()
    myPointsSortedX = myPoints[myPoints[:,0].argsort()]   #presort X
    myPointsSortedY = myPoints[myPoints[:,1].argsort()]   #presort Y
    dist1 = findClosestDistance(myPointsSortedX, myPointsSortedY)
    end = time.time()
    
    if maxBasicOperationCnt < BasicOperationCnt :
        maxBasicOperationCnt = BasicOperationCnt

    print("the closest distance is", dist1)
    print('time taken by the divide and conquer approach is', end - start)
    
    start = time.time()
    dist2 = bruteForceClosestDistance(myPointsSortedX)
    end = time.time()
    print("the closest distance is", dist2)
    print('time taken by the brute force approach is', end - start)
    
    assert(dist1 == dist2)

print("Max number of Basic Operation applications for the divide and conquer method is ", maxBasicOperationCnt)
print("Number of times Basic Operation is applied for the brute force method is ", N*(N-1)//2)

