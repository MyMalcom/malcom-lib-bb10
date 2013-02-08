/*
 * MCMNotification.hpp
 *
 *  Created on: 22/01/2013
 *      Author: amiranda
 */

#ifndef MCMNOTIFICATION_HPP_
#define MCMNOTIFICATION_HPP_

#include <QObject>
#include <bb/network/PushService>
#include <bb/network/PushStatus>
#include <bb/system/InvokeManager>
#include <bb/platform/Notification>

using namespace bb::network;
using namespace bb::platform;
using namespace bb::system;

class MCMNotification : public QObject {

	Q_OBJECT

	public:
		static MCMNotification *Instance();
		void registerDevice();

	public slots:
		void handleInvoke(const bb::system::InvokeRequest&);
		void createSessionCompleted(const bb::network::PushStatus&);
		void createChannelCompleted(const bb::network::PushStatus &status, const QString &token);
		void destroyChannelCompleted(const bb::network::PushStatus &status);
		void registerToLaunchCompleted(const bb::network::PushStatus &status);
		void unregisterFromLaunchCompleted(const bb::network::PushStatus &status);

		void registerFinished(QNetworkReply* reply);

	protected:
		MCMNotification();
		MCMNotification(const MCMNotification & );
		virtual ~MCMNotification();
		MCMNotification &operator= (const MCMNotification & );

	private:
		static MCMNotification *pinstance;
		PushService *m_pushService;
		InvokeManager m_invokeManager;
		Notification notification;
		QObject *m_createPushSessionStatus;
		QObject *m_createPushChannelStatus;
		QObject *m_registertoLaunchStatus;
		void connectPushServices();
		void registerDeviceMalcom(QString environment);
		QNetworkRequest generateBasicNetworkRequestObject();
		QHash<QString, QString> jsonHash;
		QNetworkAccessManager networkAccessManager;

};


#endif /* MCMNOTIFICATION_HPP_ */
