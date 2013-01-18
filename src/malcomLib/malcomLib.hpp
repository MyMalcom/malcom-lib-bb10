/*
 * malcomLib.hpp
 *
 *  Created on: 10/01/2013
 *      Author: amiranda
 */

#ifndef MALCOMLIB_HPP_
#define MALCOMLIB_HPP_

#include <QObject>
#include <QVariantList>

class MalcomLib : public QObject {

	Q_OBJECT
	Q_PROPERTY(QString version READ version)
	Q_PROPERTY(QString urlApi READ urlApi)

public:

	static MalcomLib *Instance();
	void initMalcom(QString uuid, QString secretKey);
	QString version();
	QString urlApi();

	//	Stats module

	void initAndStartBeacon();
	void endBeacon();
	void setTags(QVariantList tags);

protected:
	MalcomLib();
	MalcomLib(const MalcomLib &);
	virtual ~MalcomLib();

private:

	QString m_version;
	QString m_url_api;
	static MalcomLib *pinstance;
	static const QString MALCOM_URL_API;
	static const QString MALCOM_UUID;
	static const QString MALCOM_SECRET_KEY;

};


#endif /* MALCOMLIB_HPP_ */
