#include "knetstats.h"

// KDE headers
#include <kapp.h>
#include <kpopupmenu.h>
#include <kmessagebox.h>
#include <kaboutapplication.h>
#include <kconfig.h>
#include <kglobal.h>
#include <kstandarddirs.h>

#include <kaction.h>
#include <kstdaccel.h>
#include <kstdaction.h>
#include <khelpmenu.h>
#include <kpassivepopup.h>

// Qt headers
#include <qtimer.h>
#include <qfile.h>
#include <qtooltip.h>
#include <qcursor.h>
#include <qevent.h>

// C headers
#include <cstring>
#include <cstdio>

#include "configure.h"
#include "statistics.h"

#include <iostream>

extern const char* programName;

KNetStats::KNetStats():mBRx(0), mBTx(0), mPRx(0), mPTx(0), mTotalBytesRx(0), mTotalBytesTx(0), mTotalPktRx(0), mTotalPktTx(0), mSpeedRx(0), mSpeedTx(0), mbConnected(true), mTextMode(false)
{
	setTextFormat(Qt::PlainText);

	// Load icons
	mIconBoth = loadIcon("icon_both.png");
	mIconRx = loadIcon("icon_rx.png");
	mIconTx = loadIcon("icon_tx.png");
	mIconNone = loadIcon("icon_none.png");
	mIconError = loadIcon("icon_error.png");
	mCurrentIcon = &mIconNone;

	// Context menu
	KPopupMenu* menu = contextMenu();

	KAction* configure = KStdAction::preferences(this, SLOT(configure()), actionCollection(), "configure");
	configure->plug(menu);

	menu->insertItem( i18n("&Statistics"), this, SLOT(statistics()) );

	menu->insertSeparator();
	KHelpMenu* helpmenu = new KHelpMenu(this, QString::null, false);
	menu->insertItem( i18n("&Help"), helpmenu->menu() );
	connect(helpmenu, SIGNAL(showAboutApplication()), this, SLOT(about()));

	// Load config
	KConfig cfg(KGlobal::dirs()->localkdedir()+"/share/config/knetstatsrc", true);
	mUpdateInterval = cfg.readNumEntry("UpdateInterval", 300);
	mInterface = cfg.readEntry("Interface");
	if (!mInterface.isEmpty())
		QToolTip::add(this, i18n("Monitoring ")+mInterface);
	mTextMode = cfg.readBoolEntry("TextMode", false);

	// Quit signal
	connect(this, SIGNAL(quitSelected()), kapp, SLOT(quit(void)));

	// Timer
	mTimer = new QTimer(this, "timer");
	connect(mTimer, SIGNAL(timeout()), this, SLOT(update(void)));

	if (mTextMode)
	{
		update();
		setText("0B\n0B");
		mSpeedTx = mSpeedRx = 0;
		mTimer->start(1000);
	}
	else
	{
		setPixmap(*mCurrentIcon);
		mTimer->start(mUpdateInterval);
	}
}

void KNetStats::update()
{
	if (mInterface.isEmpty())
	{
		mTimer->stop();
		setPixmap( loadIcon("icon_configure.png") );
		if (KMessageBox::warningYesNo(this, "KNetstats appear to be not configured, do you want configure it now?") == KMessageBox::Yes)
			configure();
		return;
	}
	// Read and parse /proc/net/dev
	FILE* fp = fopen("/proc/net/dev", "r");
	if (!fp)
	{
		mTimer->stop();
		KMessageBox::error(this, "Error opening /proc/net/dev!");
		return;
	}

	unsigned int brx, btx, prx, ptx;
	char interface[8];
	char buffer[128];

	// skip headers (why not a fseek() ?)
	fgets(buffer, sizeof(buffer), fp);
	fgets(buffer, sizeof(buffer), fp);

	bool linkok = false;
	while(fgets(buffer, sizeof(buffer), fp))
	{
		// Read statistics
		sscanf(buffer, " %[^ \t\r\n:]%*c%u%u%*u%*u%*u%*u%*u%*u%u%u%*u%*u%*u%*u%*u%*u", interface, &brx, &prx, &btx, &ptx);

		if (interface == mInterface)
		{
			QPixmap* newIcon;

			// Calcula as velocidade
			if (mTextMode)
			{
				mSpeedTx = (btx - mBTx);
				mSpeedRx = (brx - mBRx);
				mSpeedPTx = (ptx - mPTx);
				mSpeedPRx = (prx - mPRx);
			}
			else
			{
				mSpeedTx = ((btx - mBTx)*(1000.0f/mUpdateInterval));
				mSpeedRx = ((brx - mBRx)*(1000.0f/mUpdateInterval));
				mSpeedPTx = ((ptx - mPTx)*(1000.0f/mUpdateInterval));
				mSpeedPRx = ((prx - mPRx)*(1000.0f/mUpdateInterval));
			}
// DEBUG
std::cout << "Diff: " << (btx - mBTx) << std::endl;
std::cout << "Interval: " << mUpdateInterval << std::endl;
std::cout << "Speed: " << mSpeedTx << std::endl;
std::cout << "-------------------------------\n";

			if (mTextMode)
			{
				setText(Statistics::byteFormat(mSpeedTx, 1, "", "KB", "MB")+"\n"+Statistics::byteFormat(mSpeedRx, 1, "", "KB", "MB"));
			}
			else
			{
				if (brx == mBRx)
				{
					if (btx == mBTx )
						newIcon = &mIconNone;
					else
						newIcon = &mIconTx;
				}
				else
				{
					if (btx == mBTx )
						newIcon = &mIconRx;
					else
						newIcon = &mIconBoth;
				}

				if (newIcon != mCurrentIcon)
				{
					mCurrentIcon = newIcon;
					setPixmap(*mCurrentIcon);
				}
			}

			// Update stats
			mTotalBytesRx += brx - mBRx;
			mTotalBytesTx += btx - mBTx;
			mTotalPktRx += prx - mPRx;
			mTotalPktTx += ptx - mPTx;

			mBRx = brx;
			mBTx = btx;
			mPRx = prx;
			mPTx = ptx;

			if (!mbConnected)
			{
				mbConnected = true;
				KPassivePopup::message(programName, i18n("%1 is active").arg(mInterface), mIconBoth, this);
			}
			linkok = true;
			break;
		}
	}

	fclose(fp);

	if (!linkok && mbConnected)
	{
		mbConnected = false;
		mCurrentIcon = &mIconError;
		setPixmap(*mCurrentIcon);
		KPassivePopup::message(programName, i18n("%1 is inactive").arg(mInterface), mIconError, this);
	}

}

QStringList KNetStats::searchInterfaces()
{
	FILE* fp = fopen("/proc/net/dev", "r");

	QStringList list;

	if (!fp)
		return list;
	char interface[8];
	char buffer[128];

	// Ignore header...
	fgets(buffer, sizeof(buffer), fp);
	fgets(buffer, sizeof(buffer), fp);
	while(fgets(buffer, sizeof(buffer), fp))
	{
		sscanf(buffer, " %[^ \t\r\n:]", interface);
		list.append(interface);
	}
	return list;
}

void KNetStats::configure()
{
	Configure dlg(this);
	int res = dlg.exec();
	if (res == QDialog::Accepted)
	{
		QString newInterface = dlg.interface();
		mUpdateInterval = dlg.updateInterval();
		mTextMode = (dlg.viewMode() == Configure::TextMode);
		mbConnected = true;

		KConfig cfg(KGlobal::dirs()->localkdedir()+"/share/config/knetstatsrc");
		mInterface = newInterface;
		cfg.writeEntry("UpdateInterval", mUpdateInterval);
		cfg.writeEntry("Interface", mInterface);
		cfg.writeEntry("TextMode", mTextMode);

		if (!mTextMode)	// Update icon, if we changed to icon mode from textmode
		{
			mCurrentIcon = &mIconNone;
			setPixmap(mIconNone);
			mTimer->changeInterval(mUpdateInterval);
		}
		else
			mTimer->changeInterval(1000);

		if (newInterface != mInterface)
		{
			mTotalBytesRx = mTotalBytesTx = mTotalPktRx = mTotalPktTx = 0;
			mBRx = mBTx = mPRx = mPTx = 0;
			mSpeedRx = mSpeedTx = mSpeedPRx = mSpeedPTx = 0;
			QToolTip::add(this, i18n("Monitoring ")+mInterface);
			KPassivePopup::message(programName, i18n("Now monitoring %1").arg(mInterface), mIconTx, this);
		}
	}
}

void KNetStats::mousePressEvent(QMouseEvent* ev)
{
	if (ev->button() == Qt::RightButton )
		contextMenu()->exec(QCursor::pos());
	else if (ev->button() == Qt::LeftButton)
		statistics();
}

void KNetStats::about()
{
	KAboutApplication dlg(this);
	dlg.exec();
}

void KNetStats::statistics()
{
	if (mInterface.isEmpty())
		configure();
	else
	{
		Statistics dlg(this);
		dlg.exec();
	}
}
