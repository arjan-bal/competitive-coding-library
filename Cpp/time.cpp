auto st=clock();
 
inline float ctime()
{
	return float(clock()-st)/CLOCKS_PER_SEC;
}