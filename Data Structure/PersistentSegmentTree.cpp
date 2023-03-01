/**
 *Persistence Segment Tree
 * Query -> O(logn)
 * Memory -> O(nlogn)
 **/
#include <bits/stdc++.h>
using namespace std;

using LL = long long ;
const int N = 4e6 + 7;

struct Node {
    int l = 0, r = 0, val = 0;
} tr[20 * N];

int ptr = 0;
int build(int st, int en) {
    int u = ++ptr;
    if (st == en) return u;

    int mid = (st + en) / 2;
    auto& [l, r, val] = tr[u];

    l = build(st, mid);
    r = build(mid + 1, en);
    val = tr[l].val + tr[r].val;
    return u;
}

int update(int pre, int st, int en, int idx, int v) {
    int u = ++ptr;
    tr[u] = tr[pre];

    if (st == en) {
        tr[u].val += v;
        return u;
    }

    int mid = (st + en) / 2;
    auto& [l, r, val] = tr[u];

    if (idx <= mid) {
        r = tr[pre].r;
        l = update(tr[pre].l, st, mid, idx, v);
    } else {
        l = tr[pre].l;
        r = update(tr[pre].r, mid + 1, en, idx, v);
    }

    tr[u].val = tr[l].val + tr[r].val;
    return u;
}
// finding the kth elelment in a range
int query(int left, int right, int st, int en, int k) {
    if (st == en) return st;
    int cnt = tr[tr[right].l].val - tr[tr[left].l].val;
    int mid = (st + en) / 2;

    if (cnt >= k) return query(tr[left].l, tr[right].l, st, mid, k);
    else      return query(tr[left].r, tr[right].r, mid + 1, en, k-cnt);
}

int V[N], root[N], a[N];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    map<int, int> mp;
    int n, q;
    cin >> n;

    for (int i = 1; i <= n; i++) cin >> a[i], mp[a[i]];
    int c = 0;

    for (auto& [x, y] : mp) y = ++c, V[c] = x;
    root[0] = build(1, n);

    for (int i = 1; i <= n; i++) {
        root[i] = update(root[i - 1], 1, n, mp[a[i]], 1);
    }

    cin >> q;
    while (q--) {
        LL l, r, k;
        cin >> l >> r >> k;

        LL gg = query(root[l - 1], root[r], 1,n, r-l+1 );
        LL val = V[gg];
        LL rem = val-(r-l+1);

        if(rem<k) {
            cout<<k-rem+val<<"\n";
            continue;
        }

        int lo = 1, hi = r-l+1, res = r-l+1;
        while(lo<=hi){
            int mid = (lo+hi)>>1;
            int idx = query(root[l-1], root[r] , 1, n, mid);
            int VAL = V[idx];
            int need = VAL-mid;
            if(need>=k){
                res = mid, hi = mid -1;
            }
            else lo = mid + 1;
        }

        if(res==1){
            cout<<k<<"\n";
            continue;
        }
        else {
           LL gg = query(root[l-1], root[r], 1, n, res-1); 
           LL val =  V[gg];
           LL rem = val - (res-1);
           cout<<k-rem+val<<"\n";
        }
    }
}
