

namespace lab101 {

	inline float ofMap(float value, float inputMin, float inputMax, float outputMin, float outputMax, bool clamp) {
	  
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

}