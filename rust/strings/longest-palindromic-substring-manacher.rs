/**
    Manacher's algorithm for finding the longest palindromic substring. Returns two vectors:
    <ol>
        <li>max_odd: let x = max_odd[i]. This means that s[i - x] == s[i + x] and longest odd length palindrome centered at i is of length 2 * x + 1.</li>
        <li>max_even: let x = max_even[i]. This means that s[i - x - 1] == s[i + x] and longest even length palindrome centered at i is of length 2 * x + 2.</li>
    </ol>
    NOTE: -1 in max_even[i] means that there is no even length palindrome centered at i.
*/
fn manachers<T: std::cmp::PartialEq>(s: &Vec<T>) -> (Vec<usize>, Vec<i32>) {
    let n = s.len();
    let mut max_odd = vec![0; n];
    let mut max_even = vec![0; n];

    let mut l = 0;
    let mut r: i32 = -1;
    for i in 0..n as i32 {
        let mut k = match i as i32 > r {
            true => 1,
            false => min(max_odd[(l + r - i) as usize], (r - i) as usize),
        } as i32;
        while i - k >= 0 && i + k < n as i32 && s[(i - k) as usize] == s[(i + k) as usize] {
            k += 1;
        }
        k -= 1;
        max_odd[i as usize] = k as usize;
        if i + k > r {
            l = i - k;
            r = i + k;
        }
    }

    let mut l = 0;
    let mut r: i32 = -1;
    for i in 0..n as i32 {
        let mut k = match i > r {
            true => 0,
            false => min(max_even[(l + r - i + 1) as usize] as i32, r - i + 1),
        };
        while i - k - 1 >= 0 && i + k < n as i32 && s[(i - k - 1) as usize] == s[(i + k) as usize] {
            k += 1;
        }
        k -= 1;
        max_even[i as usize] = k;
        if i + k > r {
            l = i - k - 1;
            r = i + k;
        }
    }

    (max_odd, max_even)
}