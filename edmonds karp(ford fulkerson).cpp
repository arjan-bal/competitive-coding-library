int inf=1e9;

vi par;

void init(int n)
{
    par.resize(n);
}

int bfs(int s, int t)
{
    fill(all(par), -1);
    par[s]=-2;
    queue<pii> q;
    q.push(mp(s, inf));
    pii top;
    int nf;
    while(!q.empty()){
        top=q.front();
        q.pop();
        for(auto i:adj[top.ff]){
            nf=min(top.ss, cap[top.ff][i]);
            if(!nf || par[i]!=-1) continue;
            par[i]=top.ff;
            if(i==t) return nf;
            q.push(mp(i,nf));
        }
    }
    return 0;
}

int maxflow(int s, int t)
{
    int ans=0, flow, cur;
    while(flow=bfs(s, t)){
        ans+=flow;
        cur=t;
        while(cur!=s){
            cap[par[cur]][cur]-=flow;
            cap[cur][par[cur]]+=flow;
            cur=par[cur];
        }
    }
    return ans;
}
