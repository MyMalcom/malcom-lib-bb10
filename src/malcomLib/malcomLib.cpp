/*
 * malcomLib.cpp
 *
 *  Created on: 10/01/2013
 *      Author: amiranda
 */

#include "malcomLib.hpp"
#include <bb/cascades/Application>
#include "utils.hpp"
#include "MCMStats.hpp"

const QString MalcomLib::MALCOM_URL_API =
		"malcom_url_api";
const QString MalcomLib::MALCOM_UUID =
		"malcom_uuid";
const QString MalcomLib::MALCOM_SECRET_KEY =
		"malcom_secret_key";

MalcomLib* MalcomLib::pinstance = 0;
MalcomLib* MalcomLib::Instance () {
  if (pinstance == 0) {
    pinstance = new MalcomLib;
  }
  return pinstance;
}

MalcomLib::MalcomLib() {

	m_version = "1.0.0";

}

MalcomLib::~MalcomLib() {


}

void MalcomLib::initMalcom(QString uuid, QString secretKey) {

	QSettings settings;
	settings.setValue(MALCOM_UUID, uuid);
	settings.setValue(MALCOM_SECRET_KEY, secretKey);
	//settings.setValue(MALCOM_URL_API, "http://api.mymalcom.com/");
	settings.setValue(MALCOM_URL_API, "http://malcom-api-pre.elasticbeanstalk.com/");

	m_url_api = MALCOM_URL_API + uuid + "/" + secretKey;

	//Utils::hmac_sha1("a", "b");
	m_url_api = Utils::hmac_sha1("a", "b");

	QString theJSON = "{\"beacon\":{\"app_version\":1,\"application_code\":\"com.yourcompany.FCBarcelona\",\"device_model\":\"i386\",\"device_os\":3,\"device_platform\":\"iOS\",\"city\":\"barcelona\",\"tags\":[\"tag1\",\"tag2\",\"tag3\"],\"location\":{\"accuracy\":0,\"latitude\":41.389939,\"longitude\":2.177603,\"timestamp\":\"2009-09-18T14:49:29.500+02:00\"},\"started_on\":1.253278154054249E9,\"stopped_on\":1.253278169438035E9,\"subbeacons\":[{\"name\":\"categoria uno\",\"started_on\":0.22,\"stopped_on\":0.33},{\"name\":\"categoria dos\",\"started_on\":0.22,\"stopped_on\":0.33},{\"name\":\"categoria tres\",\"started_on\":0.22,\"stopped_on\":0.33},{\"name\":\"categoria cuatro\",\"started_on\":0.22,\"stopped_on\":0.33}],\"udid\":\"7AA06235-E805-542B-8410-7DABA1726018\"}}";
	QString malcomDate = "";
	QString md5 = Utils::md5(theJSON);

	malcomDate = QDateTime::currentDateTime().toString();

	QString password = "POST\n" +
					md5 + "\n" +
			 		"application/json\n" +
			 		" \n" +
			 		"x-mcm-date:"+malcomDate+"\n"+
			 		"/v1/beacon";

}

QString MalcomLib::version() {

	return m_version;

}

QString MalcomLib::urlApi() {

	return m_url_api;

}

//	Stats module

void MalcomLib::initAndStartBeacon() {

	MCMStats *mcmStats = MCMStats::Instance();
	mcmStats -> initAndStartBeacon();

}

void MalcomLib::endBeacon() {

	MCMStats::Instance() -> endBeacon();

}

void MalcomLib::setTags(QVariantList tags) {

	MCMStats::Instance() -> setTags(tags);

}

