#ifndef LAYOUTWIDGET_HPP
#define LAYOUTWIDGET_HPP

#include <QWidget>
#include <QLayout>

class LayoutWidget : public QWidget
{
    Q_OBJECT
    QLayout *layout;

public:
    LayoutWidget(Qt::Orientation orientation) : QWidget(){
        if (orientation == Qt::Vertical)
            layout = new QVBoxLayout();
        else if (orientation == Qt::Horizontal)
            layout = new QHBoxLayout();

        setLayout(layout);
        layout->setSpacing(0);
        layout->setContentsMargins(0, 0, 0, 0);
    }

    void addWidget(QWidget * widget){
        layout->addWidget(widget);
    }
};

#endif // LAYOUTWIDGET_HPP
