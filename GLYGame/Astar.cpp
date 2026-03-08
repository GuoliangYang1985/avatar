// Astar.cpp: implementation of the CAstar class.

#include "stdafx.h"
#include "GLYGame.h"
#include "Astar.h"
#include <cmath>
#include <algorithm>
#include <memory>

using namespace std;

// 对角线移动代价常量
static const double DIAGONAL_COST = sqrt(2.0);
namespace ygl
{
    CAstar::CAstar()
    {
    }

    CAstar::CAstar(ISearchable* pGrid)
        : mGrid(pGrid)
    {
    }

    void CAstar::SetMaxSearchTime(float fTime)
    {
        mMaxSearchTime = fTime;
    }

    void CAstar::Init(ISearchable* pGrid)
    {
        mGrid = pGrid;
    }

    void CAstar::SetAllowDiag(bool bAllowDiag)
    {
        mAllowDiag = bAllowDiag;
    }

    // 获取邻居节点（返回临时 vector，由调用者接收）
    vector<INode*> CAstar::GetNeighbors(INode* n) const
    {
        if (!mGrid) return {};

        int c = n->GetCol();
        int r = n->GetRow();
        int max_c = mGrid->GetCols();
        int max_r = mGrid->GetRows();

        vector<INode*> neighbors;
        neighbors.reserve(mAllowDiag ? 8 : 4);

        // 四个基本方向
        if (c + 1 < max_c) neighbors.push_back(mGrid->GetNode(c + 1, r));
        if (r + 1 < max_r) neighbors.push_back(mGrid->GetNode(c, r + 1));
        if (c - 1 >= 0)    neighbors.push_back(mGrid->GetNode(c - 1, r));
        if (r - 1 >= 0)    neighbors.push_back(mGrid->GetNode(c, r - 1));

        // 对角线方向（如果允许）
        if (mAllowDiag)
        {
            if (c - 1 >= 0 && r + 1 < max_r) neighbors.push_back(mGrid->GetNode(c - 1, r + 1));
            if (c + 1 < max_c && r + 1 < max_r) neighbors.push_back(mGrid->GetNode(c + 1, r + 1));
            if (c - 1 >= 0 && r - 1 >= 0)    neighbors.push_back(mGrid->GetNode(c - 1, r - 1));
            if (c + 1 < max_c && r - 1 >= 0)    neighbors.push_back(mGrid->GetNode(c + 1, r - 1));
        }

        return neighbors;
    }

    bool CAstar::IsInClosed(INode* n) const
    {
        return mClosed.find(n->GetNodeId()) != mClosed.end();
    }

    double CAstar::CalculateHeuristic(INode* a, INode* b) const
    {
        int dx = a->GetCol() - b->GetCol();
        int dy = a->GetRow() - b->GetRow();
        return sqrt(static_cast<double>(dx * dx + dy * dy));
    }

    // 核心 A* 搜索
    CSearchResults CAstar::Search(INode* pStartNode, INode* pGoalNode)
    {
        CSearchResults results;

        if (!mGrid || !pStartNode || !pGoalNode)
            return results;

        // 清空 closed 集
        mClosed.clear();

        // 创建优先队列（使用优化后的 CPriorityQueue，它应支持 unique_ptr）
        CPriorityQueue openSet;

        // 初始路径：包含起始点
        auto startPath = make_unique<CPath>();
        startPath->AddNode(pStartNode);
        openSet.Enqueue(std::move(startPath));

        clock_t startTime = clock();
        bool found = false;
        unique_ptr<CPath> finalPath;

        while (openSet.HasNextItem())
        {
            // 超时检查
            if ((clock() - startTime) > mMaxSearchTime)
                break;

            // 取出当前最优路径
            unique_ptr<CPath> currentPath(openSet.GetNextItem());  // GetNextItem 返回原始指针，需包装为 unique_ptr
            // 注意：GetNextItem 应转移所有权，返回原始指针，这里用 unique_ptr 接管
            // 若原 CPriorityQueue 已改为返回 unique_ptr，则直接 auto currentPath = openSet.GetNextItem();

            INode* lastNode = currentPath->GetLastNode();

            // 如果已在 closed 集中，跳过
            if (IsInClosed(lastNode))
                continue;

            // 到达目标？
            if (lastNode->Equal(pGoalNode))
            {
                found = true;
                finalPath = std::move(currentPath);
                break;
            }

            // 加入 closed 集
            mClosed.insert(lastNode->GetNodeId());

            // 扩展邻居
            vector<INode*> neighbors = GetNeighbors(lastNode);
            for (INode* neighbor : neighbors)
            {
                if (!neighbor) continue;

                // 计算从当前路径到邻居的代价
                double stepCost = 1.0;
                // 对角线代价
                if (neighbor->GetCol() != lastNode->GetCol() && neighbor->GetRow() != lastNode->GetRow())
                    stepCost = DIAGONAL_COST;

                // 乘以移动代价系数（来自地形等）
                stepCost *= mGrid->GetNodeTransitionCost(lastNode, neighbor);

                // 创建新路径 = 当前路径 + 邻居
                auto newPath = currentPath->Clone();  // Clone 应返回原始指针，需用 unique_ptr 管理
                newPath->AddNode(neighbor);
                newPath->IncrementCost(stepCost);

                // 计算启发值
                double h = CalculateHeuristic(neighbor, pGoalNode);
                neighbor->SetHeuristic(h);

                // 入队
                openSet.Enqueue(std::move(newPath));
            }
        }

        // 设置结果
        if (found && finalPath)
        {
            results.SetIsSuccess(true);
            results.SetPath(finalPath.release());  // 转移所有权给 results（假设它负责删除）
        }

        return results;
    }
}