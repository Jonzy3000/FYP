#pragma once
#include "CalibrationOptions.h"
#include <QtNetwork>
#include <QUrl>
#include <qmessagebox.h>

class HttpPostRequests : public QObject {
	Q_OBJECT
public:
	HttpPostRequests(const std::shared_ptr<CalibrationOptions> & pCalibrationOptions, QObject *parent = Q_NULLPTR) :
		pCalibrationOptions(pCalibrationOptions)
	{
		auto serverSettings = pCalibrationOptions->getServerConfig();
		url.setScheme("http");
		url.setHost(QString::fromStdString(serverSettings->ipAddress));
		url.setPort(serverSettings->portNumber);

		QObject::connect(pNetworkManager.get(), SIGNAL(finished(QNetworkReply*)),
			this, SLOT(replyFinished(QNetworkReply*)));
	}

	void newRoom(std::string name, int maxOccupancy) {
		const QString apiPath = "/fypApi/counter/newRoom";
		url.setPath(apiPath, QUrl::DecodedMode);
		QUrlQuery query = QUrlQuery();
		query.addQueryItem("name", QString::fromStdString(name));
		query.addQueryItem("maxOccupancy", QString::fromStdString(std::to_string(maxOccupancy)));
		genericPost(query);
	}

	void updateCounter(std::string name, int incrementBy) {
		const QString apiPath = "/fypApi/counter/updateCounter";
		url.setPath(apiPath, QUrl::DecodedMode);
		QUrlQuery query = QUrlQuery();
		query.addQueryItem("name", QString::fromStdString(name));
		query.addQueryItem("incrementBy", QString::fromStdString(std::to_string(incrementBy)));
		genericPost(query);
	}

private:
	void replyFinished(QNetworkReply* pReply) {
		qDebug() << "HELLO";
		QMessageBox::information(nullptr, "HELLO", "REPLY FINISHED");
		pReply->deleteLater();
	}

	void slotError(QNetworkReply::NetworkError error) {
		QMessageBox::warning(nullptr, tr("Network Error"), tr("Something went wrong sending data to server"));
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
	std::shared_ptr<QNetworkAccessManager> pNetworkManager = std::make_shared<QNetworkAccessManager>();
};
