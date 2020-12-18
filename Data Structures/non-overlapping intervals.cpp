void insert(set<pii> &s, pii cur)
{
	auto it=s.upper_bound(cur);
	vpii rem;
	if(it!=s.end() && it->ff==cur.ss+1){
		cur.ss=it->ss;
		rem.pb(*it);
	}
	if(it!=s.begin()){
		--it;
		if(it->ss+1==cur.ff){
			cur.ff=it->ff;
			rem.pb(*it);
		}
	}
	for(auto i:rem)
		s.erase(i);
	s.insert(cur);
}

void erase(set<pii> &s, pii cur)
{
	auto it=s.upper_bound(cur);
	--it;
	pii tmp=*it;
	s.erase(it);
	if(tmp.ff<cur.ff) s.insert({tmp.ff, cur.ff-1});
	if(tmp.ss>cur.ss) s.insert({cur.ss+1, tmp.ss});
}