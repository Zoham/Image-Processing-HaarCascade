#include "edu_hon5037tamu_detection_OpencvClass.h"
#define printf(...) __android_log_print(ANDROID_LOG_DEBUG, "TAG", __VA_ARGS__);


JNIEXPORT Mat& JNICALL Java_edu_hon5037tamu_detection_OpencvClass_faceDetection
  (JNIEnv * jenv, jclass, jstring jFileName, jlong addrRgba) {
         cv:: Mat& frame = *(Mat*)addrRgba;
        __android_log_print(ANDROID_LOG_DEBUG, "LOG_TAG", "Need to print *****************LA MAISON DE MON PERE N'EST PAS GROS **************\n");
        LOGD("Need to print *****************LA MAISON DE MON PERE N'EST PAS GROS **************\n");

        const char *jnamestr = jenv->GetStringUTFChars(jFileName, NULL);
	        printf("String is %s -------------",jnamestr)
            string stdFileName(jnamestr);

        const char *jnamestr1= jenv->GetStringUTFChars(jFileName, NULL);
            string stdFileName1(jnamestr1);

            CascadeClassifier face_cascade;
            CascadeClassifier eyes_cascade;

            face_cascade.load(stdFileName);
            eyes_cascade.load(stdFileName1);
    if(face_cascade.empty())
    {
        printf("Classifier1 empty-------------------------------");
    }
    else if (eyes_cascade.empty())
        {
        printf("Classifier2 empty-------------------------------");
        }
    else
    {
        printf("Both Classifiers loaded Fabulously-------------------------------");
    }
        //store face and then applpy Haar for the eyes


    vector <cv::Rect> faces;

    Mat frame_gray;

    cvtColor( frame, frame_gray, CV_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    GaussianBlur( frame, frame_gray, Size( 7,7 ), 0, 0 );


    face_cascade.detectMultiScale( frame, faces, 1.01, 3, 0 |CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));

    printf("%d Face -------------------------------------", faces.size());

    for (int i = 0; i<faces.size(); i++)
    {
        printf("Face Inside -------------------------------------");
        Point center(faces[i].x + faces[i].width * 0.9, faces[i].y + faces[i].height * 0.9);
        //ellipse(frame, center, Size(faces[i].width * 0.9, faces[i].height * 0.9), 0, 0, 360, cv::Scalar(255, 0, 255), 4, 8, 0);

        Mat faceROI = frame(faces[i]);
        printf(" %d, %d Face Ellipse---------------------------------------",faces[i].x,faces[i].y );

        std::vector <Rect> eyes;
        printf("Eyes --------------------------------------------");
        eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, cv::Size(20, 20));

        printf("%d Eyes Size ---------------------------------", eyes.size());
        for (size_t j = 0;j<eyes.size();j++)
        {
            printf("Eyes Inside------------------------------");

            Point center(faces[i].x + eyes[j].x + eyes[j].width * 0.5, faces[i].y + eyes[j].y + eyes[j].height * 0.5);
            int radius = cvRound((eyes[j].width + eyes[j].height) * 0.25);
            circle(frame, center, radius, Scalar(255, 0, 0),4, 8, 0);

             printf(" %d, %d Eyes Ellipse---------------------------------------",eyes[i].x,eyes[i].y );

        }

    }
    return frame;
}

   //detect(frame);






/*
void detect(Mat& frame) {
        printf("*****************LA MAISON DE MON PERE N'EST PAS GROS **************\n");
        LOGD("*****************LA MAISON DE MON PERE N'EST PAS GROS **************\n");


//set location for haar cascade classcifier.




      String face_cascade_name = "haarcascade_frontalface_alt2.xml";
      String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";

      FILE* file = fopen("storage/sdcard0/hello.txt","w");

      CascadeClassifier face_cascade;
      CascadeClassifier eyes_cascade;

//Loading the haar cascade classifier.
        face_cascade.load( face_cascade_name );
        eyes_cascade.load( eyes_cascade_name );

        if (eyes_cascade.empty())		///
            {
                printf ( "**************** YO MAMA ********************************************** \n");
         }
         else
         {
                 printf("******************THIS BII IS IN THERE IT JUST DOESNT WANT TO WORK AUSE ITS BEING A S.O.B ************************ \n");
        }


        //if(face_cascade.load( face_cascade_name )== false ) {
            //printf("*******************--(!)Error loading******************\n");
         //}

       // if(eyes_cascade.load( eyes_cascade_name )== false ) {
          //  printf("*******************--(!)Error loading**************\n");
            // }
        //CascadeClassifier face_cascade;
        //CascadeClassifier eyes_cascade;

       //face_cascade.load( "C:/storage/emulated/0/Data/haarcascade_frontalface_alt2.xml" );
       //eyes_cascade.load( "C:/storage/emulated/0/Data/haarcascade_eye_tree_eyeglasses.xml" );



        vector<cv::Rect> faces;
        Mat frame_gray;


        cvtColor( frame, frame_gray, CV_BGR2GRAY );
        equalizeHist( frame_gray, frame_gray );

         //-- Detect faces
        // face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));

         for( size_t i = 0; i < faces.size(); i++ )
         {
          Point center ( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
          ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, cv:: Scalar( 255, 0, 255 ), 4, 8, 0 );

           Mat faceROI = frame_gray( faces[i]);

           std::vector<Rect> eyes;

           //-- In each face, detect eyes
          // eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));

           for( size_t j = 0; j < eyes.size(); j++ )
            {
              Point center( faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5 );
             int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
              circle( frame, center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
            }
         }


}*/