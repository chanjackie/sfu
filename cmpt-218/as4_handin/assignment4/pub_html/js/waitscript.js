var player1 = false;
var startGame;
var socket = io("cmpt218.csil.sfu.ca:12834");

socket.on('connect', function() {
	console.log("connected to waiting room");
	$.ajax({
		method: 'get',
		url: '/stats',
		data: '',
		success: displayWaiting
	});
});

socket.on('changeData', function(data, p1) {
	var msg = "";
	for (var i=0;i<data.length;i++) {
		msg = msg + " " + data[i];
	}
	document.getElementById("currentUsers").innerHTML = msg;
	if (data.length == 1) {
		var x = Math.random();
		if (x<0.5) {
			console.log("This is player 1");
			player1 = true;
		}
	}
	if (data.length == 2) {
		if (!p1) {
			if (document.getElementsByClassName("name")[0].value != data[0]) {
				console.log("This is player 1");
				player1 = true;
			} else {
				player1 = false;
				console.log("This is player 2");
			}
		}
		document.getElementById("connected").innerHTML = "Both players connected. Starting in 5 seconds..."
		if (player1) {
			startGame = setTimeout(enterGame, 5000);
		} else {
			startGame = setTimeout(enterGame, 6000);
		}
	}
});

socket.on('returnThis', function() {
	alert("Other player left. Returning to landing...")
	setTimeout(returnLanding, 1000);
});

function returnLanding() {
	document.getElementById("returnForm").submit();
}

function enterGame() {
	if (player1) {
		document.getElementById("player1").submit();	
	} else {
		document.getElementById("player2").submit();
	}
}

function displayWaiting(data) {
	console.log(data[0]._id);
	document.getElementsByClassName("name")[0].value = data[0]._id;
	document.getElementsByClassName("name")[1].value = data[0]._id;
	document.getElementsByClassName("name")[2].value = data[0]._id;
	socket.emit('updateData', player1);
}

function cancelStart() {
	socket.emit('returnOther', player1);
}