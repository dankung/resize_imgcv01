#define DROGON_TEST_MAIN
#include <drogon/drogon_test.h>
#include <drogon/drogon.h>
#include <fstream>
#include <memory>
#include "../controllers/image_converter.h"
#include "../controllers/TaskController.h"

DROGON_TEST(BasicTest)
{
    // Add your tests here
}

DROGON_TEST(RemoteAPITest)
{
   auto client = HttpClient::newHttpClient("http://localhost:8080");
   //auto req = HttpRequest::newHttpRequest();
   //auto req = HttpRequest::
   std::string all_headers;
   std::string imgbase64;
   int desired_width;
   int desired_height;

   //req->setPath("/resize_image/");
   std::ifstream is ("encode1.bin", std::ifstream::binary);
   REQUIRE( is.is_open());
   // if (is) 
   // {
        is.seekg (0, is.end);
        int length = is.tellg();
        is.seekg (0, is.beg);

        std::unique_ptr<char[]> buffer{new char [length]}; // note: use char[] as parameter
        is.read (buffer.get(), length);
        // cout << buffer.get() << endl;
        imgbase64 = buffer.get();
        desired_width = 300;
        desired_height = 200;

        Json::Value ret;        
         
	ret["desired_height"]=desired_height;		
        ret["desired_width"]= desired_width;
        ret["input_jpeg"]=imgbase64;
        
        
       auto req  =  HttpRequest::newCustomHttpRequest(ret);
       req->setPath("/resize_image/");  
       req->setMethod(Post);
 
       // LOG_DEBUG << " isi json= " << req->getBody() << " end";             
       // LOG_DEBUG << " isi client host= " << client->getHost() << " end";     

       client->sendRequest(req, [TEST_CTX](ReqResult res, const HttpResponsePtr& resp) {

                REQUIRE(res == ReqResult::Ok);
       		REQUIRE(resp != nullptr);
		
       		CHECK(resp->getStatusCode() == k200OK);
       		CHECK(resp->contentType() == CT_APPLICATION_JSON);
   	});
   //}
     
     
}

int main(int argc, char** argv) 
{
    using namespace drogon;

    std::promise<void> p1;
    std::future<void> f1 = p1.get_future();

    // Start the main loop on another thread
    std::thread thr([&]() {
        // Queues the promise to be fulfilled after starting the loop
        app().getLoop()->queueInLoop([&p1]() { p1.set_value(); });
        app().run();
    });

    // The future is only satisfied after the event loop started
    f1.get();
    int status = test::run(argc, argv);

    // Ask the event loop to shutdown and wait
    app().getLoop()->queueInLoop([]() { app().quit(); });
    thr.join();
    return status;
}
