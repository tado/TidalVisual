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

void main( void ) {
	vec2 p = (gl_FragCoord.xy * 2.0 - RENDERSIZE.xy) / min(RENDERSIZE.x, RENDERSIZE.y);
	float mask = length(p);
	mask=smoothstep(0.1,0.65,mask);
	p.y/=length(p*0.01)*p.y*20.;
	float circle = sin(p.y*3.+TIME*55.);
	circle*=mask;
	//gl_FragColor = vec4(vec3( circle)*vec3(0.1,0.8,0.9+sin(TIME)), 1.0);
	gl_FragColor = vec4(vec3(circle), 1.0) * vec4(r, g, b, 1.0);
}