// Extended euclidean algorithm
fn gex(a: i64, b: i64, x: &mut i64, y: &mut i64) -> i64 {
    if a == 0 {
        *x = 0;
        *y = 1;
        return b;
    }

    let mut x1 = 0;
    let mut y1 = 0;
    let g = gex(b % a, a, &mut x1, &mut y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    g
}

// Returns the mod inverse when a & m are co-prime,
// panics otherwise
fn inv(a: i64, m: i64) -> i64 {
    let mut x: i64 = 0;
    let mut y: i64 = 0;
    let g = gex(a, m, &mut x, &mut y);
    assert!(g == 1);
    (x % m + m) % m
}

// x^y mod m
fn power(x: i64, y: i64, m: i64) -> i64 {
    if y == 0 {
        return 1;
    }

    let mut p = power(x, y >> 1, m) % m;
    p = p * p % m;
    if y % 2 == 1 {
        (x * p) % m
    } else {
        p
    }
}