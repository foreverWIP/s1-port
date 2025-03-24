void main()
{
	uint lookup = texture(CurTexture, Frag_UV.st / texture_size.xy).r;
	if (mod(lookup, 16) == 0) discard;
	Out_Color = palette[lookup];
}