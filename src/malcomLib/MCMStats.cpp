/*
 * MCMStats.cpp
 *
 *  Created on: 15/01/2013
 *      Author: amiranda
 */

#include "MCMStats.hpp"
#include "utils.hpp"
#include "MCMJson.hpp"
#include <bb/cascades/Application>
#include <bb/device/HardwareInfo>
#include <qt4/QtNetwork/QNetworkRequest>
#include <qt4/QtNetwork/QNetworkReply>
#include <QLocale>

using namespace bb::cascades;

MCMStats* MCMStats::pinstance = 0;
MCMStats* MCMStats::Instance () {
  if (pinstance == 0) {
    pinstance = new MCMStats;
  }
  return pinstance;
}
MCMStats::MCMStats() {

}

MCMStats::~MCMStats() {


}

//	Public Methods

void MCMStats::initAndStartBeacon() {

	started_on = QString::number(QDateTime().currentMSecsSinceEpoch());
	Utils::log("initAndStartBeacon: "+started_on);

}
void MCMStats::endBeacon() {

	stopped_on = QString::number(QDateTime().currentMSecsSinceEpoch());
	Utils::log("start_on: "+started_on);
	Utils::log("stop_on: "+stopped_on);

	QSettings settings;

	jsonHash["started_on"] = started_on;
	jsonHash["stopped_on"] = stopped_on;
	jsonHash["udid"] = Utils::uniqueDeviceIdentifier();
	jsonHash["device_platform"] = "BB";
	jsonHash["application_code"] = settings.value("malcom_uuid").toString();
	jsonHash["device_model"] = Utils::modelDevice();
	jsonHash["device_os"] = "Blackberry10";
	jsonHash["app_version"] = "1.0";
	jsonHash["language"] = QLocale::system().name().mid(0, 2);
	jsonHash["country"] = QLocale::system().name().mid(3, 4);
	jsonHash["tags"] = tagsToString();

	//Utils::log("Milisegundos: "+start.setNum(started_on.currentMSecsSinceEpoch()));

	QString json = MCMJson::fromHashToString(jsonHash);

	Utils::log(MCMJson::fromHashToString(jsonHash));

	disconnect(&networkAccessManager, 0, 0, 0);
	connect(&networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(sendBeaconFinished(QNetworkReply*)));

	QNetworkRequest networkRequest = generateBasicNetworkRequestObject();
	networkRequest.setRawHeader("Content-Type", "application/json");
	//json = "{\"beacon\":{\"app_version\":1,\"application_code\":\"com.yourcompany.FCBarcelona\",\"device_model\":\"i386\",\"device_os\":3,\"device_platform\":\"iOS\",\"city\":\"barcelona\",\"tags\":[\"tag1\",\"tag2\",\"tag3\"],\"location\":{\"accuracy\":0,\"latitude\":41.389939,\"longitude\":2.177603,\"timestamp\":\"2009-09-18T14:49:29.500+02:00\"},\"started_on\":1.253278154054249E9,\"stopped_on\":1.253278169438035E9,\"subbeacons\":[{\"name\":\"categoria uno\",\"started_on\":0.22,\"stopped_on\":0.33},{\"name\":\"categoria dos\",\"started_on\":0.22,\"stopped_on\":0.33},{\"name\":\"categoria tres\",\"started_on\":0.22,\"stopped_on\":0.33},{\"name\":\"categoria cuatro\",\"started_on\":0.22,\"stopped_on\":0.33}],\"udid\":\"7AA06235-E805-542B-8410-7DABA1726018\"}}";
	networkAccessManager.post(networkRequest, json.toUtf8());

}

void MCMStats::setTags(QVariantList tags) {

	QSettings settings;

	settings.setValue("MCM_TAGS", tags);

}

//	Private Methods

QNetworkRequest MCMStats::generateBasicNetworkRequestObject() {

	QNetworkRequest networkRequest;
	QSettings settings;

	QString url(settings.value("malcom_url_api").toString() + "v1/beacon");

	networkRequest.setUrl(url);

	QString json = MCMJson::fromHashToString(jsonHash);
	QString md5 = Utils::md5(json);
	QString malcomDate = QDateTime().currentDateTime().toUTC().toString("ddd, dd MMM yyyy HH:mm:ss ")+ "UTC";
	QString paswd = "POST\n" +
					md5 + "\n" +
			 		"application/json\n" +
			 		"\n" +
			 		"x-mcm-date:"+malcomDate+"\n"+
			 		"/v1/beacon";

	paswd = Utils::hmac_sha1(paswd, settings.value("malcom_secret_key").toString());

	QString login = QString("%1:%2").arg(settings.value("malcom_uuid").toString()).arg(paswd);
	QByteArray encoded = login.toAscii().toBase64();

	networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	networkRequest.setRawHeader("Authorization", "basic " + encoded);
	networkRequest.setRawHeader("content-md5", ""+md5.toUtf8());
	networkRequest.setRawHeader("x-mcm-date", malcomDate.toUtf8());

	return networkRequest;
}

QString MCMStats::tagsToString() {

	QSettings settings;
	QList<QVariant> tags = settings.value("MCM_TAGS").toList();
	QString tagsString = "[";

	for (int i =0; i < tags.size(); i++) {

		QVariant v = tags.at(i);

		QString vString = v.toString();

		tagsString.append("\"");
		tagsString.append(vString);
		tagsString.append("\"");

		if (i != tags.size() - 1) {

			tagsString.append(",");

		}

	}

	tagsString.append("]");

	return tagsString;

}

//	Delegate Methods

void MCMStats::sendBeaconFinished(QNetworkReply* reply) {

	QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
	Utils::log(reply->errorString() + " - Error code: "+statusCodeV.toString());

}
