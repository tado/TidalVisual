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

vec3   iResolution = vec3(RENDERSIZE, 1.0);
float  iGlobalTime = TIME;
//vec4   iMouse = vec4(mouse, 0.0, 1.0);

// uniform vec3       iResolution;
// uniform float      iGlobalTime;
// uniform float      iChannelTime[4];
// uniform vec3       iChannelResolution[4];
// uniform vec4       iMouse;
// uniform vec4       iDate;




// I/O fragment shader by movAX13h, August 2013

#define SHOW_BLOCKS

float rand(float x)
{
    return fract(sin(x) * 4358.5453123);
}

float rand(vec2 co)
{
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5357);
}

float box(vec2 p, vec2 b, float r)
{
  return length(max(abs(p)-b,0.0))-r;
}

float sampleMusic()
{
	return 0.5;
}

void main(void)
{
	const float speed = 2.0;
	const float ySpread = 1.6;
	const int numBlocks = 30;

	float pulse = sampleMusic();
	
	vec2 uv = gl_FragCoord.xy / iResolution.xy - 0.5;
	float aspect = iResolution.x / iResolution.y;
	// defines the background color, which determines the color for the entire thing
	vec3 baseColor = uv.x > 0.0 ? vec3(0.4, 0.4, 0.4) : vec3(0.4, 0.4, 0.4);
	
	vec3 color = pulse*baseColor*0.5*(0.9-cos(uv.x*8.0));
	uv.x *= aspect*2.0;
	
	for (int i = 0; i < numBlocks; i++)
	{
		float z = 1.0-0.7*rand(float(i)*1.4333); // 0=far, 1=near
		float tickTime = iGlobalTime*z*speed + float(i)*1.23753;
		float tick = floor(tickTime);
		
		vec2 pos = vec2(1.5*aspect*(rand(tick)-0.5), sign(uv.x)*ySpread*(0.5-fract(tickTime)));
		pos.x += 0.24*sign(pos.x); // move aside
		if (abs(pos.x) < 0.1) pos.x++; // stupid fix; sign sometimes returns 0
		
		vec2 size = 1.8*z*vec2(0.04, 0.04 + 0.1*rand(tick+0.2));
		float b = box(uv-pos, size, 0.01);
		float dust = z*smoothstep(0.22, 0.0, b)*pulse*0.5;
		#ifdef SHOW_BLOCKS
		float block = 0.2*z*smoothstep(0.002, 0.0, b);
		float shine = 0.6*z*pulse*smoothstep(-0.002, b, 0.007);
		color += dust*baseColor + block*z + shine;
		#else
		color += dust*baseColor;
		#endif
	}
	
	//color -= rand(uv)*0.04;
	gl_FragColor = vec4(color, 1.0) * vec4(r, g, b, 1.0);
}