/*
 * MCMNotification.cpp
 *
 *  Created on: 22/01/2013
 *      Author: amiranda
 */

#include "MCMNotification.hpp"
#include "Utils.hpp"
#include <bb/network/PushPayload>
#include <bb/cascades/Application>
#include <bb/network/PushErrorCode>
#include <bb/system/InvokeRequest>
#include <bb/network/PushStatus>
#include "MCMJson.hpp"

using namespace bb::cascades;
using namespace bb::system;

MCMNotification* MCMNotification::pinstance = 0;
MCMNotification* MCMNotification::Instance () {
  if (pinstance == 0) {
    pinstance = new MCMNotification;
  }
  return pinstance;
}
MCMNotification::MCMNotification() : m_invokeManager(new InvokeManager(this)) {

}

MCMNotification::~MCMNotification() {


}

//	Public methods

void MCMNotification::registerDevice () {

	Utils::log("registerDevice");
	registerDeviceMalcom("SANDBOX");
	// If our application gets invoked (via a Push or otherwiser) this section will
	// call our handleInvoke method with the InvokeRequest data
	// If our application gets invoked (via a Push or otherwiser) this section will
		// call our handleInvoke method with the InvokeRequest data
	connect(&m_invokeManager, SIGNAL(invoked(const bb::system::InvokeRequest&)),
				this, SLOT(handleInvoke(const bb::system::InvokeRequest&)));
	m_pushService = new PushService("3436-59445eB83r704866oor7D81i256er8431e5","com.malcom.client.sample");
	connectPushServices();
	m_pushService->createSession();

}

//	Private Methods

void MCMNotification::registerDeviceMalcom(QString environment) {

	QSettings settings;

	jsonHash["applicationCode"] = settings.value("malcom_uuid").toString();
	jsonHash["environment"] = environment;
	jsonHash["token"] = "hayquecambiarlo";
	jsonHash["udid"] = Utils::uniqueDeviceIdentifier();
	jsonHash["devicePlatform"] = "BB";

	QString json = MCMJson::fromHashToString(jsonHash, "NotificationRegistration");

	Utils::log(MCMJson::fromHashToString(jsonHash, "NotificationRegistration"));

	disconnect(&networkAccessManager, 0, 0, 0);
	connect(&networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(registerFinished(QNetworkReply*)));

	QNetworkRequest networkRequest = generateBasicNetworkRequestObject();
	networkRequest.setRawHeader("Content-Type", "application/json");
	networkAccessManager.post(networkRequest, json.toUtf8());

}

QNetworkRequest MCMNotification::generateBasicNetworkRequestObject() {

	QNetworkRequest networkRequest;
	QSettings settings;

	QString url(settings.value("malcom_url_api").toString() + "v3/notification/registry/application");
	Utils::log("URL: "+url);
	networkRequest.setUrl(url);

	QString json = MCMJson::fromHashToString(jsonHash, "NotificationRegistration");
	QString md5 = Utils::md5(json);
	QString malcomDate = QDateTime().currentDateTime().toUTC().toString("ddd, dd MMM yyyy HH:mm:ss ")+ "UTC";
	QString paswd = "POST\n" +
					md5 + "\n" +
			 		"application/json\n" +
			 		"\n" +
			 		"x-mcm-date:"+malcomDate+"\n"+
			 		"/v3/notification/registry/application";

	paswd = Utils::hmac_sha1(paswd, settings.value("malcom_secret_key").toString());

	QString login = QString("%1:%2").arg(settings.value("malcom_uuid").toString()).arg(paswd);
	QByteArray encoded = login.toAscii().toBase64();

	networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	networkRequest.setRawHeader("Authorization", "basic " + encoded);
	networkRequest.setRawHeader("content-md5", ""+md5.toUtf8());
	networkRequest.setRawHeader("x-mcm-date", malcomDate.toUtf8());

	return networkRequest;
}

// This section connects the various signals emitted by PushServices to slots
// in this class
void MCMNotification::connectPushServices() {
	connect(m_pushService,
			SIGNAL(createSessionCompleted(const bb::network::PushStatus&)),
			this, SLOT(createSessionCompleted(const bb::network::PushStatus&)));

	connect(m_pushService,
			SIGNAL(createChannelCompleted(const bb::network::PushStatus&,
							const QString &)), this,
			SLOT(createChannelCompleted(const bb::network::PushStatus&,
							const QString &)));

	connect(m_pushService,
			SIGNAL(destroyChannelCompleted(const bb::network::PushStatus&)),
			this, SLOT(
					destroyChannelCompleted(const bb::network::PushStatus&)));

	connect(m_pushService,
			SIGNAL(registerToLaunchCompleted(const bb::network::PushStatus &)),
			this,
			SLOT(registerToLaunchCompleted(const bb::network::PushStatus&)));

	connect(m_pushService,
			SIGNAL(unregisterFromLaunchCompleted(const bb::network::PushStatus &)),
			this, SLOT(unregisterFromLaunchCompleted(
							const bb::network::PushStatus&)));
}

//	SLOTS

void MCMNotification::handleInvoke(const InvokeRequest &request) {

	Utils::log("Invocation received");

	// In this case we don't care about the invocation unless it is of type Push
	if (request.action().compare("bb.action.PUSH") != 0) {
		return;
	}
	PushPayload payload(request);
	if (payload.isValid()) {
		if (payload.isAckRequired()) {
			m_pushService->acceptPush(payload.id());
		}
		Utils::log("<html><em><b>Push Received</b></em><br/>Payload: <br/> " + payload.data() + "</html>");
		//notification -> notify();
	}
}

void MCMNotification::createSessionCompleted(const bb::network::PushStatus &status) {
	if (!status.isError()) {
		Utils::log("Successfully created session");
		QMetaObject::invokeMethod(m_createPushSessionStatus, "setState", Q_ARG(QVariant, true));
	} else {
		Utils::log("Failed to create session: " + status.errorDescription());
		QMetaObject::invokeMethod(m_createPushSessionStatus, "setState", Q_ARG(QVariant, false));
	}
}

void MCMNotification::createChannelCompleted(const PushStatus &status, const QString &token) {
	if (!status.isError() && m_pushService) {
		QMetaObject::invokeMethod(m_createPushChannelStatus, "setState", Q_ARG(QVariant, true));
		Utils::log("Successfully created channel");
		m_pushService->registerToLaunch();

		Utils::log("Registering with Malcom: "+token);
		//m_urbanAirshipAPI.setToken(token);
		//m_urbanAirshipAPI.urbanAirshipRegisterPIN(); <-- SE REGISTRA EN MALCOM
	} else {
		QMetaObject::invokeMethod(m_createPushChannelStatus, "setState", Q_ARG(QVariant, false));
		Utils::log("Failed to create channel: " + status.errorDescription());
		//m_logger->setText("Failed to create channel: " + status.errorDescription());
	}
}

void MCMNotification::destroyChannelCompleted(const PushStatus &status) {
	if (!status.isError()) {
		QMetaObject::invokeMethod(m_createPushChannelStatus, "setState", Q_ARG(QVariant, false));
		Utils::log("Unregistering from launch");
		m_pushService->unregisterFromLaunch();
		Utils::log("Unregistering with Malcom");
		//m_urbanAirshipAPI.urbanAirshipUnRegisterPIN(); <------SE DESREGISTRA DE MALCOM
	} else {
		Utils::log("Failed to destroy channel: " + status.errorDescription());
	}
}

void MCMNotification::registerToLaunchCompleted(const bb::network::PushStatus &status) {
	if (!status.isError()) {
		QMetaObject::invokeMethod(m_registertoLaunchStatus, "setState", Q_ARG(QVariant, true));
		Utils::log("Register to launch completed successfully");
	} else {
		QMetaObject::invokeMethod(m_registertoLaunchStatus, "setState", Q_ARG(QVariant, false));
		Utils::log("Failed to register to launch: " + status.errorDescription());
	}
}

void MCMNotification::unregisterFromLaunchCompleted(const bb::network::PushStatus &status) {
	if (!status.isError()) {
		QMetaObject::invokeMethod(m_registertoLaunchStatus, "setState", Q_ARG(QVariant, false));
		Utils::log("Unregister to launch completed successfully");
	} else {
		Utils::log("Failed to unregister to launch: " + status.errorDescription());
	}
}

void MCMNotification::registerFinished(QNetworkReply* reply) {

	QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
	Utils::log(reply->errorString() + " - Error code: "+statusCodeV.toString());

}


