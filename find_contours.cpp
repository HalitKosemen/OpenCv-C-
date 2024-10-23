/* �ncelikle herhangi bir foto�rafta contours(�ekil) bulma yap�caz. 
   Hakk�nda A��klama : �ncelik ile 2 kolay fonksiyonumuz var findcontours ve drawcontours
                       ve 2 farkl� algotirma var CHAIN_APPROX_SIMPLE VE CHAIN_APPROX_NONE
                       fotoyu grayscale �evirmek thresholding i�in gerekli bir i�lem , resmi 
                       resmi grayscale �evirdikten sonra 2 i�lemden birini yapabiliriz ya thresholding
                       yada canny edge detect . thresholding image siyah ve beyaz yap�yor,
                       thresholding yap�nca beyaz nesneleri tespit edebiliyoruz.siyah pikseller
                       de�eri 0 olur ve arka plan pikseli olarak alg�lan�p g�z arda edilir.
                       thresholdingten sonra findcontours() fonksiyonu kullan�l�r. findcontours tan sonra
                       baz� uygulamalarda daha y�ksek hassasiyetli contourslar laz�m bu durumlarda
                       farkl� thresholdlar deneyerek bulunabilir.
                       
   Takip Edilmesi Gereken Ad�mlar 1-)read the image and convert it to grayscale format
                                  2-)apply binary thresholding 
                                  3-)find the contours
                                  4-)draw contours
                                  threshold(girdi,��kt�,e�ik_degeri,255or0,THRESH_BINARY)
                                  findContours(girdi,mode,method)
                                  drawContours(girdi,findcontours_girdisi,istenilen_contours_�izme_-1_hepsini_�izer,renk,kal�nl�k)
                                  */

#include <iostream>
#include<opencv2/opencv.hpp>
#include <opencv2/core/utils/logger.hpp>
#include <opencv2/imgproc.hpp>

int main() {

    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);

    cv::Mat image = cv::imread("images.jpeg");

    cv::Mat image_gray;

    cv::cvtColor(image, image_gray, cv::COLOR_BGR2GRAY);

    cv::Mat image_thresh;
    cv::threshold(image_gray, image_thresh, 222, 255, cv::THRESH_BINARY);
    cv::imshow("binary mage", image_thresh);

    std::vector<std::vector<cv::Point>> contours;  /*std::vector<T> dinamik diziler olu�turmak i�in kullan�l�r(dinamik = de�i�ebilen)
                                                    yani bu kodda her kontor birs�r� nokta i�erir ve bu noktalar�n veya contourlar�n tamam�
                                                    bu vekt�rde saklan�r */

    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(image_thresh, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);

    cv::Mat image_copy = image.clone();
    cv::drawContours(image_copy, contours, -1, cv::Scalar(0, 255, 0), 1);
    cv::imshow("image_gg", image_copy);

    std::vector<std::vector<cv::Point>> contours1;
    std::vector<cv::Vec4i> hierarchy1;
    cv::findContours(image_thresh, contours1, hierarchy1, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE); // simple ile none aras�ndaki fark simple da vertical and horizontal straight tamamem ignorlan�yo sadece k��elerinden bi nokta at�yo
    cv::Mat image_copy_1 = image.clone();
    cv::drawContours(image_copy_1, contours1, -1, cv::Scalar(0, 0, 255), 1);
    cv::imshow("image_gg_1", image_copy_1);

                                                
    cv::waitKey(0);
    cv::destroyAllWindows();


    return 0;

}