/*{
	"CREDIT": "by tado",
	"CATEGORIES": [
		"test"
	],
	"INPUTS": [
		{
			"NAME": "velocity",
			"TYPE": "float",
			"DEFAULT": 0.5
		},
		{
			"NAME": "gain",
			"TYPE": "float",
			"DEFAULT": 0.5
		}
	]
}*/



void main() {
	gl_FragColor = vec4(1.0 * gain, 0.0, 0.0, 1.0);
}