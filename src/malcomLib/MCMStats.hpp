/*
 * MCMStats.hpp
 *
 *  Created on: 14/01/2013
 *      Author: amiranda
 */

#ifndef MCMSTATS_HPP_
#define MCMSTATS_HPP_

#include <QObject>
#include <QDateTime>
#include <QHash>
#include <QVariantList>
#include <qt4/QtNetwork/QNetworkAccessManager>

class MCMStats: public QObject {

	Q_OBJECT

public:
	static MCMStats *Instance();
	void initAndStartBeacon();
	void endBeacon();
	void setTags(QVariantList tags);
protected:
	MCMStats();
	MCMStats(const MCMStats & );
	virtual ~MCMStats();
	MCMStats &operator= (const MCMStats & ) ;

private slots:
	void sendBeaconFinished(QNetworkReply* reply);

	signals:
	void sendBeaconnResult(bool registrationSuccess,
			QString resultMessage = "");
private:
	static MCMStats *pinstance;
	QString started_on;
	QString stopped_on;
	QHash<QString, QString> jsonHash;
	QNetworkAccessManager networkAccessManager;
	QNetworkRequest generateBasicNetworkRequestObject();
	QString tagsToString();

};

#endif /* MCMSTATS_HPP_ */
