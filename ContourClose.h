#pragma once

#include <vector>
#include <map>
#include <qpolygon.h>

/******************���νṹ********************
        A _____________ D
		 |             |
		 |             |
		 |             | 
		 |_____________|
        B               C
*********************************************/
struct Rectangle
{
	QPointF rectPointA;
	QPointF rectPointB;
	QPointF rectPointC;
	QPointF rectPointD;
};

class ContourClose
{
public:
	ContourClose();
	~ContourClose();

	// �Ե�ֵ�����ݽ���Ԥ����
	void preprocessContourData();
	void closeContour();//��յ�ֵ��
	double getDistance(std::pair<int, QPointF> crossPoint);//����δ��յ�ֵ�߶˵㵽�߽�����ͼ����ľ���
	bool isPointOnLine(QPointF tPoint, QPointF sPoint, QPointF ePoint);//�жϵ��Ƿ���ֱ����
	double calculateTwoPointDistance(QPointF point1, QPointF point2);//������֮��ľ���
	std::vector<std::pair<double, QPolygonF>> getClosedContourData();//��ȡ�¹���ıպϵ�ֵ������

	void quickSort(std::vector<std::pair<int, double>> allDistVec, int l, int r);
	bool isTheSamePoint(QPointF p1, QPointF p2);
	int getIndexInAllCrossedPointsSortedByDist(QPointF point);
	QPointF getAnotherEndPointOnContour(int contourId, QPointF point);
	int getPointIndexInContour(int contourId, QPointF point);
	Rectangle getRectange() const;

private:
	std::vector<std::pair<double, QPolygonF>> m_allContourData;//ԭʼ��ֵ������
	std::vector<std::pair<int, QPointF>> m_allCrossPoints;//δ��յ�ֵ����߽��ߵĽ�������
	std::vector<std::pair<double, QPolygonF>> m_allClosedContourData;//���еıպϵ�ֵ������
	std::vector<std::tuple<double, int, QPointF>> m_allCrossedPointsSortedByDist;

	double m_minX = 0.0;//��Сxֵ
	double m_minY = 0.0;//��Сyֵ
	double m_maxX = 0.0;//���xֵ
	double m_maxY = 0.0;//���yֵ

	Rectangle m_rect;
};