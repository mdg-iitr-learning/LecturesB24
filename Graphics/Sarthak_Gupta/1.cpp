#include<iostream>
#include<fstream>
#include<cstdio>

int frac_to_rgb(float i){
	int f = int(255.99*i);
//	if(f>255) f = 255;
//	if(f<0) f = 0;
	return f;
}

using namespace std;

int main(){
	int npx = 200;
	int npy = 100;
	ofstream ofs("test.ppm", ios::out | ios::app);
	ofs<<"P3 \n"<<npx<<" "<<npy<<"\n255"<<endl;
	for(int j = 0 ; j<npy ; j++ ){
		for(int i = 0 ; i<npx ; i++){
			float b = float(i)/float(npx);
			float r = 0.9;
			float g = float(j)/float(npy);
			ofs<<frac_to_rgb(r) << " " << frac_to_rgb(g) << " " << frac_to_rgb(b)<<endl;
		}
	}
}

/* Played around with the loops to see what and how i can influence the actal image output,8 
*/

