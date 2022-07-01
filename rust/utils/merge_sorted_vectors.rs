fn merge_sorted<T: PartialOrd + Copy>(v1: &Vec<T>, v2: &Vec<T>) -> Vec<T> {
    let mut res: Vec<T> = Vec::with_capacity(v1.len() + v2.len());
    let mut it1 = v1.iter().peekable();
    let mut it2 = v2.iter().peekable();

    while it1.peek() != None && it2.peek() != None {
        if it1.peek().unwrap() < it2.peek().unwrap() {
            res.push(*it1.next().unwrap());
        } else {
            res.push(*it2.next().unwrap());
        }
    }

    res.extend(it1);
    res.extend(it2);
    return res;
}
