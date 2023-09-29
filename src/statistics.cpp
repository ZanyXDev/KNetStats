#include "statistics.h"
#include "chart.h"
#include "knetstatsview.h"
#include <QNetworkInterface>
#include <QTimer>
#include <QMenu>

Statistics::Statistics(KNetStatsView *parent)
		: Ui::StatisticsBase(), mParent(parent) {

	setupUi(this);
	this->setWindowTitle(QString("Monitoring Interface %1 - KNetStats").arg(parent->interface().name()));
	auto *chart = new Chart(parent->speedHistoryTx(), parent->speedHistoryRx(), parent->historyBufferSize(),
							parent->historyPointer(), parent->maxSpeed(),
							parent->getViewOptions());
	mChart->addWidget(chart);
	update();

	mTimer = new QTimer(this);
	connect(tabWidget, &QTabWidget::tabBarClicked, this, &Statistics::updateTabSize);
	connect(mTimer, &QTimer::timeout, this, &Statistics::updateStatistics);
	connect(mTimer, &QTimer::timeout, chart, qOverload<>(&Chart::repaint));
	connect(mOk, &QPushButton::clicked, this, &Statistics::hideWindow);
}

void Statistics::updateStatistics() {
	mMaxSpeed->setText(this->locale().formattedDataSize(*mParent->maxSpeed()) + +"/s");
	mBRx->setText(this->locale().formattedDataSize(mParent->totalBytesRx()));
	mBTx->setText(this->locale().formattedDataSize(mParent->totalBytesTx()));
	mByteSpeedRx->setText(this->locale().formattedDataSize(mParent->byteSpeedRx()) + "/s");
	mByteSpeedTx->setText(this->locale().formattedDataSize(mParent->byteSpeedTx()) + "/s");

	mPRx->setText(QString::number(mParent->totalPktRx()));
	mPTx->setText(QString::number(mParent->totalPktTx()));
	mPktSpeedRx->setText(QString::number(mParent->pktSpeedRx(), 'f', 1) + "pkts/s");
	mPktSpeedTx->setText(QString::number(mParent->pktSpeedTx(), 'f', 1) + "pkts/s");
}

void Statistics::updateTabSize(int tabIndex) {
	for (int i = 0; i < tabWidget->count(); i++) {
		if (i != tabIndex)
			tabWidget->widget(i)->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	}

	tabWidget->widget(tabIndex)->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	tabWidget->widget(tabIndex)->adjustSize();
}

void Statistics::showWindow() {
	// Update details...
	mMTU->setNum(mParent->interface().maximumTransmissionUnit());
	if (mParent->interface().flags() &
		(QNetworkInterface::InterfaceFlag::IsUp | QNetworkInterface::InterfaceFlag::IsRunning)) {
		QString ipStr, netmaskStr;
		for (const QNetworkAddressEntry &addr: mParent->interface().addressEntries()) {
			ipStr += addr.ip().toString() + "\n";
			netmaskStr += addr.netmask().toString() + "\n";
		}
		mIP->setText(ipStr.remove(QRegExp("\\n$")));
		mNetmask->setText(netmaskStr.remove(QRegExp("\\n$")));
	} else {
		mIP->setText("Not Connected");
		mNetmask->setText("Not Connected");
	}
	mMAC->setText(mParent->interface().hardwareAddress());

	mTimer->start(mParent->updateInterval());
	show();
}

void Statistics::hideWindow() {
	mTimer->stop();
	hide();
}
