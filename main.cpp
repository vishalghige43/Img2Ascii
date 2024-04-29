#include<iostream>
#include <opencv2/opencv.hpp>
#include<fstream>
#include<math.h>

using namespace std;
using namespace cv;

int calculateAvg(Mat img,int row,int col,int scale){
    int sum=0;
    int pixelCnt=0;
    int r=row,c=col;

    while(r<row+scale&& r<img.rows){
        while(c<col+scale&& c<img.cols){
            sum+=(int)img.at<uchar>(r,c);
            pixelCnt++;
            c++;
        }
        r++;
    }
    return sum/pixelCnt;
}
    
int main(int argc,char **argv){
    if(argc!=2){
        cout<<"Specify the image path...\n";
        return EXIT_FAILURE;
    }
    string path="../";path+=argv[1];
    
    Mat img=imread(path);
    string ascii_level_70="$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
    string ascii_level_10="@%#*+=-:. ";

    string output;
    resize(img,img,{0,0},0.5,0.5);

    cvtColor(img,img,COLOR_BGR2GRAY);

    int scale=8;

    for(int i=0;i<img.rows;i+=scale){
        string text="";
        for(int j=0;j<img.cols;j+=scale){
            int pixel=calculateAvg(img,i,j,scale);
            text+=ascii_level_70[69*pixel/255];
            text+=" ";
        }
        output+=text+"\n";
    }
    cout<<output<<endl;
    
    return 0;
}