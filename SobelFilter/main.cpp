#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
    Mat frame;
    bool fotoGemaakt = false;
    VideoCapture video(1); // open the video camera no. 0

    if (!video.isOpened())  // if not success, exit program
    {
        cout << "Geen verbinding met webcam" << endl;
        return -1;
    }

    //double dWidth = video.get(CV_CAP_PROP_FRAME_WIDTH);
    //double dHeight = video.get(CV_CAP_PROP_FRAME_HEIGHT);

    namedWindow("Video",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"

    while (!fotoGemaakt)
    {
        bool vidOK = video.read(frame); // lezen van frame

        if (!vidOK) //Controle op frame
        {
             cout << "Geen nieuw frame gevonden" << endl;
             break;
        }
        imshow("Video", frame); //Nieuw videoframe tonen

        if (waitKey(30) == 13) //Wachten op Enter
        {
            cout << "Foto gemaakt" << endl;
            destroyWindow("Video");
            namedWindow("Foto",WINDOW_AUTOSIZE);
            imshow("Foto",frame);
            imwrite("pngFoto.png", frame); //Foto opslaan in een bestand pngFoto.png
            fotoGemaakt = true;
            break;
        }
    }





    cout << "Kies het gewenste effect: 1=sobel" << endl;
    while (fotoGemaakt)
    {
        if(waitKey(30) == 49){
            /*Sobel detectie*/
    Mat src, src_gray, grad, image, grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y; //sobelvariabelen


    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;


    //Foto's inlezen
    image = imread("pngFoto.png", CV_LOAD_IMAGE_COLOR);
    src = imread("pngFoto.png");

    //filter toepassen
    GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );
    cvtColor( src, src_gray, CV_RGB2GRAY );

    // X factor
    Sobel( src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
    // Y factor
    Sobel( src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );

    convertScaleAbs( grad_x, abs_grad_x );
    convertScaleAbs( grad_y, abs_grad_y );
    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );

    //Foto's tonen
    imshow( "foto normaal", image );
    imshow( "foto Sobeleffect",grad);


            if (waitKey (0)){
                return 0;
            }
        }
    }

    return 0;

}


//***  Testprogramma voor het openen van een blauw scherm. ***//
//    Mat test(500,1000, CV_8UC3, Scalar(255,0,0));

//    //FOUTENCONTROLE
//    IF (TEST.EMPTY())
//    {
//        COUT << "GEEN AFBEELDING INGELADEN." << ENDL;
//        WAITKEY(0);//ONEINDIG WACHTEN OP HET DUWEN VAN EEN TOETS
//        RETURN(-1);
//    }
//
//    NAMEDWINDOW("VENSTER",WINDOW_NORMAL);
//    IMSHOW("VENSTER",TEST);
//
//    WAITKEY(0);


 //******FOTO OPSLAAN*****/////
    // Capture the Image from the webcam

    // Get the frame
    //Mat pngFoto;
    //frame >> pngFoto;

//    if(pngFoto.empty())
//    {
//      std::cerr << "Fout bij opslaan, geen foto in pngFoto" << std::endl;
//    }
    // Save the frame into a file
    //imwrite("pngFotoSaved.png", frame); // A JPG FILE IS BEING SAVED
//****************************************//
