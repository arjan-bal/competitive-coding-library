int grundyPosition(int x , int y){
    if(memo[x][y] != -1) return memo[x][y] ;
    set<int>s ; s.clear() ;
    for(int i = 0 ; i < 3 ; i++){
        if(valid(x+dx[i], y+dy[i])){
            s.insert(grundyPosition(x+dx[i],y+dy[i])) ;
        }
    }
    int ret = 0;
    while(s.find(ret) != s.end())  ret++ ;
    return memo[x][y] = ret ;
}