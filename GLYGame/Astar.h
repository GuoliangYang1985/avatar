// Astar.h: interface for the CAstar class.

#pragma once
#include "INode.h"
#include "SearchResults.h"
#include "ISearchable.h"
#include "Path.h"
#include "PriorityQueue.h"
#include <functional>
#include <string>
#include <atlstr.h>
namespace std {
    template<> struct hash<CString>
    {
        size_t operator()(const CString& s) const noexcept
        {
#ifdef _UNICODE
            return std::hash<std::wstring>()(s.GetString());
#else
            return std::hash<std::string>()(s.GetString());
#endif
        }
    };
}
#include <unordered_set>
#include <vector>

class CAstar
{
public:
    CAstar();
    explicit CAstar(ISearchable* pGrid);
    ~CAstar() = default;

    // 禁用拷贝（可根据需要启用移动）
    CAstar(const CAstar&) = delete;
    CAstar& operator=(const CAstar&) = delete;

    void SetMaxSearchTime(float fTime);
    void Init(ISearchable* pGrid);

    /**
     * 使用 A* 算法查找从起始点到目标点的路径。
     * @param pStartNode 起始点
     * @param pGoalNode  目标点
     * @return 寻路结果对象
     */
    CSearchResults Search(INode* pStartNode, INode* pGoalNode);

    void SetAllowDiag(bool bAllowDiag);

private:
    // 获取邻居节点（不分配动态内存，返回临时 vector）
    std::vector<INode*> GetNeighbors(INode* n) const;

    // 检查节点是否在 closed 集中
    bool IsInClosed(INode* n) const;

    // 计算启发值（欧几里得距离）
    double CalculateHeuristic(INode* a, INode* b) const;

private:
    ISearchable* mGrid = nullptr;
    float mMaxSearchTime = 2000.0f;
    bool mAllowDiag = true;

    // 使用 unordered_set 存储已访问节点的 ID
    std::unordered_set<CString> mClosed;
};
