//2022.08.19
//1168 요세푸스 문제 2
//C로 구현
//시간 초과 (4%)

#include "stdio.h"

int n, t[4 * 100000] = { 0 };
int min(int x, int y) {
    if (x > y) return y;
    return x;
}
int max(int x, int y) {
    if (x > y) return x;
    return y;
}
void build(int a[], int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = a[tl];
    }
    else {
        int tm = (tl + tr) / 2;
        build(a, v * 2, tl, tm);
        build(a, v * 2 + 1, tm + 1, tr);
        t[v] = t[v * 2] + t[v * 2 + 1];
    }
}
int sum(int v, int tl, int tr, int l, int r) {
    if (l > r)
        return 0;
    if (l == tl && r == tr) {
        return t[v];
    }
    int tm = (tl + tr) / 2;
    return sum(v * 2, tl, tm, l, min(r, tm))
        + sum(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
}
void update(int v, int tl, int tr, int pos) {
    if (tl == tr) {
        t[v] = 0;
    }
    else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update(v * 2, tl, tm, pos);
        else
            update(v * 2 + 1, tm + 1, tr, pos);
        t[v]--;
    }
}
int main() {
    int n = 0, k = 0;
    scanf_s("%d %d", &n, &k);
    int a[100000];
    for (int i = 1; i <= n; i++) a[i] = 1;
    build(a, 1, 1, n);
    printf("<");

    int pivot = 1;
    for (int i = 0; i < n; i++) {
        int x = sum(1, 1, n, pivot, n);
        int temp = 0;
        if (x > k) {
            temp = (pivot + n) / 2;
            int prev = pivot;
            int next = n;

            x = sum(1, 1, n, pivot, temp);
            while (x != k) {
                if (x > k) {
                    int t = temp;
                    temp = (prev + temp) / 2;
                    next = t;
                    x = sum(1, 1, n, pivot, temp);
                }
                else {
                    int t = temp;
                    temp = (next + temp) / 2;
                    prev = t;
                    x = sum(1, 1, n, pivot, temp);
                }
            }
        }
        else if (x == k) { temp = n; }
        else {
            int surp = k - x;
            x = sum(1, 1, n, 1, n);
            surp %= x;
            if (surp == 0) { temp = n; }
            else {
                int prev = 1;
                int next = n;
                temp = (pivot + n) / 2;
                x = sum(1, 1, n, 1, temp);
                while (x != surp) {
                    if (x > surp) {
                        int t = temp;
                        temp = (prev + temp) / 2;
                        next = t;
                        x = sum(1, 1, n, 1, temp);
                    }
                    else {
                        int t = temp;
                        temp = (next + temp) / 2;
                        prev = t;
                        x = sum(1, 1, n, 1, temp);
                    }
                }
            }
        }
        while (a[temp] != 1) temp--;

        a[temp] = 0;
        update(1, 1, n, temp);
        if (i != n - 1) printf("%d, ", temp);
        else printf("%d>\n", temp);
        pivot = temp;
    }
}
