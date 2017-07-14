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

OSCFunc.trace(true);

OSCFunc.trace(false);