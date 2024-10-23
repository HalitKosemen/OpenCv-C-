/* öncelikle herhangi bir fotoðrafta contours(þekil) bulma yapýcaz. 
   Hakkýnda Açýklama : öncelik ile 2 kolay fonksiyonumuz var findcontours ve drawcontours
                       ve 2 farklý algotirma var CHAIN_APPROX_SIMPLE VE CHAIN_APPROX_NONE
                       fotoyu grayscale çevirmek thresholding için gerekli bir iþlem , resmi 
                       resmi grayscale çevirdikten sonra 2 iþlemden birini yapabiliriz ya thresholding
                       yada canny edge detect . thresholding image siyah ve beyaz yapýyor,
                       thresholding yapýnca beyaz nesneleri tespit edebiliyoruz.siyah pikseller
                       deðeri 0 olur ve arka plan pikseli olarak algýlanýp göz arda edilir.
                       thresholdingten sonra findcontours() fonksiyonu kullanýlýr. findcontours tan sonra
                       bazý uygulamalarda daha yüksek hassasiyetli contourslar lazým bu durumlarda
                       farklý thresholdlar deneyerek bulunabilir.
                       
   Takip Edilmesi Gereken Adýmlar 1-)read the image and convert it to grayscale format
                                  2-)apply binary thresholding 
                                  3-)find the contours
                                  4-)draw contours
                                  threshold(girdi,çýktý,eþik_degeri,255or0,THRESH_BINARY)
                                  findContours(girdi,mode,method)
                                  drawContours(girdi,findcontours_girdisi,istenilen_contours_çizme_-1_hepsini_çizer,renk,kalýnlýk)
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

    std::vector<std::vector<cv::Point>> contours;  /*std::vector<T> dinamik diziler oluþturmak için kullanýlýr(dinamik = deðiþebilen)
                                                    yani bu kodda her kontor birsürü nokta içerir ve bu noktalarýn veya contourlarýn tamamý
                                                    bu vektörde saklanýr */

    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(image_thresh, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);

    cv::Mat image_copy = image.clone();
    cv::drawContours(image_copy, contours, -1, cv::Scalar(0, 255, 0), 1);
    cv::imshow("image_gg", image_copy);

    std::vector<std::vector<cv::Point>> contours1;
    std::vector<cv::Vec4i> hierarchy1;
    cv::findContours(image_thresh, contours1, hierarchy1, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE); // simple ile none arasýndaki fark simple da vertical and horizontal straight tamamem ignorlanýyo sadece köþelerinden bi nokta atýyo
    cv::Mat image_copy_1 = image.clone();
    cv::drawContours(image_copy_1, contours1, -1, cv::Scalar(0, 0, 255), 1);
    cv::imshow("image_gg_1", image_copy_1);

                                                
    cv::waitKey(0);
    cv::destroyAllWindows();


    return 0;

}