/*
 * utils.hpp
 *
 *  Created on: 10/01/2013
 *      Author: amiranda
 */

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <QObject>
#include <QCryptographicHash>
#include <QDebug>
#include <bb/platform/bbm/Context>

#ifdef __QNXNTO__
#include <bb/device/HardwareInfo>
#endif

class Utils {

public:

	static QString hmac_sha1(const QString &key, const QString &secret) {

		//Length of the text, that will be hashed
		   int   text_lenght;

		   //For secret word.
		   QByteArray K;
		   //Lenght of secret word
		   int   K_lenght;

		   K_lenght = secret.size();
		   text_lenght = key.size();

		   //Need to do for XOR operation. Transforms QString to
		   //unsigned char


		   K = secret.toUtf8();

		   //Inner padding
		   QByteArray ipad;
		   //Outer pad
		   QByteArray opad;

		   //if secret key > 64 bytes use this to obtain sha1 key
		   if(K_lenght > 64)
		   {
		      QByteArray tempSecret;

		      tempSecret.append(secret);

		      K = QCryptographicHash::hash(tempSecret,
		                                  QCryptographicHash::Sha1);

		      K_lenght = 20;
		   }

		   //Fills ipad and opad with zeros
		   //bzero( ipad, sizeof ipad);
		   //bzero( opad, sizeof opad);

		   ipad.fill( 0, 64);
		   opad.fill(0, 64);

		   //Copies Secret to ipad and opad
		   //bcopy( K, ipad, K_lenght);
		   //bcopy( K, opad, K_lenght);

		   ipad.replace(0, K_lenght, K);
		   opad.replace(0, K_lenght, K);



		   //XOR operation for inner and outer pad
		   for (int i=0; i<64; i++)
		   {
		      ipad[i] = ipad[i] ^ 0x36;
		      opad[i] = opad[i] ^ 0x5c;
		   }

		   //Stores hashed content
		   QByteArray context;

		   //Appends XOR:ed ipad to context
		   context.append(ipad,64);
		   //Appends key to context
		   context.append(key);

		   //Hashes Inner pad
		   QByteArray Sha1   = QCryptographicHash::hash(context,
		                                                QCryptographicHash::Sha1);

		   context.clear();
		   //Appends opad to context
		   context.append(opad,64);
		   //Appends hashed inner pad to context
		   context.append(Sha1);

		   Sha1.clear();

		   // Hashes outerpad
		   Sha1 = QCryptographicHash::hash(context,
		                                   QCryptographicHash::Sha1);

		   // String to return hashed stuff in Base64 format
		   QByteArray str(Sha1.toBase64());

		   return str;

	};

	static QString md5(const QString &data) {

		QByteArray encodedPass = QCryptographicHash::hash((data.toUtf8().constData()),QCryptographicHash::Md5);

		//return encodedPass.toHex().toBase64();

		QString r = "hola que tal";

		return encodedPass.toBase64();

	};

	static void log(const QString text) {

		qDebug() << text;

	};

	static QString uniqueDeviceIdentifier()
	{
	#ifdef __QNXNTO__
	  bb::device::HardwareInfo hwid;
	  return hashString(hwid.serialNumber());
	#else
	  QSettings settings;
	  QString deviceId = settings.value(QLatin1String("DEVICE_ID")).toString();
	  if (deviceId.isEmpty())
	  {
		  deviceId = randomUUID();
		  settings.setValue(QLatin1String("DEVICE_ID"), deviceId);
		  settings.sync();
	  }
	  return hashString(deviceId);
	#endif
	};

	static QString hashString(QString input)
	{
	  QByteArray stringBytes = input.toUtf8();
	  QByteArray digest = QCryptographicHash::hash(stringBytes, QCryptographicHash::Sha1);
	  return QString::fromAscii(digest.toHex());
	};

	static QString modelDevice() {

		QString model = "";

		#ifdef __QNXNTO__
			  bb::device::HardwareInfo hwid;
			  model = hwid.modelName();
		#endif

		return model;

	};

};


#endif /* UTILS_HPP_ */
