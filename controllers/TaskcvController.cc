#include "TaskcvController.h"

/*	
	Created by 		: Daniel Agus Listiantoro
	Date Created 	: 5/5/2022
	Description		: Create a simple HTTP server application that listens on port 8080 to serves a
					specific function: resizing a jpeg image, in the form of base 64 encoded binary input data
					to the desired target dimension. The server only needs to serve exactly single API below:
*/

// Add definition of your processing function here
/*
Task 1:
Please create a simple HTTP server application that listens on port 8080 to serves a
specific function: resizing a jpeg image, in the form of base 64 encoded binary input data
to the desired target dimension. The server only needs to serve exactly single API below:

HTTP://[host_address]:8080/resize_image [POST]

Input Payload:
Content-Type: application/json
{
"input_jpeg": "[base 64 encoding of jpeg binary]",
"target_width": [target_width],
"target_height": [target_height]
}

Output Payload:
If success:
HTTP 200
Content-Type: application/json
{
"code": 200,
"message": "success",
"output_jpeg": "[base 64 encoding of output jpeg binary]"
}


If failed:
HTTP 4XX/5XX
Content-Type: application/json
{
"code": 4xx/5xx,
"Message": "[output error description here]"
}
*/

void Resize_Image::resize_image(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 ImageSrc &&pImageSrc) const				 
{
	
	// LOG_DEBUG<<"Resize_Image::resize_image get his information";
	
	Json::Value ret;
	
	auto req1=HttpRequest::newHttpRequest();
	
	int x = pImageSrc.input_jpeg.compare("");
	
	if ( x != 0 )
	{
		// error
		ret["code"]="4xx/5xx";
		ret["message"]="[JSON format error]";
		auto resp=HttpResponse::newHttpJsonResponse(ret);
		callback(resp);
	}
	
	/*
	LOG_DEBUG << "isi imgbase64: " << pImageSrc.input_jpeg << "  end";
	LOG_DEBUG << "isi target_width: " << pImageSrc.target_width << "  end";
	LOG_DEBUG << "isi target_height: " << pImageSrc.target_height << "  end";
	*/
	
	//Authentication algorithm, read database, verify identity, etc...
    //...
	//ImageSrc imgSrc = (*pImageSrc);
	
	Image_Converter img_converter;
	std::string imgbase64, imgbase64_out;
	
	Mat image_out;
	Mat image_resized;
	
	image_out = img_converter.str2mat(pImageSrc.input_jpeg);
	if ( image_out.empty() == false )
	{
		//resize 
		resize(image_out, image_resized, Size(pImageSrc.target_width, pImageSrc.target_height), INTER_LINEAR);
		imgbase64_out = img_converter.mat2str(image_resized);
	
	}
    else
	{
		// error
		ret["code"]="4xx/5xx";
		ret["message"]="[Conversion Base64 to image error ]";
		auto resp=HttpResponse::newHttpJsonResponse(ret);
		callback(resp);
	}
	
	ret["code"]="200";
	ret["message"]="success";
	ret["output_jpeg"]= imgbase64_out;
    auto resp=HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
	
}
