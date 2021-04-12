# Templates
## Factorials and Combinatorics
```cpp
#include "bits/stdc++.h"
using namespace std;
 
const int N = 2e5 + 7;
typedef long long LL;
 
const int M = 1e9 + 7;
LL fac[N], invfac[N];
 
LL bm(LL a, LL p) {
    if (p == 0) return 1;
    if (p == 1) return a;
    if (p & 1) return (a * bm(a, p - 1)) % M;
    LL f = bm(a, p / 2);
    return (f * f) % M;
}
 
void pre() {
    fac[0] = 1;
    for (int i = 1; i < N; i++) fac[i] = (fac[i - 1] * i) % M;
    invfac[N - 1] = bm(fac[N - 1], M - 2);
    for (int i = N - 2; i >= 0; i--) invfac[i] = (invfac[i + 1] * (i + 1)) % M;
}
 
LL ncr(LL n, LL r) {
    if (n == r) return 1;
    if (r > n) return 0;
    LL ans = fac[n];
    ans = (ans * invfac[r]) % M;
    ans = (ans * invfac[n - r]) % M;
    return ans;
}
```

## Matrix Exponentiation

```cpp
#include "bits/stdc++.h"
using namespace std;
 
const int M = 1e9 + 7;
 
struct Mat {
    long long a[2][2] = {{0, 0}, {0, 0}};
    Mat operator*(const Mat& other) {
        Mat res;
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                for (int k = 0; k < 2; k++) {
                    res.a[i][k] = (res.a[i][k] + (a[i][j] * other.a[j][k]))%M;
                }
        return res;
    }
};
 
Mat bm(Mat a, long long p) {
    if (p == 1) return a;
    if (p & 1) return a * (bm(a, p - 1));
    Mat tepm = bm(a, p / 2);
    return (tepm * tepm);
}
```
