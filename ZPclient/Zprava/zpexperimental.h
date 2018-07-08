#ifndef ZPEXPERIMENTAL_H
#define ZPEXPERIMENTAL_H

#include <QWidget>
#include <QVBoxLayout>

class ZpExperimental : public QWidget
{
    Q_OBJECT
public:
    explicit ZpExperimental(QWidget *parent = 0);
    QVBoxLayout* exp;

signals:

public slots:
};

#endif // ZPEXPERIMENTAL_H
