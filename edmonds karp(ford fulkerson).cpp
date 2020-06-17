const int N=2e3+1;
int inf=1e9;

int cap[N][N];
vector<int> par, adj[N];

void add_edge(int a, int b, int c)
{
    cap[a][b]+=c;
    adj[a].pb(b);
    adj[b].pb(a);
}

int bfs(int s, int t)
{
    fill(all(par), -1);
    par[s]=-2;
    queue<pair<int, int>> q;
    q.push({s, inf});
    pair<int, int> top;
    int nf;
    while(!q.empty()){
        top=q.front();
        q.pop();
        for(auto i:adj[top.first]){
            nf=min(top.second, cap[top.first][i]);
            if(!nf || par[i]!=-1) continue;
            par[i]=top.first;
            if(i==t) return nf;
            q.push({i, nf});
        }
    }
    return 0;
}

int maxflow(int s, int t)
{
    int ans=0, flow, cur;
    while((flow=bfs(s, t))){
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

// par.resize(nodes+1);