//
// Created by edgar on 10/31/20.
//

// TU Dresden, Inf, CV1 Ex1, Holger Heidrich
// non-linear grey value transformation, Gamma correction
// --
// This program does Gamma correction.
// Clicking into the "GreyCurve"-image gives a point which the gamma curve has to go trough.
// The "GreyCurve"-image itself has size (512,512). Point (0,0) is upper left corner for the image, but (0,0) of the curve is at (0,511) in the curve image. \n"
// Map values x of the input image to values y of an output image by creating and using a lookup table.\n"
//
// the input image is taken from
// https://github.com/opencv/opencv/tree/master/samples/data
//-----------------------------------------------------------------------------


#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <algorithm>
#include <cmath>

using namespace cv;
using namespace std;

#define MaxPoints 1
int nb_points = 0;

Mat MapCurveImage512;
Mat image, color_img, result_img;
Point    SrcPtInt[(int)MaxPoints];
unsigned char LUtable[256];

void help()
{
    cout <<
         "\nTU Dresden, CV1 Ex1, Holger Heidrich\n"
         "This program does Gamma correction.\n"
         "Clicking into the \"GreyCurve\"-image gives a point which the gamma curve has to go trough.\n"
         "The \"GreyCurve\"-image itself has size (512,512). Point (0,0) is upper left corner for the image, but (0,0) of the curve is at (0,511) in the curve image. \n"
         "Map values x of the input image to values y of an output image.\n"
         "Call:\n"
         "./image Image [image-name Default: fruits.jpg]\n" << endl;
}

void apply_LUT()
{
    CV_Assert(result_img.depth() == CV_8U);
    CV_Assert(color_img.depth() == CV_8U);

    int channels = result_img.channels();

    int nRows = result_img.rows;
    int nCols = result_img.cols * channels;

//    if (result_img.isContinuous())
//    {
//        nCols *= nRows;
//        nRows = 1;
//    }

    int i,j;
    uchar* rp, *cp;
    for( i = 0; i < nRows; ++i)
    {
        rp = result_img.ptr<uchar>(i);
        cp = color_img.ptr<uchar>(i);
        for ( j = 0; j < nCols; ++j)
        {
            rp[j] = LUtable[cp[j]];
        }
    }
}

void on_mouse( int event, int x, int y, int flags, void* param )
{
    switch( event )
    {
        case EVENT_LBUTTONDOWN:
        {
            // new point to pass trough
            SrcPtInt[nb_points].x=x;
            SrcPtInt[nb_points].y=y;
            MapCurveImage512 = 0;

            // read the curve point
            int x1 = SrcPtInt[0].x;
            int y1 = 511 - SrcPtInt[0].y; // "511 -" cause we have "0" in lower left corner

            // determine gamma coefficient
            // (want to cheat? see end of file)

            double gamma = log((511 - y)) / log(x);

            cout << gamma;

            // create the LUT for that curve function and
            // draw the gamma curve in the MapCurveimage (pixelwise)
            // your code for the gamma curve and color transform (instead of or additionally to the following line)
            // line example

            for (int i=0; i<256; i++)
            {
                LUtable[i] = clamp((int) pow(i, gamma), 0, 255);
            }

            for(int ix=0; ix<255; ix+=1){
                line(MapCurveImage512, Point(2*ix,511 - 2*LUtable[ix]),  Point(2*(ix+1), 511 - 2*LUtable[ix+1]), CV_RGB(255, 255, 255));
            }

            // use the lookup table (LUT) to map the input image to the result image
            // use the same LUT for each color channel (or fantasize)
            apply_LUT();

            // show non-linear mapping curve
            imshow("GreyCurve", MapCurveImage512);

            // show the result
            imshow( "result image", result_img);
        }
            break;
    }
}  // void on_mouse( int event, int x, int y, int flags, void* param )


int main( int argc, char** argv )
{
    help();

    char* filename = argc == 2 ? argv[1] : (char*)"../images/fruits.jpg";
    image = imread(filename, 1);
    color_img = image.clone();
    result_img = image.clone();

    namedWindow( "GreyCurve");
    namedWindow( "Fruits!");
    imshow( "Fruits!", color_img);

    MapCurveImage512.create(512, 512, CV_8U);
    MapCurveImage512 = 0;
    imshow("GreyCurve", MapCurveImage512);

    setMouseCallback( "GreyCurve", on_mouse, 0 );
    waitKey();

    return 0;
}





















































































/*
// determine g of y(x):=x^g
double xd = x/511.0;
double yd = (511-y)/511.0;
double gamma = log(yd)/log(xd);
*/



























































