SuperDirt.start

(
//forward OSC message (localhost, port 3333)
var addr = NetAddr.new("127.0.0.1", 3333);
OSCdef(\tidalplay2, {
	arg msg;
	//msg.postln;
	addr.sendMsg("/play2", *msg);
}, '/play2', n);
)

(
OSCdef(\tidaln_on, {
	arg msg;
	//msg.postln;
	addr.sendMsg("/n_on", *msg);
}, '/n_on', n);
)


(
//forward OSC message (localhost, port 3333)
var addr = NetAddr.new("127.0.0.1", 3333);
OSCdef(\testosc, {
	arg msg;
	//msg.postln;
	addr.sendMsg("/n_off", *msg);
}, '/n_off', n);
)


OSCFunc.trace(true);

OSCFunc.trace(false);