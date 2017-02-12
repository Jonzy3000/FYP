#pragma once
#include <cpprest/http_client.h>


using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

class HttpPostRequests {
public:

	HttpPostRequests() {

	}

	void newRoom(std::string name, int maxOccupancy) {
		auto request = L"name=" + conversions::to_string_t(name) + L"&maxOccupancy=" + conversions::to_string_t(std::to_string(maxOccupancy));
		uri_builder builder(U("newRoom"));
		genericPost(builder, request);
	}

	void updateCounter(std::string name, int incrementBy) {
		auto request = L"name=" + conversions::to_string_t(name) + L"&incrementBy=" + conversions::to_string_t(std::to_string(incrementBy));
		uri_builder builder(U("updateCounter"));
		genericPost(builder, request);
	}

private:
	const uri ROUTING_ADDRESS = U("http://localhost:8080/fypApi/counter/");

	void genericPost(uri_builder query, string_t req) {
		http_client client(ROUTING_ADDRESS);
		http_request request(methods::POST);
		request.headers().set_content_type(L"application/x-www-form-urlencoded");
		request.set_body(req);
		request.set_request_uri(query.to_uri());

		client.request(request).then([=](http_response response) {
			auto x = response.status_code();
			std::cout << x << std::endl;
		});
	}
};