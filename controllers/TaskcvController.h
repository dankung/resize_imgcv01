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
			
			if(!(*json)["input_jpeg"].isNull())
			{
				imgSrc.input_jpeg = (*json)["input_jpeg"].asString();

			} else
				imgSrc.input_jpeg = "";
			
			
			if(!(*json)["target_width"].isNull())
			{
				imgSrc.target_width = (*json)["target_width"].asInt();

			} else
				imgSrc.input_jpeg = "";
				
			
			if(!(*json)["target_height"].isNull())
			{
				imgSrc.target_height = (*json)["target_height"].asInt();

			} else
				imgSrc.input_jpeg = "";
				
			

		}
		else
			imgSrc.input_jpeg = "";
		return imgSrc;
	}
}

class Resize_Image : public drogon::HttpController<Resize_Image>
{
  public:
    METHOD_LIST_BEGIN
		METHOD_ADD(Resize_Image::resize_image,"/",Post);
    METHOD_LIST_END

		void resize_image(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 ImageSrc &&pImageSrc) const;	
};
