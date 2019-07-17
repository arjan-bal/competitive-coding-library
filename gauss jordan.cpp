bool gauss()
{
	int i=0;

    for(int cbit=st; cbit>=0 && i<n; --cbit){
        for(int j=i; j<n; ++j){
            if(((vec[j]>>cbit)&1)==0) continue;
            swap(vec[i], vec[j]);
            break;
        }

        if(((vec[i]>>cbit)&1)==0) continue;

        for(int j=i+1; j<n; ++j){
            if((vec[j]>>cbit)&1) vec[j]^=vec[i];
            if(!vec[j]){
                return 1;
            }
        }

        ++i;
    }
    return 0;
}