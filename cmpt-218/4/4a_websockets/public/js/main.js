var username = "unknown";
function myfunction(){
	  username = prompt("Please enter your name", "unknown");
}

var socket = io("http://cmpt218.csil.sfu.ca:8080");

socket.on('connect', function(){
	var msg = username + " has connected!!";
	socket.emit('chat',msg);
});

socket.on('clientChange', function(clientNum){
	document.querySelector("#number").innerHTML = clientNum + " clients connected";
});

socket.on('message',function(message){
	printMessage(message);
});

document.getElementById('discon').onclick = function(){
	socket.emit('chat', `${username} has diconnected`);
	printMessage("You have diconnected");
	socket.close();
	// re-direct
}

document.forms[0].onsubmit = function () {
    var input = document.getElementById("message");
		var msg = username + ": " + input.value
    printMessage(msg);
    socket.emit('chat',msg);
    input.value = '';
};

function printMessage(message) {
    var p = document.createElement("p");
    p.innerText = message;
    document.querySelector("div.messages").appendChild(p);
}
