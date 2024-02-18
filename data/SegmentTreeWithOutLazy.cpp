template <typename T> class SegmentTree {
public:
    int n;
    vector<T> t;
    // default value;
    T out = 0;

    template<typename U>
    void init(const U &arr, int N) {
        n = N;
        t = vector<T>(4 * N + 4);
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

    template<typename U>
    void pointUpdate(int idx, U val) {
        pointUpdate(idx, val, 1, 0, n - 1);
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

    T query(int qi, int qj, int i, int s, int e) {
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
