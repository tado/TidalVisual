/*
{
  "INPUTS": [
   {
 "NAME": "scale",
 "TYPE": "float",
 "MAX" : 0.05,
 "MIN" : 0.0001,
 "DEFAULT":0.015
 },
 {
 "NAME": "modVal",
 "TYPE": "float",
 "MAX" : 10.0,
 "MIN" : 0.2,
 "DEFAULT":0.3
 },
 {
 "NAME": "zAdder",
 "TYPE": "float",
 "MAX" : 1.0,
 "MIN" : -1.0,
 "DEFAULT":0.7
 },
  {
 "NAME": "cosinAdder",
 "TYPE": "float",
 "MAX" : 1.0,
 "MIN" : -1.0,
 "DEFAULT":0.7
 },
   {
 "NAME": "sinAdder",
 "TYPE": "float",
 "MAX" : 1.0,
 "MIN" : -1.0,
 "DEFAULT":0.7
 },
   {
 "NAME": "finalMulti",
 "TYPE": "float",
 "MAX" : 1.0,
 "MIN" : 0.0,
 "DEFAULT":0.7
 },
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


#ifdef GL_ES
precision mediump float;
#endif

#define PI 3.14159265

void main()
{
	vec4 c;
	float l = TIME;
	float z=TIME;
	
	for(int i=0;i<4;i++) {
		vec2 uv;
		vec2 p=gl_FragCoord.xy/RENDERSIZE;
		uv=p;
		p-=0.5;
		p.x*=RENDERSIZE.x/RENDERSIZE.y;
		z+=zAdder;
		l=length(p);
		uv+=p/l*(cos(z)+cosinAdder)*(sin(l*9.-z*2.)+sinAdder);
		c[i]=scale/length(abs(mod(uv,modVal)-modVal/2.));
	}
	//vec4 fin = vec4(c/l*finalMulti);
	//gl_FragColor=vec4(fin.r * r, fin.g * g, fin.b * b, 1.0);
	gl_FragColor = vec4(c/l*finalMulti) * vec4(r, g, b, 1.0);
}