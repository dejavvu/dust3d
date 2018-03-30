#include <QPen>
#include "skeletoneditedgeitem.h"
#include "theme.h"

SkeletonEditEdgeItem::SkeletonEditEdgeItem(QGraphicsItem *parent) :
    QGraphicsLineItem(parent),
    m_firstNode(NULL),
    m_secondNode(NULL)
{
    setData(0, "edge");
    m_checked = false;
    updateAppearance();
}

void SkeletonEditEdgeItem::setChecked(bool checked)
{
    if (m_checked == checked) {
        return;
    }
    m_checked = checked;
    updateAppearance();
}

bool SkeletonEditEdgeItem::checked()
{
    return m_checked;
}

void SkeletonEditEdgeItem::updateAppearance()
{
    QPen pen;
    if (m_firstNode) {
        QColor color = m_firstNode->sideColor();
        color.setAlphaF(Theme::edgeAlpha);
        pen.setColor(color);
    } else if (m_secondNode) {
        QColor color = m_secondNode->sideColor();
        color.setAlphaF(Theme::edgeAlpha);
        pen.setColor(color);
    }
    pen.setWidth(Theme::skeletonEdgeWidth);
    setPen(pen);
}

void SkeletonEditEdgeItem::setNodes(SkeletonEditNodeItem *first, SkeletonEditNodeItem *second)
{
    m_firstNode = first;
    m_secondNode = second;
    updatePosition();
}

bool SkeletonEditEdgeItem::connects(SkeletonEditNodeItem *nodeItem)
{
    return m_firstNode == nodeItem || m_secondNode == nodeItem;
}

void SkeletonEditEdgeItem::updatePosition()
{
    if (m_firstNode && m_secondNode) {
        QLineF line(m_firstNode->origin(), m_secondNode->origin());
        setLine(line);
    }
    updateAppearance();
}

SkeletonEditNodeItem *SkeletonEditEdgeItem::firstNode()
{
    return m_firstNode;
}

SkeletonEditNodeItem *SkeletonEditEdgeItem::secondNode()
{
    return m_secondNode;
}