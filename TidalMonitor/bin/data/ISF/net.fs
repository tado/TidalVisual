/*
{
"INPUTS" : [
		{
			"NAME": "r",
			"TYPE": "float",
			"DEFAULT": 1.0,
			"MIN": 0.0,
			"MAX": 1.0
		},
		{
			"NAME": "g",
			"TYPE": "float",
			"DEFAULT": 1.0,
			"MIN": 0.0,
			"MAX": 1.0
		},
		{
			"NAME": "b",
			"TYPE": "float",
			"DEFAULT": 1.0,
			"MIN": 0.0,
			"MAX": 1.0
		}
  ]
}
*/

float hex( vec2 p )
{		
	p.y += mod( floor(p.x), 4.0) * 0.5;
	p = abs( fract(p)- 0.5 );
	return 1.-abs( max(p.x*1.5 + p.y, p.y * 2.0) - 1.0 )*12. ;
}

void main( void ) {

	vec2 uv = ( gl_FragCoord.xy / RENDERSIZE.xy ) * 2.0 - 1.0;
	uv.x *= RENDERSIZE.x / RENDERSIZE.y;	
	uv/=dot(uv,uv)*0.7;
	uv.x+=TIME*3.0;
	gl_FragColor = vec4( vec3(hex(uv)), 5.0 ) * vec4(r, g, b, 1.0) * 0.7;

}