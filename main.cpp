#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void imgProc(Mat& desMat, string imgPath, string imgPathChild) //�����ԭͼ·������ԭͼ·��
{
    /*
        TM_SQDIFF           //ƽ����ƥ��
        TM_SQDIFF_NORMED
        TM_CCORR            //����ƥ��
        TM_CCORR_NORMED
        TM_CCOEFF           //���ƥ��
        TM_CCOEFF_NORMED
    */
    int METHOD = TM_CCOEFF;                 //ʹ�����ƥ���㷨�����ǰ����ƥ�侫׼������
    Mat imgSrc = imread(imgPath);           //��ԭͼ
    Mat imgTmp = imread(imgPathChild);      //��ƥ����ͼ
              
    Mat imgRes;        //�ȽϽ����ӳ��ͼ��
    Mat imgDisplay;    //�����ͼƬ
    imgSrc.copyTo(imgDisplay);
    int rescols = imgSrc.cols - imgTmp.cols + 1; //imgRes�ĳߴ�
    int resrows = imgSrc.rows - imgTmp.rows + 1;
    imgRes.create(rescols, resrows, CV_32FC1);          //�����������ľ���32λ������ͼ��
    matchTemplate(imgSrc, imgTmp, imgRes, METHOD);      //����ƥ��
    normalize(imgRes, imgRes, 0, 1, NORM_MINMAX, -1, Mat());//���б�׼��
    double minVal;
    double maxVal;
    Point minLoc;
    Point maxLoc;
    Point matchLoc;
    minMaxLoc(imgRes, &minVal, &maxVal, &minLoc, &maxLoc, Mat());//ͨ������ minMaxLoc ��λ��ƥ���λ��
    //���ڷ��� SQDIFF �� SQDIFF_NORMED, ԽС����ֵ������ߵ�ƥ����. ��������������, ��ֵԽ��ƥ��Խ��
    if (METHOD == TM_SQDIFF || METHOD == TM_SQDIFF_NORMED) {
        matchLoc = minLoc;
    }
    else {
        matchLoc = maxLoc;
    }
    //���ƾ���
    rectangle(imgDisplay, matchLoc, Point(matchLoc.x + imgTmp.cols, matchLoc.y + imgTmp.rows), Scalar(0,255,255), 2, 8, 0);
   // rectangle(imgRes, matchLoc, Point(matchLoc.x + imgTmp.cols, matchLoc.y + imgTmp.rows), Scalar::all(0), 2, 8, 0);
    desMat = imgDisplay;
}

int main(int argc, char** argv) {
    string imgPath = "C:/Users/lenovo/Pictures/examMid/WeldingProcessImage/t_3.jpg";        //ԭͼ·��
    string imgPathChild = "C:/Users/lenovo/Pictures/examMid/1.png";                         //ƥ����ͼ·��
    Mat des; //������ͼƬ
    imgProc(des, imgPath, imgPathChild); //ƥ��ɽ�
    namedWindow("���봰��", WINDOW_FREERATIO); //��������
	imshow("���봰��", des);
    string stuNum = "114514";
    string nameIndex = imgPath.substr(imgPath.length() - 5, 1);
    string desPath = "C:/Users/lenovo/Pictures/examMid/WeldingProcessImageDetectionResults/"+ stuNum + "_" + nameIndex + ".png"; //���洦����ͼƬ
    imwrite(desPath, des);

	waitKey(0); 
	destroyAllWindows();
	return 0;
}