template <typename T> class SegmentTree {
public:
    int n;
    vector<T> t, lazy;
    vector<bool> isLazy;
    // default value;
    T out = 0;

    template<typename U>
    void init(const U &arr, int N) {
        n = N;
        t = vector<T>(4 * N + 4);
        lazy = vector<T>(4 * N + 4);
        isLazy = vector<bool> (4 * N + 4, false);
        build(arr, 1, 0, n - 1);
    }

    template<typename U>
    void buildApply(int i, U val) {
        // {... update here ...}
        t[i] = val;
    }

    void mergeApply(T &cur, T &left, T &right) {
        // {... update here ...}
        cur = left + right;
    }

    template<typename U>
    void pointApply(int i, U val) {
        // {... update here ...}
        t[i] += val;
    }

    void push(int i, int s, int e) {
        // handle lazy propogation here
        if (s != e) {
            isLazy[i * 2] = true;
            isLazy[i * 2 + 1] = true;
            lazy[i * 2] += lazy[i];
            lazy[i * 2 + 1] += lazy[i];
        }
        // {... update here ...}
        t[i] += (e - s + 1) * lazy[i];
        isLazy[i] = false;
        lazy[i] = 0;
    }

    template<typename U>
    void pointUpdate(int idx, U val) {
        pointUpdate(idx, val, 1, 0, n - 1);
    }

    template<typename U>
    void rangeUpdate(int ri, int rj, U val) {
        rangeUpdate(ri, rj, val, 1, 0, n - 1);
    }

    T query(int qi, int qj) {
        return query(qi, qj, 1, 0, n - 1);
    }

private:
    template<typename U>
    void build(const U &arr, int i, int s, int e) {
        if (s == e) {
            buildApply(i, arr[s]);
            return;
        }
        int mid = (s + e) >> 1;
        build(arr, i * 2, s, mid);
        build(arr, i * 2 + 1, mid + 1, e);
        mergeApply(t[i], t[i * 2], t[i * 2 + 1]);
    }

    template<typename U>
    void pointUpdate(int idx, U val, int i, int s, int e) {
        if (isLazy[i]) {
            push(i, s, e);
        }

        if (idx > e or idx < s) {
            return;
        }
        if (s == e) {
            pointApply(i, val);
            return;
        }
        int mid = (s + e) >> 1;
        pointUpdate(idx, val, i * 2, s , mid);
        pointUpdate(idx, val, i * 2 + 1, mid + 1, e);
        mergeApply(t[i], t[i * 2], t[i * 2 + 1]);
    }

    template<typename U>
    void rangeUpdate(int ri, int rj, U val, int i, int s, int e) {
        if (isLazy[i]) {
            push(i, s, e);
        }
        if (ri > e or rj < s) {
            return;
        }
        if (ri <= s and rj >= e) {
            isLazy[i] = true;
            lazy[i] = val;
            push(i, s, e);
            return;
        }
        int mid = (s + e) >> 1;
        rangeUpdate(ri, rj, val, i * 2, s, mid);
        rangeUpdate(ri, rj, val, i * 2 + 1, mid + 1, e);
        mergeApply(t[i], t[i * 2], t[i * 2 + 1]);
    }

    T query(int qi, int qj, int i, int s, int e) {
        if (isLazy[i]) {
            push(i, s, e);
        }
        if (e < qi or s > qj) {
            return out;
        }
        if (s >= qi and e <= qj) {
            return t[i];
        }
        int mid = (s + e) >> 1;
        T leftAns = query(qi, qj, i * 2, s, mid);
        T rightAns = query(qi, qj, i * 2 + 1, mid + 1, e);
        T anshere;
        mergeApply(anshere, leftAns, rightAns);
        return anshere;
    }
};
