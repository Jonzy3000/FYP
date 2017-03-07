#pragma once
#include "CalibrationOptions.h"
#include <QtNetwork>
#include <QUrl>
#include <qmessagebox.h>


/*
TODO move this into main exec thread
then emit signal from CountManager to do these*/
class HttpPostRequests : public QObject {
	Q_OBJECT
public:
	HttpPostRequests(QObject *parent, const std::shared_ptr<CalibrationOptions> & pCalibrationOptions) :
		pCalibrationOptions(pCalibrationOptions), QObject(parent)
	{
		QMetaObject::invokeMethod(this, "init", Qt::QueuedConnection);

		pNetworkManager = new QNetworkAccessManager(this);
		QObject::connect(pNetworkManager, &QNetworkAccessManager::finished, this, &HttpPostRequests::replyFinished);

		auto serverSettings = pCalibrationOptions->getServerConfig();
		url.setScheme("http");
		url.setHost(QString::fromStdString(serverSettings->ipAddress));
		url.setPort(serverSettings->portNumber);
	}

	void newRoom() {
		std::string name = pCalibrationOptions->getRoomConfig()->roomName;
		int maxOccupancy = pCalibrationOptions->getRoomConfig()->maxOccupancy;
		const QString apiPath = "/fypApi/counter/newRoom";
		url.setPath(apiPath, QUrl::DecodedMode);
		QUrlQuery query = QUrlQuery();
		query.addQueryItem("name", QString::fromStdString(name));
		query.addQueryItem("maxOccupancy", QString::fromStdString(std::to_string(maxOccupancy)));
		genericPost(query);
	}

	void updateCounter(int incrementBy) {
		std::string name = pCalibrationOptions->getRoomConfig()->roomName;
		const QString apiPath = "/fypApi/counter/updateCounter";
		url.setPath(apiPath, QUrl::DecodedMode);
		QUrlQuery query = QUrlQuery();
		query.addQueryItem("name", QString::fromStdString(name));
		query.addQueryItem("incrementBy", QString::fromStdString(std::to_string(incrementBy)));
		genericPost(query);
	}

private:
	void sslErrors(QNetworkReply* pReply, const QList<QSslError> &errors) {
		QMessageBox::information(nullptr, "Errors", "First error " + errors.at(0).errorString());
	}


	void replyFinished(QNetworkReply* pReply) {
		pReply->deleteLater();

	}

	void slotError(QNetworkReply::NetworkError error) {
		QMessageBox::information(nullptr, "HELLO", "error");
	}

	void genericPost(QUrlQuery postData) {
		QString host = url.host();
		int port = url.port();
		auto path = url.path();
		auto urlStr = url.toDisplayString();
		
		if (url.isValid()) {
			QNetworkRequest request(url);
			request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

			pNetworkManager->post(request, postData.toString(QUrl::FullyEncoded).toUtf8());
		}
	}


	QUrl url;
	std::shared_ptr<CalibrationOptions> pCalibrationOptions;
	QString ip;
	QString port;
	QNetworkAccessManager* pNetworkManager;
};
