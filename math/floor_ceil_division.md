# 切り上げ、切り捨て

```cpp
// floor(a / b)
template <class T>
T floor_div(T a, T b) {
    assert(b != 0);

    T q = a / b;
    T r = a % b;

    if (r != 0 && ((r > 0) != (b > 0))) {
        --q;
    }

    return q;
}

// ceil(a / b)
template <class T>
T ceil_div(T a, T b) {
    assert(b != 0);

    T q = a / b;
    T r = a % b;

    if (r != 0 && ((r > 0) == (b > 0))) {
        ++q;
    }

    return q;
}
```
