#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

void showImage() {
  Mat image = cv::imread("test.png", IMREAD_GRAYSCALE);
  if (image.empty()) {
    std::cerr << "Image not found\n";
  }

  const string window_name("test");
  namedWindow(window_name);
  imshow(window_name, image);
  waitKey(0);
}

int main() {
  
  double scale = 1.0;

  CascadeClassifier faceCascade;
  bool loaded = faceCascade.load("/Users/matteofusilli/Apps/opencv_example/haarcascade_frontalface_alt.xml");
  if (!loaded) cerr << "Could not load faceCascade model";

  VideoCapture cap(0);
  if (!cap.isOpened()) 
    return -1;

  for (;;) {
    Mat frame;
    cap >> frame;

    Mat grayscale;
    cvtColor(frame, grayscale, COLOR_BGR2GRAY);
    resize(grayscale, grayscale, Size(grayscale.size().width / scale, grayscale.size().height / scale));
    
    vector<Rect> faces;
    faceCascade.detectMultiScale(grayscale, faces, 1.1, 3, 0, Size(30, 30));

    for (Rect area: faces) {
      Scalar drawColor = Scalar(0, 0, 255);
      rectangle(frame, Point(cvRound(area.x * scale), cvRound(area.y * scale)),
        Point(cvRound((area.x + area.width -1) * scale), cvRound((area.y + area.height - 1) * scale)), drawColor);
    }

    imshow("Webcam frame", frame);

    if (waitKey(30) >= 0)
      break;
  }
  return 0;
}