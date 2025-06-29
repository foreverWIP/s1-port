float normpdf(in float x, in float sigma)
{
	return 0.39894*exp(-0.5*x*x/(sigma*sigma))/sigma;
}

void main()
{
	//declare stuff
	const int mSize = 9;
	const int kSize = (mSize-1)/2;
	float kernel[mSize];
	vec3 final_colour = vec3(0.0);
	
	//create the 1-D kernel
	float sigma = 9.0;
	float Z = 0.0;
	for (int j = 0; j <= kSize; ++j)
	{
		kernel[kSize+j] = kernel[kSize-j] = normpdf(float(j), sigma);
	}
	
	//get the normalization factor (as the gaussian has been clamped)
	for (int j = 0; j < mSize; ++j)
	{
		Z += kernel[j];
	}
	
	//read out the texels
	for (int i=-kSize; i <= kSize; ++i)
	{
		for (int j=-kSize; j <= kSize; ++j)
		{
			vec4 c = readtex_nodiscard(CurTexture, (Frag_UV.xy+vec2(float(i),float(j))) / texture_size.xy);
			if (c.a < 1.0) {
				c = bgColor;
			}
			final_colour += kernel[kSize+j]*kernel[kSize+i]*c.rgb;
		}
	}
	
	
	Out_Color = vec4(final_colour/(Z*Z), 1.0);
}