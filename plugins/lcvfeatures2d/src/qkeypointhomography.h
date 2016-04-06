#ifndef QKEYPOINTHOMOGRAPHY_H
#define QKEYPOINTHOMOGRAPHY_H

#include "qmatdisplay.h"
#include "qkeypointtoscenemap.h"
#include "qlcvfeatures2dglobal.h"

class Q_LCVFEATURES2D_EXPORT QKeypointHomography : public QMatDisplay{

    Q_OBJECT
    Q_PROPERTY(QKeyPointToSceneMap* keypointsToScene READ keypointsToScene WRITE setKeypointsToScene NOTIFY keypointsToSceneChanged)
    Q_PROPERTY(QMat* queryImage                      READ queryImage       WRITE setQueryImage       NOTIFY queryImageChanged)
    Q_PROPERTY(QVariantList objectCorners            READ objectCorners    WRITE setObjectCorners    NOTIFY objectCornersChanged)

public:
    QKeypointHomography(QQuickItem* parent = 0);
    ~QKeypointHomography();

    QKeyPointToSceneMap* keypointsToScene() const;
    void setKeypointsToScene(QKeyPointToSceneMap* arg);

    QMat* queryImage() const;
    QVariantList objectCorners() const;

public slots:
    void setQueryImage(QMat* queryImage);
    void setObjectCorners(QVariantList arg);
    void appendObjectCorners(QVariantList corner);

protected:
    virtual QSGNode *updatePaintNode(QSGNode *node, UpdatePaintNodeData *nodeData);

signals:
    void keypointsToSceneChanged();
    void queryImageChanged();
    void objectCornersChanged();

private:
    QKeyPointToSceneMap* m_keypointsToScene;
    QMat*                m_queryImage;
    QVariantList         m_objectCorners;
};

inline QKeyPointToSceneMap *QKeypointHomography::keypointsToScene() const{
    return m_keypointsToScene;
}

inline void QKeypointHomography::setKeypointsToScene(QKeyPointToSceneMap *arg){
    m_keypointsToScene = arg;
    emit keypointsToSceneChanged();
    update();
}

inline QMat *QKeypointHomography::queryImage() const{
    return m_queryImage;
}

inline QVariantList QKeypointHomography::objectCorners() const{
    return m_objectCorners;
}

inline void QKeypointHomography::setQueryImage(QMat *queryImage){
    if ( queryImage == 0 )
        return;

    cv::Mat* matData = queryImage->cvMat();
    if ( implicitWidth() != matData->cols || implicitHeight() != matData->rows ){
        setImplicitWidth(matData->cols);
        setImplicitHeight(matData->rows);
    }

    m_queryImage = queryImage;
    emit queryImageChanged();
    update();
}

inline void QKeypointHomography::setObjectCorners(QVariantList arg){
    m_objectCorners = arg;
    emit objectCornersChanged();
    update();
}

inline void QKeypointHomography::appendObjectCorners(QVariantList corner){
    m_objectCorners.append(QVariant::fromValue(corner));
    emit objectCornersChanged();
    update();
}

#endif // QKEYPOINTHOMOGRAPHY_H