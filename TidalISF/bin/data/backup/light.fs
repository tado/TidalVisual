/*{
	"CREDIT": "by tado",
	"CATEGORIES": [
		"test"
	],
	"INPUTS": [
		{
			"NAME": "vel",
			"TYPE": "float",
			"DEFAULT": 1.0
		},
		{
			"NAME": "gain",
			"TYPE": "float",
			"DEFAULT": 1.0
		}
	]
}*/



void main() {
	float light = gain * vel;
	gl_FragColor = vec4(light, light, light, 1.0);
}