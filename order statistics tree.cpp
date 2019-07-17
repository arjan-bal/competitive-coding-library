#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update

using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> oset;	
typedef tree<int, int, less<int>, rb_tree_tag, tree_order_statistics_node_update> omap;

/*
functions:
1)insert()
2)find_by_order(x) returns iterator to xth smallest element
3)order_of_key(x) return no of elems less than x
4)erase(number)
*/