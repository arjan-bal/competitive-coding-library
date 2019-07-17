double det3(double a, double b, double c, double d, double e, double f, double g, double h, double i) {
	double det[3][3] = { {a,b,c},{d,e,f},{g,h,i} };
	double d0 = det[0][0] * ((det[1][1] * det[2][2]) - (det[1][2] * det[2][1]));
	double d1 = det[0][1] * ((det[1][0] * det[2][2]) - (det[1][2] * det[2][0]));
	double d2 = det[0][2] * ((det[1][0] * det[2][1]) - (det[1][1] * det[2][0]));
	return d0 + d2 - d1;
}
 
void centercircle(double& cx, double& cy, double& cr2, int a, int b, int c){
	double ssq[] = { (x1 * x1) + (y1 * y1),(x2 * x2) + (y2 * y2) ,(x3 * x3) + (y3 * y3) };
	double A = det3(x1, y1, 1, x2, y2, 1, x3, y3, 1);
	double B = -det3(ssq[0], y1, 1, ssq[1], y2, 1, ssq[2], y3, 1);
	double C = det3(ssq[0], x1, 1, ssq[1], x2, 1, ssq[2], x3, 1);
	double D = -det3(ssq[0], x1, y1, ssq[1], x2, y2, ssq[2], x3, y3);
	cx = -B / (2 * A);
	cy = -C / (2 * A);
	cr2 = ((B*B) + (C*C) - (4 * A*D)) / (4 * A*A);
}
 
void centercircle(double& cx, double& cy, double& cr2, int a, int b){
	cx = (x1 + x2) / 2;
	cy = (y1 + y2) / 2;
	cr2 = distsq(x1, y1, x2, y2) / 4;
}