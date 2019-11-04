//used to find propery such as min, max, sum etc. over subsets or supersets

const int N=21;

for(int i = 0; i<(1<<N); ++i)
    F[i] = A[i];

//property over subsets
for(int i = 0;i < N; ++i) for(int mask = 0; mask < (1<<N); ++mask){
    if(mask & (1<<i)) F[mask] += F[mask^(1<<i)];
}

//property over supersets
for(int i = 0;i < N; ++i) for(int mask = (1<<N)-1; mask >= 0; --mask){
    if(mask & (1<<i)) continue;
    F[mask] += F[mask|(1<<i)];
}