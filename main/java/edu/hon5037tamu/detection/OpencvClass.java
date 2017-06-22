package edu.hon5037tamu.detection;

import org.opencv.core.Mat;

/**
 * Created by Hermann on 5/25/2017.
 */
public class OpencvClass {
    public native static Mat faceDetection(String filename, long addrRgba);
}
