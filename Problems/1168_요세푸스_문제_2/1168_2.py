#2022.08.18
#1168 요세푸스 문제 2
#Segment Tree 구현 및 적용
#시간초과 (4%)

def build(pos, left, right):
    if left == right:
        data[pos] = item[left]
        return
    mid = (left + right) // 2
    build(pos*2, left, mid)
    build(pos*2+1, mid+1, right)
    data[pos] = data[pos*2] + data[pos*2+1]

def add(pos, tl, tr, left, right):
    if left > right:
        return 0
    if left == tl and right == tr:
        return data[pos]
    tm = (tl + tr) // 2
    return add(pos*2, tl, tm, left, min(right, tm)) + add(pos*2+1, tm+1, tr, max(left, tm+1), right)

def update(pos, tl, tr, p):
    if tl == tr:
        data[pos] = 0
    else:
        tm = (tl + tr) // 2
        if p <= tm:
            update(pos*2, tl, tm, p)
        else:
            update(pos*2+1, tm+1, tr, p)
        data[pos] = data[pos] - 1
    
    
n, k = map(int, input().split())

item = [1 for _ in range(n+1)]
data = [0 for _ in range(4*n+1)]

build(1, 1, n)

pivot = 1
print("<", end = "")
for it in range(n):
    x = add(1, 1, n, pivot, n)
    if x > k:
        temp = (pivot+n)//2
        prev = pivot
        nex = n

        x = add(1, 1, n, pivot, temp)
        while x != k:
            if x > k:
                temp, nex = (prev+temp)//2, temp
                x = add(1, 1, n, pivot, temp)
            else:
                temp, prev = (nex+temp)//2, temp
                x = add(1, 1, n, pivot, temp)
    elif x == k:
        temp = n
    else:
        surp = k - x
        x = add(1, 1, n, 1, n)
        surp %= x
        if surp == 0:
            temp = n
        else:
            prev = 1
            nex = n
            temp = (pivot+n)//2
            x = add(1, 1, n, 1, temp)
            while x != surp:
                if x > surp:
                    temp, nex = (prev+temp)//2, temp
                    x = add(1, 1, n, 1, temp)
                else:
                    temp, prev = (nex+temp)//2, temp
                    x = add(1, 1, n, 1, temp)
    while item[temp] != 1:
        temp -= 1

    item[temp] = 0
    update(1, 1, n, temp)
    if it != n-1:
        print(temp, end = ", ")
    else:
        print(temp, end = ">\n")
    pivot = temp
