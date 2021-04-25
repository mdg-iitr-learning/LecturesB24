#include<fstream>
#include "vec3.h"

int main(){
	int npx = 200;
	int npy = 100;
	ofstream ofs ("second.ppm" , ios::out | ios::app);
	ofs<<"P3 \n"<<npx<<" "<<npy<<"\n255"<<endl;

	for(int j = 0 ; j<npy ; j++ ){
		for(int i = 0 ; i<npx ; i++){
			vec3 col( 0.9 , float(j)/float(npy) , float(i)/float(npx));
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			ofs<<ir << " " << ig << " " << ib <<endl;
		}
	}
	
	ofs.close();
}
