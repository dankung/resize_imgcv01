#pragma once

#include <drogon/HttpController.h>
#include "image_converter.h"

using namespace drogon;

struct ImageSrc{
    std::string input_jpeg;
    int target_width;
    int target_height;
	//bool bjson;
};

namespace drogon
{
	template <>
	inline ImageSrc fromRequest(const HttpRequest &req)
	{
		auto json = req.getJsonObject();
		//LOG_DEBUG << "ImageSrc fromRequest get his information";
		
		ImageSrc imgSrc;
		if(json)
		{
			//imgSrc.bjson = true;
			if(!(*json)["input_jpeg"].isNull())
			{
				imgSrc.input_jpeg = (*json)["input_jpeg"].asString();

			} else
				imgSrc.input_jpeg = "";
				//imgSrc.bjson = false;								// json false
			
			if(!(*json)["target_width"].isNull())
			{
				imgSrc.target_width = (*json)["target_width"].asInt();

			} else
				imgSrc.input_jpeg = "";
				// imgSrc.bjson = false;								// json false
			
			if(!(*json)["target_height"].isNull())
			{
				imgSrc.target_height = (*json)["target_height"].asInt();

			} else
				imgSrc.input_jpeg = "";
				// imgSrc.bjson = false;								// json false
			

		}
		return imgSrc;
	}
}

class Resize_Image : public drogon::HttpController<Resize_Image>
{
  public:
    METHOD_LIST_BEGIN
    // use METHOD_ADD to add your custom processing function here;
    // METHOD_ADD(TaskcvController::get, "/{2}/{1}", Get); // path is /TaskcvController/{arg2}/{arg1}
    // METHOD_ADD(TaskcvController::your_method_name, "/{1}/{2}/list", Get); // path is /TaskcvController/{arg1}/{arg2}/list
    // ADD_METHOD_TO(TaskcvController::your_method_name, "/absolute/path/{1}/{2}/list", Get); // path is /absolute/path/{arg1}/{arg2}/list
		// METHOD_ADD(Resize_Image::login,"/token?userId={1}&passwd={2}",Post);		//				---> sudah bisa resize image dari base64		
		// METHOD_ADD(Resize_Image::getInfo,"/{1}/info?token={2}",Get);
		METHOD_ADD(Resize_Image::resize_image,"/",Post);
    METHOD_LIST_END
    // your declaration of processing function maybe like this:
    // void get(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int p1, std::string p2);
    // void your_method_name(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, double p1, int p2) const;
    /*		
             void login(const HttpRequestPtr &req,
				   std::function<void (const HttpResponsePtr &)> &&callback,
				   std::string &&userId,
				   const std::string &password
				   //, ImageSrc &&pImageSrc 
				   );
		void getInfo(const HttpRequestPtr &req,
					 std::function<void (const HttpResponsePtr &)> &&callback,
					 std::string userId,
					 const std::string &token) const;
     */ 
		void resize_image(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 ImageSrc &&pImageSrc) const;	
};
