// Sieve that runs in O(n).
// Returns a list of smallest prime factors
// for each i <= n and
// and a lost of all primes <= n
fn sieve(n: i32) -> (Vec<i32>, Vec<i32>) {
    let mut lp: Vec<i32> = (0..n+1).map(|_| 0).collect();
    let mut prime: Vec<i32> = Vec::with_capacity(n as usize + 1);
    for i in 2..n as usize + 1 {
        if lp[i] == 0 {
            lp[i] = i as i32;
            prime.push(i as i32);
        }
        for j in &prime {
            if *j > lp[i as usize] || i as i32 * j > n {
                break;
            }
            lp[i * *j as usize] = *j;
        }
    }
    return (prime, lp);
}
