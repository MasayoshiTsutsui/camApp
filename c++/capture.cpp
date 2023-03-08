#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>

int main() {
    cv::CascadeClassifier face_cascade;
    face_cascade.load("../../haarcascade_frontalface_alt.xml");

    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Could not open camera" << std::endl;
        return -1;
    }

    while (true) {
        cv::Mat frame;
        cap >> frame;
        if (frame.empty()) {
            break;
        }

        // 顔の検出
        std::vector<cv::Rect> faces;
        face_cascade.detectMultiScale(frame, faces, 1.3, 5);

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