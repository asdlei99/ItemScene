#ifndef PGE_EDIT_SCENE_ITEM_H
#define PGE_EDIT_SCENE_ITEM_H

#include <cmath>
#include <type_traits>
#include "pge_rect.h"
#include "pge_quad_tree.h"

#include <QTransform>

class QPainter;
class PGE_EditScene;
class PGE_EditSceneItem
{
    friend class PGE_EditScene;
    PGE_EditScene *m_scene = nullptr;
    PGE_EditSceneItem *m_parent = nullptr;
    bool m_selected = false;
    PgeQuadTree m_childrenTree;
    QTransform m_transform;

public:
    explicit PGE_EditSceneItem(PGE_EditScene *parent);
    PGE_EditSceneItem(const PGE_EditSceneItem &it);
    virtual ~PGE_EditSceneItem();

    void setSelected(bool selected);
    bool selected() const;

    void addChild(PGE_EditSceneItem *item);

    bool isTouching(int64_t x, int64_t y) const;
    bool isTouching(const QRect &rect) const;
    bool isTouching(const QRectF &rect) const;
    bool isTouching(const PGE_Rect<int64_t> &rect) const;

    /* Relative position (to parent) */
    int64_t x() const;
    int64_t y() const;
    int64_t w() const;
    int64_t h() const;

    int64_t left() const;
    int64_t top() const;
    int64_t right() const;
    int64_t bottom() const;

    /* Absolute position (dig through all parents and compute the real position) */
    int64_t x_abs() const;
    int64_t y_abs() const;
    int64_t w_abs() const;
    int64_t h_abs() const;

    int64_t left_abs() const;
    int64_t top_abs() const;
    int64_t right_abs() const;
    int64_t bottom_abs() const;

    void queryChildren(PGE_Rect<int64_t> &zone, PgeQuadTree::t_resultCallback a_resultCallback, void *context) const;

    virtual void paint(QPainter *painter, const QPointF &camera = QPoint(0, 0),
                       const double &zoom = 1.0);

    PGE_Rect<int64_t> m_posRect;
};

#endif // PGE_EDIT_SCENE_ITEM_H
