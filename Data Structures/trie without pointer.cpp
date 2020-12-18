struct node{
	int f=0;
	int child[2]={};
};

node nil;

vector<node> trie(1, nil);

inline void insert(int purana, int naya, int val)
{
	for(int idx=30; idx>=0; --idx){
		trie[naya].f=trie[purana].f+1;
		if((val>>idx)&1){			
			trie[naya].child[0]=trie[purana].child[0];
			purana=trie[purana].child[1];
			trie[naya].child[1]=trie.size();
			trie.pb(nil);
			naya=trie.size()-1;
			continue;
		}
		trie[naya].child[1]=trie[purana].child[1];
		purana=trie[purana].child[0];
		trie[naya].child[0]=trie.size();
		trie.pb(nil);
		naya=trie.size()-1;
	}
	trie[naya].f=trie[purana].f+1;
	return ;
}

int ans;

inline void qry1(int l, int r, int val)
{
	for(int idx=30; idx>=0; --idx){
		if((val>>idx)&1){
			//try to get 0
			if(trie[trie[r].child[0]].f - trie[trie[l].child[0]].f){
				l=trie[l].child[0];
				r=trie[r].child[0];
				continue;
			}
			//make do with 1
			ans|=(1<<idx);
			l=trie[l].child[1];
			r=trie[r].child[1];
			continue;
		}
		//try to get 1
		if(trie[trie[r].child[1]].f - trie[trie[l].child[1]].f){
			ans|=(1<<idx);
			l=trie[l].child[1];
			r=trie[r].child[1];
			continue;
		}
		l=trie[l].child[0];
		r=trie[r].child[0];
	}
	return ;
}

int rootIdx[N];

/*
rootIdx[v]=trie.size();
trie.pb(nil);
insert(rootIdx[u], trie.size()-1, val);
*/