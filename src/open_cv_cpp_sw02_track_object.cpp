//https://docs.opencv.org/4.x/d2/d0a/tutorial_introduction_to_tracker.html

#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cstring>
 
using namespace std;
using namespace cv;
 
int main( int argc, char** argv ){
    // show help
    //  if(argc<2){
    //  cout<<
    //  " arguments missing \n"
    //  " Usage: tracker <video_name>\n"
    //  " examples:\n"
    //  " example_tracking_kcf Bolt/img/%04d.jpg\n"
    //  " example_tracking_kcf faceocc2.webm\n"
    //  << endl;
    //  return 0;
    //  }
    
    // declares all required variables
    Rect roi;
    Mat frame;
    
    // create a tracker object
    Ptr<Tracker> tracker = TrackerCSRT::create();
    
    // set input video
    
    //std::string video = argv[1];
    VideoCapture cap(0);
    
    // get bounding box
    cap >> frame;
    roi=selectROI("tracker",frame);
    
    //quit if ROI was not selected
    if(roi.width==0 || roi.height==0)
    return 0;
    
    // initialize the tracker
    tracker->init(frame,roi);
    
    // perform the tracking process
    printf("Start the tracking process, press ESC to quit.\n");

    for ( ;; ){
        // get frame from the video
        cap >> frame;
        
        // stop the program if no more images
        if(frame.rows==0 || frame.cols==0)
        break;
        
        // update the tracking result
        bool ok = tracker->update(frame, roi);

        if (ok){
            // draw the tracked object
            rectangle( frame, roi, Scalar( 255, 0, 0 ), 2, 1 );
        }
        else
        {
        // Tracking failure detected.
        putText(frame, "Tracking failure detected", Point(100,80), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0,0,255),2);
        }
            
        
        // show image with the tracked object
        imshow("tracker",frame);
        
        //quit on ESC button
        // Exit if ESC pressed.
        int k = waitKey(1);
        if(k == 27)    {
            break;
        }
    }
 
 return 0;
}

// //https://learnopencv.com/object-tracking-using-opencv-cpp-python/
// #include <opencv2/opencv.hpp>
// #include <opencv2/tracking.hpp>
// #include <opencv2/core/ocl.hpp>
 
// using namespace cv;
// using namespace std;
 
// // Convert to string
// #define SSTR( x ) static_cast< std::ostringstream & >( 
// ( std::ostringstream() << std::dec << x ) ).str()
 
// int main(int argc, char **argv)
// {
//     // List of tracker types in OpenCV 3.4.1
//     string trackerTypes[8] = {"BOOSTING", "MIL", "KCF", "TLD","MEDIANFLOW", "GOTURN", "MOSSE", "CSRT"};
//     // vector <string> trackerTypes(types, std::end(types));
 
//     // Create a tracker
//     string trackerType = trackerTypes[2];
 
//     //Ptr<Tracker> tracker;
//     Ptr<TrackerKCF> tracker = TrackerKCF::create();
 
//     #if (CV_MINOR_VERSION < 3)
//     {
//         tracker = Tracker::create(trackerType);
//     }
//     #else
//     {
//         // if (trackerType == "BOOSTING")
//         //     tracker = TrackerBoosting::create();
//         if (trackerType == "MIL")
//             tracker = TrackerMIL::create();
//         if (trackerType == "KCF")
//             tracker = TrackerKCF::create();
//         // if (trackerType == "TLD")
//         //     tracker = TrackerTLD::create();
//         // if (trackerType == "MEDIANFLOW")
//         //     tracker = TrackerMedianFlow::create();
//         // if (trackerType == "GOTURN")
//         //     tracker = TrackerGOTURN::create();
//         // if (trackerType == "MOSSE")
//         //     tracker = TrackerMOSSE::create();
//         if (trackerType == "CSRT")
//             tracker = TrackerCSRT::create();
//     }
//     #endif
//     // Read video
//     VideoCapture video("videos/chaplin.mp4");
     
//     // Exit if video is not opened
//     if(!video.isOpened())
//     {
//         cout << "Could not read video file" << endl; 
//         return 1; 
//     } 
 
//     // Read first frame 
//     Mat frame; 
//     bool ok = video.read(frame); 
 
//     // Define initial bounding box 
//     Rect2d bbox(287, 23, 86, 320); 
 
//     // Uncomment the line below to select a different bounding box 
//     // bbox = selectROI(frame, false); 
//     // Display bounding box. 
//     rectangle(frame, bbox, Scalar( 255, 0, 0 ), 2, 1 ); 
 
//     imshow("Tracking", frame); 
//     tracker->init(frame, bbox);
     
//     while(video.read(frame))
//     {     
//         // Start timer
//         double timer = (double)getTickCount();
         
//         // Update the tracking result
//         bool ok = tracker->update(frame, bbox);
         
//         // Calculate Frames per second (FPS)
//         float fps = getTickFrequency() / ((double)getTickCount() - timer);
         
//         if (ok)
//         {
//             // Tracking success : Draw the tracked object
//             rectangle(frame, bbox, Scalar( 255, 0, 0 ), 2, 1 );
//         }
//         else
//         {
//             // Tracking failure detected.
//             putText(frame, "Tracking failure detected", Point(100,80), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0,0,255),2);
//         }
         
//         // Display tracker type on frame
//         putText(frame, trackerType + " Tracker", Point(100,20), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50,170,50),2);
         
//         // Display FPS on frame
//         putText(frame, "FPS : " + SSTR(int(fps)), Point(100,50), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50,170,50), 2);
 
//         // Display frame.
//         imshow("Tracking", frame);
         
//         // Exit if ESC pressed.
//         int k = waitKey(1);
//         if(k == 27)
//         {
//             break;
//         }
 
//     }
// }