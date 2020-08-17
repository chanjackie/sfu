var run;

function runCommand() {
	document.getElementById('secOnes').innerHTML++;
	if (document.getElementById('secOnes').innerHTML>=10) {
		document.getElementById('secOnes').innerHTML = 0;
		document.getElementById('secTens').innerHTML++;
	}
	if (document.getElementById('secTens').innerHTML>=6) {
		document.getElementById('secTens').innerHTML = 0;
		document.getElementById('minOnes').innerHTML++;
	}
	if (document.getElementById('minOnes').innerHTML>=10) {
		document.getElementById('minOnes').innerHTML = 0;
		document.getElementById('minTens').innerHTML++;
	}
	if (document.getElementById('minTens').innerHTML>=6) {
		document.getElementById('minTens').innerHTML = 0;
		document.getElementById('hours').innerHTML++;
	}
	if (document.getElementById('hours').innerHTML>=24) {
		document.getElementById('hours').innerHTML = 0;
	}
}

function startClock() {
	run = setInterval(runCommand, 1000);
}

function stopClock() {
	run = clearInterval(run);
}

function resetClock() {
	document.getElementById('secOnes').innerHTML = 0;	
	document.getElementById('secTens').innerHTML = 0;
	document.getElementById('minOnes').innerHTML = 0;
	document.getElementById('minTens').innerHTML = 0;
	document.getElementById('hours').innerHTML = 0;
	run = clearInterval(run);
}
document.getElementById('start').onclick = startClock;
document.getElementById('stop').onclick = stopClock;
document.getElementById('reset').onclick = resetClock;