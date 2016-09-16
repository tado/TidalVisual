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

#ifdef GL_ES
precision mediump float;
#endif


#define HorizontalAmplitude		1.50
#define VerticleAmplitude		0.50

#define HorizontalSpeed			0.90
#define VerticleSpeed			0.50

#define ParticleMinSize			1.46
#define ParticleMaxSize			1.71

#define ParticleBreathingSpeed		0.30
#define ParticleColorChangeSpeed	0.70

#define ParticleCount			2.0
#define ParticleColor1			vec3(9.0, 5.0, 3.0)
#define ParticleColor2			vec3(1.0, 3.0, 9.0)


vec3 checkerBoard( vec2 uv, vec2 pp )
{
    vec2 p = floor( uv * 4.6 );
    float t = mod( p.x + p.y, 2.2);
    vec3 c = vec3(t+pp.x, t+pp.y, t+(pp.x*pp.y));

    return c;
}

vec3 tunnel( vec2 p, float scrollSpeed, float rotateSpeed )
{    
    float a = 2.0 * atan( p.x, p.y  );
    float po = 2.0;
    float px = pow( p.x*p.x, po );
    float py = pow( p.y*p.y, po );
    float r = pow( px + py, 1.0/(2.0*po) );    
    vec2 uvp = vec2( 1.0/r + (TIME*scrollSpeed), a + (TIME*rotateSpeed));	
    vec3 finalColor = checkerBoard( uvp, p ).xyz;
    finalColor *= r;

    return finalColor;
}

/*
vec3 particles( vec2 uv )
{
	vec2 pos = uv * 2.0 - 1.0;
	pos.x *= (RENDERSIZE.x / RENDERSIZE.y);
	
	vec3 c = vec3( 0, 0, 0 );
	
	for( float i = 1.0; i < ParticleCount+1.0; ++i )
	{
		float cs = cos( TIME * HorizontalSpeed * (i/ParticleCount) ) * HorizontalAmplitude;
		float ss = sin( TIME * VerticleSpeed   * (i/ParticleCount) ) * VerticleAmplitude;
		vec2 origin = vec2( cs , ss );
		
		float t = sin( TIME * ParticleBreathingSpeed * i ) * 0.5 + 0.5;
		float particleSize = mix( ParticleMinSize, ParticleMaxSize, t );
		float d = clamp( sin( length( pos - origin )  + particleSize ), 0.0, particleSize);
		
		float t2 = sin( TIME * ParticleColorChangeSpeed * i ) * 0.5 + 0.5;
		vec3 color = mix( ParticleColor1, ParticleColor2, t2 );
		c += color * pow( d, 70.0 );
	}
	
	return c;
}
*/

void main(void)
{
    vec2 uv = gl_FragCoord.xy / RENDERSIZE.xy;
    float timeSpeedX = TIME * 0.0;
    float timeSpeedY = TIME * 0.0;
//    vec2 p = uv + vec2( -0.50+cos(timeSpeedX)*0.2, -0.5-sin(timeSpeedY)*0.3 );
    vec2 p = uv + vec2( -0.5, -0.5 );

    vec3 finalColor = tunnel( p , 8.0, 2.0);


    timeSpeedX = TIME * 1.30001;
    timeSpeedY = TIME * 1.20001;
    p = uv + vec2( -0.50+cos(timeSpeedX)*0.2, -0.5-sin(timeSpeedY)*0.3 );
    
	
//	finalColor += particles( uv );
    float mixcol = (finalColor.r + finalColor.g + finalColor.b) / 3.0;
	
    gl_FragColor = vec4( mixcol, mixcol, mixcol, 1.0 ) * vec4(r, g, b, 1.0);
}