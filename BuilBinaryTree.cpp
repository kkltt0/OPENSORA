#include "BuilBinaryTree.h"
#include "readdata.h"
#include "contourdata.h"
#include "topotree.h"
#include "treenode.h"

// 构造函数
BuildBinTopoTree::BuildBinTopoTree(std::vector<std::pair<double, QPolygonF> > &iAllPolygonData)
	: m_allPolygonData(iAllPolygonData)
	, m_topologyBinaryTree(nullptr)
{
}

BuildBinTopoTree::~BuildBinTopoTree()
{
	if (m_topologyBinaryTree != nullptr)
	{
		delete m_topologyBinaryTree;
		m_topologyBinaryTree = nullptr;
	}

	if (!m_preorderContourVec.empty())
	{
		m_preorderContourVec.clear();
	}
}

// 拓扑二叉树建立的函数
void BuildBinTopoTree::makeTopologyBinaryTree()
{

	if (m_topologyBinaryTree != nullptr)
	{
		delete m_topologyBinaryTree;
		m_topologyBinaryTree = nullptr;
	}

	//**************************************
	// 创建并初始化根节点
	//**************************************
	int contour_id = 1;

	ReadData *readFileData = new ReadData();
	readFileData->readContourData();
	//readFileData->GetAllContourData();
	double m_minX = readFileData->getMinX();
	double m_maxX = readFileData->getMaxX();
	double m_minY = readFileData->getMinY();
	double m_maxY = readFileData->getMaxY();
	delete readFileData;

	double rootX[] = { m_maxX, m_minX, m_minX, m_maxX, m_maxX };
	double rootY[] = { m_minY, m_minY, m_maxY, m_maxY, m_minY };
	
	QPolygonF rootArrayData;
	for (int i = 0; i < 5; i++)
	{
		rootArrayData.append(QPointF(rootX[i], rootY[i]));
	}

	const int root_node_size = rootArrayData.size();
	int rootID = 0;
	double root_value = 0;

	ContourData * rootData = new ContourData(rootID, root_value, rootArrayData);
	TreeNode *root = new TreeNode(rootData, nullptr, nullptr, nullptr);
	m_topologyBinaryTree = new TopologyTree(root);
	//出错判断
	if (0 == m_allPolygonData.size())
	{
		return;
	}

	//遍历所有等值线数据,并建立二叉树
	for (int i = 0; i < m_allPolygonData.size(); i++)
	{
		double contourValue = m_allPolygonData[i].first;
		ContourData * treenodedata = new ContourData(contour_id, contourValue, m_allPolygonData[i].second);
		m_topologyBinaryTree->insert(treenodedata);
		++contour_id;
	}
}

//先序遍历二叉树
void BuildBinTopoTree::preoderTopologyBinaryTree(TreeNode *node)
{
	if (node != nullptr)
	{
		m_preorderContourVec.push_back(node);
		preoderTopologyBinaryTree(node->getMyLeftChild());
		preoderTopologyBinaryTree(node->getMyRightChild());
	}
}

//// 获取先根遍历好的二叉树的函数
//void BuildBinTopoTree::make_preorder_contour_list()
//{
//	if(!preorder_contour_list.empty())
//	{
//		make_topo_binary_tree();
//		if( topo_binary_tree != nullptr )
//		{
//			preorder_topo_binary_tree(topo_binary_tree->GetMyRoot());
//		}
//	}
//}

//获取先跟遍历好的二叉树
std::vector<TreeNode *> BuildBinTopoTree::getPreorderContourTree() const
{
	return m_preorderContourVec;
}
