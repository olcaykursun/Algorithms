"""
My heap vs Heapq
Created on Tue Oct 18 16:09:55 2022
@author: Olcay Kursun, Dept. of Computer Science, Auburn University at Montgomery
"""

from operator import gt
class heap:
    
    def __init__(self, x = None, func = gt):
        if x is None:
            self.x = [None]
        else:
            self.x = [None] + x
            
        self.comparator = func
        self.n = len(self.x) - 1        
        self.heapify()
        
    def sink(self, i):
        k = i
        v = self.x[i]
        heap = False
        while (not heap) and 2*k <= self.n :
            j = 2*k
            if j<self.n and self.comparator(self.x[j+1],self.x[j]):
                j += 1
            if self.comparator(v, self.x[j]) :
                heap = True
            else :
                self.x[k] = self.x[j]
                k = j
        self.x[k] = v

    def heapify(self):
        for i in range(self.n//2,0,-1):
            self.sink(i)
            
    def print_sorted(self):
        for i in range(self.n, 0, -1):  #n-1 times
            ith_max = self.x[1]
            self.x[1] = self.x[i]
            self.x[i] = ith_max
            self.n -= 1
            self.sink(1)   #better call "sink" here but lets do this the lazy way
        print(*self.x[1:])
                        

def main():         
    from operator import lt as oper_lt
    numbers = [40, 50, 12, 11, 7, 3, 600, 9]
    heap(numbers).print_sorted()
    heap(numbers, oper_lt).print_sorted()
    
    class Employee:
        def __init__(self, name, salary):
            self.name = name
            self.salary =salary
            
        def __gt__(self, other):
            return self.name > other.name
        
        def gt_salary(self, other):
            return self.salary > other.salary
        
        def __repr__(self):
            return f'[{self.name}]'
    

    names =    ['a', 'd', 'b', 'f', 'c', 'e', 'g', 'h']
    salaries = [40,  50,  12,  11,   7,   3,  60,   9]
    emps = [Employee(name, salary) for name, salary in zip(names, salaries)]
    
    heap(emps).print_sorted()    #uses __gt__ and thus sorts alphabetically
    heap(emps, lambda x,y: x < y).print_sorted()    #cannot find __lt__ and thus uses the complement of __gt__
    heap(emps, Employee.gt_salary).print_sorted()   #prints in increasing order of salary

    print("Now repeat the same heaps using the standard library's 'heapq' module")
#Note that reverse alphabetical order is not easy (see line 94, that ord needs some work for strings)
#Once you get the list you can print in reverse order of course but I just want a heap with "b" having higher priority than "a"
    import heapq as hq
    nums_heap1 = numbers.copy()
    hq.heapify(nums_heap1)
    print(*[hq.heappop(nums_heap1) for i in range(len(nums_heap1))])
    
    nums_heap2 = [(-num, num) for num in numbers]
    hq.heapify(nums_heap2)
    print(*[hq.heappop(nums_heap2)[1] for i in range(len(nums_heap2))])

    emps_heap1 = emps.copy()
    hq.heapify(emps_heap1)
    print(*[hq.heappop(emps_heap1) for i in range(len(emps_heap1))])
    
    emps_heap2 = [(-ord(emp.name), emp) for emp in emps]
    hq.heapify(emps_heap2)
    print(*[hq.heappop(emps_heap2)[1] for i in range(len(emps_heap2))])
    
    emps_heap3 = [(emp.salary, emp) for emp in emps]
    hq.heapify(emps_heap3)
    print(*[hq.heappop(emps_heap3)[1] for i in range(len(emps_heap3))])

if __name__ == '__main__': 
    main() 
