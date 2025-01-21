#include "periodictask.h"

PeriodicTask::PeriodicTask(QObject *parent)
    : QObject{parent}
{
    // Настраиваем таймер для вызова задачи каждые 10 раз в секунду
    m_timer.setInterval(100);
    connect(&m_timer, &QTimer::timeout, this, &PeriodicTask::runTask);
}

void PeriodicTask::start()
{
    if (!m_timer.isActive()) {
        m_timer.start();
#ifdef QT_DEBUG
        qDebug() << "Started periodic task.";
#endif
    }
}

void PeriodicTask::stop() {
    if (m_timer.isActive()) {
        m_timer.stop();
#ifdef QT_DEBUG
        qDebug() << "Stopped periodic task.";
#endif \
        // Ожидание завершения фоновых задач
        if (m_futureWatcher.isRunning()) {
#ifdef QT_DEBUG
            qDebug() << "Waiting for running tasks to complete...";
#endif
            m_futureWatcher.waitForFinished();
#ifdef QT_DEBUG
            qDebug() << "All tasks completed.";
#endif
        }
    }
}

void PeriodicTask::setDeviceList(const QStringList &newDeviceList)
{
    stop();
    // Подготавливаем список задач для асинхронной обработки
    m_deviceList = newDeviceList;
    start();
}

void PeriodicTask::runTask()
{
    // Проверяем, завершена ли предыдущая задача
    if (m_futureWatcher.isRunning()) {
        qDebug() << "Previous task is still running. Will not start a new one.";
        return; // Предыдущая задача еще выполняется, выходим
    }



    // Асинхронно обрабатываем задачи с помощью QtConcurrent::map
    QFuture<void> future = QtConcurrent::map(m_deviceList, [this](const QString& task) {
        return performBackgroundWork(task);
    });

    m_futureWatcher.setFuture(future); // Устанавливаем будущее для наблюдателя
}

void PeriodicTask::performBackgroundWork(const QString &task) {
    // Симуляция тяжелой работы с задержкой
    QThread::sleep(1);

    // Генерируем случайное число
    static std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, 100);
    qDebug()<< "QThread::currentThreadId()" <<QThread::currentThreadId();
    emit taskCompleted(task,true,distribution(generator),distribution(generator),distribution(generator),distribution(generator));
}

