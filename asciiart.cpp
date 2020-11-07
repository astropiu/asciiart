#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <fstream>
#include <iterator>
#include<vector>
#include<string>
#include<sstream>
#include <string_view>
using namespace cv;
using namespace std;

array<char,11> ch= {'@','#','$','%','?','*','+',';',':',',','.'};
//array<char,16> ch= {'@','#','$','%','?','*','/','\\' , '(',')','+',';',':',',','.',' '};
vector<char> as;
void imgtoasci(Mat img){
    int nl=img.rows;
    int nc=img.cols;
    if(img.isContinuous()){
         nc= nc*nl;
          nl= 1;
    }
    string a;
    ifstream mf ("asciorder.txt");
    getline(mf,a);
    vector<char> asciorder (a.begin(),a.end());
       for (int j=0; j<nl; j++) {

          uchar* data= img.ptr<uchar>(j);

          for (int i=0; i<nc; i++) {
              as.push_back(ch[static_cast<int>(*data++/25)]);
          }}
}
int main(){
    Mat da= imread("sirdavid.jpg",0);
    Mat adpt;
    namedWindow("original");
    imshow("original",da);
   
    adaptiveThreshold(da,adpt,255,cv::ADAPTIVE_THRESH_MEAN_C,cv::THRESH_BINARY,9,5);
    namedWindow("adpt");
    imshow("adpt",adpt);
    adpt=da.clone();
    int ratio= adpt.rows/adpt.cols;
    resize(adpt,adpt,Size(500,500*ratio*0.85));
    imgtoasci(adpt);

    
    for(auto i=as.begin()+adpt.cols;i<as.end();i+=(adpt.cols+1)){
     as.insert(i,'\n');

     }
    cout<<as.size();
    ofstream myfile;
    myfile.open("asci16.txt");
    ostream_iterator<char> output_iterator(myfile, "");
    copy(as.begin(), as.end(), output_iterator);
    /*ostringstream oss;
    copy(as.begin(), as.end(), std::ostream_iterator<char>(oss,"") );
    string_view sv {oss.str()};
 

    Mat out (700,543,CV_8U,255);
    putText(out,static_cast<String>(sv),Point(5,0),FONT_HERSHEY_COMPLEX_SMALL,1,0);
    namedWindow("asci");
    imshow("ascii",out);
    waitKey();
    imwrite("asci.jpg",out);*/
    
   


}