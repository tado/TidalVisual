/*
{
  "CATEGORIES": [
    "Automatically Converted"
  ],
  "INPUTS": [
   {
 "NAME": "scale",
 "TYPE": "float",
 "MAX" : 0.05,
 "MIN" : 0.0001,
 "DEFAULT":0.025
 },
 {
 "NAME": "modVal",
 "TYPE": "float",
 "MAX" : 10.0,
 "MIN" : 0.2,
 "DEFAULT":1.0
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
 "NAME": "vel",
 "LABEL": "vel",
 "TYPE": "float",
 "MIN": 0.0,
 "MAX": 1.0,
 "DEFAULT": 0.5
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
	float col = 0.0;
	
	for(int i=0;i<4;i++) {
		vec2 uv;
		vec2 p=gl_FragCoord.xy/RENDERSIZE;
		uv=p;
		p-=0.5;
		p.x*=RENDERSIZE.x/RENDERSIZE.y;
		z+=zAdder * vel;
		l=length(p)* vel;
		uv+=p/l*(cos(z)+cosinAdder)*(sin(l*9.-z*2.)+sinAdder);
		c[i]=scale/length(abs(mod(uv,modVal)-modVal/2.));
		col += c[i];
	}
	//gl_FragColor=vec4(c/l*finalMulti);
	gl_FragColor=vec4(col, col, col, 1.0);
}