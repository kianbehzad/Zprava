#include "zpexperimental.h"
#include "zpwindow.h"
#include "zpthread.h"

extern ZpUser* WHOAMI;

ZpExperimental::ZpExperimental(QWidget *parent) : QWidget(parent)
{
    WHOAMI = new ZpUser("amirbayat98");
    //create your widget
    ZpWindow* window = new ZpWindow();
    ZpThread* thread = new ZpThread();
    connect(thread, SIGNAL(updated()), window, SLOT(handle_threadUpdate()));
    thread->start();

    exp= new QVBoxLayout(this);
    exp->addWidget(window);
    this->setLayout(exp);
}
