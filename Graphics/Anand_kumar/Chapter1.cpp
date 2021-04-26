#include"vec3.h"
#include<fstream>
using namespace std;
int main(){
    int x = 200;
    int y = 100;
    ofstream ostream;
    ostream.open("Chapter1.ppm");
    ostream << "P3\n" << x << " " << y << "\n255\n";
    for(int j = y-1 ; j >= 0 ; j--){
        for(int i = 0 ; i < x ; i++){
            vec3 colors(float(i) / float(x) , float(j) / float(y) , 0.2);
            int r = int(255.99*colors[0]);
            int g = int(255.99*colors[1]);
            int b = int(255.99*colors[2]);

            ostream << r << " " << g << " " << b << "\n";
        }
    }
    ostream.close();
    return 0;
}
