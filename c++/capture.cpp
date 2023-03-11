#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <boost/version.hpp>
#include <boost/timer/timer.hpp>


int main() {
    cv::CascadeClassifier face_cascade;
    // opencv's path may be different in your env.
    // Most articles say opencv is in /usr/local/Cellar/opencv
    face_cascade.load("/opt/homebrew/Cellar/opencv/4.7.0_2/share/opencv4/haarcascades/haarcascade_eye_tree_eyeglasses.xml");

    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Could not open camera" << std::endl;
        return -1;
    }

    boost::timer::cpu_timer timer;

    int maxItr = 10;

    for (size_t i = 0; i < maxItr; i++)
    {
        cv::Mat frame;

        timer.start();
        cap >> frame;
        timer.stop();

        if (frame.empty()) {
            break;
        }

        std::cout << "Get Frame : " << timer.format() << std::endl;

        // 顔の検出
        std::vector<cv::Rect> faces;

        timer.start();
        face_cascade.detectMultiScale(frame, faces, 1.3, 5);
        timer.stop();

        std::cout << "Detect Face : " << timer.format() << std::endl;

        // 検出された顔に四角形を描画
        for (const auto& face : faces) {
            cv::rectangle(frame, face, cv::Scalar(0, 0, 255), 2);
        }

        // 結果の表示
        cv::imshow("Face detection", frame);

        // 終了するためのキー操作
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }
    return 0;
}