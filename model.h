#ifndef MODEL_H
#define MODEL_H

#include <QAbstractItemModel>
#include <QFileIconProvider>
#include <QIcon>
#include <QVector>

class Model : public QAbstractItemModel
{
    Q_OBJECT
public:
    Model(int rows, int columns, QObject * parent = 0);
    ~Model();

    QModelIndex index(int row, int column, const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &child) const Q_DECL_OVERRIDE;

    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;

    bool hasChildren(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

private:
    struct Node
    {
        Node(Node *parent = 0) : parent(parent), children(0) {}
        ~Node() { delete children; }
        Node *parent;
        QVector<Node> *children;
    };

    Node *node(int row, Node *parent) const;
    Node *parent(Node *child) const;
    int row(Node *node) const;

    QIcon services;
    int rc;
    int cc;
    QVector<Node> *tree;
    QFileIconProvider iconPrivider;

};

#endif // MODEL_H
