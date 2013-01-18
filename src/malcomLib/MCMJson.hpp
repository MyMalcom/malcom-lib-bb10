/*
 * MCMJson.hpp
 *
 *  Created on: 16/01/2013
 *      Author: amiranda
 */

#ifndef MCMJSON_HPP_
#define MCMJSON_HPP_

#include <QHash>

class MCMJson {

public:
	static QString fromHashToString(QHash<QString, QString> hash) {

		QString jsonString = "{\"beacon\":{";

		QHashIterator<QString, QString> i(hash);

		while (i.hasNext()) {

			i.next();

			jsonString.append("\"");
			jsonString.append(i.key());
			jsonString.append("\"");
			jsonString.append(":");

			if (i.key().compare("tags") != 0) {

				jsonString.append("\"");
				jsonString.append(i.value());
				jsonString.append("\"");

			}
			else {

				jsonString.append(i.value());

			}

			if (i.hasNext()) {

				jsonString = jsonString + ",";

			}

		}

		jsonString = jsonString + "}}";

		return jsonString;

	};

};


#endif /* MCMJSON_HPP_ */
