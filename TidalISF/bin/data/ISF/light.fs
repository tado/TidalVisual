/*{
	"CREDIT": "by tado",
	"CATEGORIES": [
		"tidal"
	],
	"INPUTS": [
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
		},
		{
			"NAME": "gain",
			"TYPE": "float",
			"DEFAULT": 1.0,
			"MIN": 0.0,
			"MAX": 1.0
		}
	]
}*/

void main() {
	vec3 color = vec3(1.0, 1.0, 1.0);
	gl_FragColor = vec4(vec3(color.r * r, color.g * g, color.b * b) * gain, 1.0);
}
