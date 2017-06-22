package edu.hon5037tamu.detection;

import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

import org.opencv.android.BaseLoaderCallback;
import org.opencv.android.CameraBridgeViewBase;
import org.opencv.android.InstallCallbackInterface;
import org.opencv.android.JavaCameraView;
import org.opencv.android.LoaderCallbackInterface;
import org.opencv.android.OpenCVLoader;
import org.opencv.core.CvType;
import org.opencv.core.Mat;

import static edu.hon5037tamu.detection.OpencvClass.faceDetection;

public class MainActivity extends AppCompatActivity implements CameraBridgeViewBase.CvCameraViewListener2 {
    private static String TAG = "MainActivity";
    JavaCameraView javaCameraView;
    Mat mRgba;
    Mat Ret;


    static {

        System.loadLibrary("MyOpencvLibs");
    }


    BaseLoaderCallback mLoaderCallback = new BaseLoaderCallback(this) {
        @Override
        public void onManagerConnected(int status) {
            switch (status) {
                case BaseLoaderCallback.SUCCESS:
                    javaCameraView.enableView();
                    break;
                default:
                    super.onManagerConnected(status);
                    break;
            }
        }
};

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Log.i(TAG, "FileLocation: " + Environment.getExternalStorageDirectory().getAbsolutePath());
        javaCameraView=(JavaCameraView)findViewById(R.id.java_camera_view);
        javaCameraView.setVisibility(View.VISIBLE);
        javaCameraView.setCvCameraViewListener(this);
    }


    @Override
    protected void onPause() {
        super.onPause();
        if(javaCameraView!=null)
            javaCameraView.disableView();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        if(javaCameraView!=null)
            javaCameraView.disableView();
    }

    @Override
    protected void onResume() {
        super.onResume();
        if (OpenCVLoader.initDebug()) {
            Log.i(TAG, "Opencv is working properly");
            mLoaderCallback.onManagerConnected(LoaderCallbackInterface.SUCCESS);
        }
        else {
            Log.i(TAG, "Opencv is being an idiot, and a fool and a salaud");
            OpenCVLoader.initAsync(OpenCVLoader.OPENCV_VERSION_3_2_0,this,mLoaderCallback);
        }
    }

    @Override
    public void onCameraViewStarted(int width, int height) {
        mRgba = new Mat(height,width, CvType.CV_8UC4);
    }

    @Override
    public void onCameraViewStopped() {
        mRgba.release();
    }

    @Override
    public Mat onCameraFrame(CameraBridgeViewBase.CvCameraViewFrame inputFrame) {

        System.out.println("New Frameeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee");
        mRgba = inputFrame.rgba();
        try
        {
            String path = getFilesDir().getAbsolutePath();
            System.out.println(path);

            mRgba= faceDetection("/storage/emulated/0/assets/haarcascade_frontalface_alt2.xml", mRgba.getNativeObjAddr());
            mRgba= faceDetection("/storage/emulated/0/assets/haarcascade_eye_tree_eyeglasses.xml", mRgba.getNativeObjAddr());
        }
        catch(Exception E)
        {
            System.out.println("File error ----------------------------");
        }

        System.out.println("End Frameeeeeeeeeeeeeeeeeeeeeeeee");
        return mRgba;
    }


}
