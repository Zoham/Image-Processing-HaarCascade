#include "edu_hon5037tamu_detection_OpencvClass.h"

#define printf(...) __android_log_print(ANDROID_LOG_DEBUG, "TAG", __VA_ARGS__);


JNIEXPORT void JNICALL
Java_edu_hon5037tamu_detection_OpencvClass_faceDetection(JNIEnv* jenv, jclass ,jstring jFileName,jlong addrRgba)
{
    cv::Mat &frame = *(Mat *) addrRgba;__android_log_print(ANDROID_LOG_DEBUG,"LOG_TAG", "Need to print *****************LA MAISON DE MON PERE N'EST PAS GROS **************\n");

    const char *jnamestr = jenv->GetStringUTFChars(jFileName, NULL);
printf("String is %s -------------",jnamestr)
    string stdFileName(jnamestr);

    CascadeClassifier face_cascade;
    face_cascade.load(stdFileName);

    if(face_cascade.empty())
    {
        printf("Classifier1 empty-------------------------------");
    }
    else
    {
        printf("Classifier1 loaded-------------------------------");
    }

    vector <cv::Rect> faces;

    cvtColor(frame, frame, CV_BGR2GRAY);
    GaussianBlur( frame, frame, Size( 7,7 ), 0, 0 );
    equalizeHist(frame, frame);

    face_cascade.detectMultiScale( frame, faces, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));

    printf("%d Face -------------------------------------", faces.size());

    for (int i = 0;i<faces.size();i++)
    {
        printf("Face Inside -------------------------------------");
        Point center(faces[i].x + faces[i].width * 0.5, faces[i].y + faces[i].height * 0.5);
        ellipse(frame, center, Size(faces[i].width * 0.5, faces[i].height * 0.5), 0, 0, 360, cv::Scalar(255, 0, 255), 4, 8, 0);

        Mat faceROI = frame(faces[i]);
        printf(" %d, %d Face Ellipse---------------------------------------",faces[i].x,faces[i].y );

        /*std::vector <Rect> eyes;

        eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));

        for (size_t j = 0;j<eyes.size();j++)
        {
            Point center(faces[i].x + eyes[j].x + eyes[j].width * 0.5, faces[i].y + eyes[j].y + eyes[j].height * 0.5);
            int radius = cvRound((eyes[j].width + eyes[j].height) * 0.25);
            circle(frame, center, radius, Scalar(255, 0, 0),4, 8, 0);
        }*/
    }
}