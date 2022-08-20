#2022.08.19
#1168 요세푸스 문제 2
#bruteforce

#import sys
#sys.stdin.readline()
n, k = map(int, input().split())

print("<", end = "")

data = [1 for i in range(n)]
ind = 0
for i in range(n-1):
    ind += k - 1
    while ind >= n - i: #len(data)
        ind = ind - (n - i)
    
    print(data.pop(ind), end = ", ")
    
    
print(data.pop(), end = ">\n")
