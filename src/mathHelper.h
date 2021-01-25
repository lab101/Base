#pragma once

namespace lab101 {

    // ofMap from openframeworks source
	inline float ofMap(float value, float inputMin, float inputMax, float outputMin, float outputMax, bool clamp = true) {
	  
	   if (fabs(inputMin - inputMax) < FLT_EPSILON){
		   return outputMin;
	   }
	   else {
		   float outVal = ((value - inputMin) / (inputMax - inputMin) * (outputMax - outputMin) + outputMin);
		  
		   if (clamp){
			   if (outputMax < outputMin){
				   if (outVal < outputMax)outVal = outputMax;
				   else if (outVal > outputMin)outVal = outputMin;
			   }
			   else{
				   if (outVal > outputMax)outVal = outputMax;
				   else if (outVal < outputMin)outVal = outputMin;
			   }
		   }
		   return outVal;
	   }

	}

	inline float toDegrees(float radians){
	    return radians * M_PI / 180;
	}

}
