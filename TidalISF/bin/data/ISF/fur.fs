/*
{
  "IMPORTED" : [

  ],
  "CATEGORIES" : [
    "space",
    "fur",
    "2",
    "Automatically Converted"
  ],
  "INPUTS" : [
         {
            "NAME":"level",
            "TYPE": "float",
           "DEFAULT": 0.02,
            "MIN": 0.01,
            "MAX": 0.05
        },
        {
            "NAME":"speed",
            "TYPE": "float",
           "DEFAULT": 0.5,
            "MIN": 0.0,
            "MAX": 1.0
        },
        {
            "NAME":"shift",
            "TYPE": "float",
           "DEFAULT": 0.06,
            "MIN": 0.0,
            "MAX": 0.1
        }
  ]
}
*/

mat3 getRotZMat(float a){return mat3(cos(a),-sin(a),0.,sin(a),cos(a),0.,0.,0.,1.);}

float dstepf = 0.0;

float map(vec3 p)
{
	p.x += sin(p.z*1.8);
    p.y += cos(p.z*.2) * sin(p.x*.8);
	p *= getRotZMat(p.z*0.8+sin(p.x)+cos(p.y));
    p.xy = mod(p.xy, 0.3) - 0.15;
	dstepf += 0.003;
	return length(p.xy);
}

void main()
{
	vec2 uv = (gl_FragCoord.xy - RENDERSIZE.xy*.5 )/RENDERSIZE.y;
    vec3 rd = normalize(vec3(uv, (1.-dot(uv, uv)*.5)*.5));
    vec3 ro = vec3(0, 0, TIME*1.26), col = vec3(0), sp;
	float cs = cos( TIME*speed ), si = sin( TIME*speed );
    rd.xz = mat2(cs, si,-si, cs)*rd.xz;
	float t=shift, layers=0., d=0., aD;
    float thD = level;
	for(float i=0.; i<250.; i++)
	{
        if(layers>15. || col.x > 1. || t>5.6) break;
        sp = ro + rd*t;
        d = map(sp);
        aD = (thD-abs(d)*15./16.)/thD;
        if(aD>0.)
		{
            col += aD*aD*(3.-2.*aD)/(1. + t*t*0.25)*.2;
            layers++;
		}
        t += max(d*.7, thD*1.5) * dstepf;
	}
    col = max(col, 0.);
    col = mix(col, vec3(min(col.x*1.5, 1.), pow(col.x, 2.5), pow(col.x, 12.)),
              dot(sin(rd.yzx*8. + sin(rd.zxy*8.)), vec3(.1666))+0.4);
    col = mix(col, vec3(col.x*col.x*.85, col.x, col.x*col.x*0.3),
             dot(sin(rd.yzx*4. + sin(rd.zxy*4.)), vec3(.1666))+0.25);
	gl_FragColor = vec4( clamp(col, 0., 1.), 1.0 );
}
