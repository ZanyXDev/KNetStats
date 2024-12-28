#include "backend.h"

Backend::Backend(QObject *parent)
    : QObject{parent}
    , m_interfaceList(new QStringList())
{

}
